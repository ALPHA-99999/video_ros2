#include "video_decode/hevc_decoder.hpp"

#include <cstring>

namespace {
bool isHardwarePixelFormatForDevice(AVHWDeviceType device_type, AVPixelFormat pixel_format)
{
    switch (device_type) {
    case AV_HWDEVICE_TYPE_D3D11VA:
        return pixel_format == AV_PIX_FMT_D3D11 || pixel_format == AV_PIX_FMT_D3D11VA_VLD;
    case AV_HWDEVICE_TYPE_DXVA2:
        return pixel_format == AV_PIX_FMT_DXVA2_VLD;
    default:
        return false;
    }
}
}  // namespace

HevcDecoder::HevcDecoder()
{
    initialized_ = init();
}

HevcDecoder::~HevcDecoder()
{
    if (packet_) av_packet_free(&packet_);
    if (frame_) av_frame_free(&frame_);
    if (sw_frame_) av_frame_free(&sw_frame_);
    if (hw_device_ctx_) av_buffer_unref(&hw_device_ctx_);
    if (rgb_sws_ctx_) sws_freeContext(rgb_sws_ctx_);
    if (codec_ctx_) avcodec_free_context(&codec_ctx_);
}

AVPixelFormat HevcDecoder::getHwFormat(AVCodecContext *ctx, const AVPixelFormat *pix_fmts)
{
    auto *decoder = static_cast<HevcDecoder *>(ctx->opaque);
    if (!decoder) return pix_fmts[0];

    for (const AVPixelFormat *fmt = pix_fmts; *fmt != AV_PIX_FMT_NONE; ++fmt) {
        if (decoder->hw_enabled_ && isHardwarePixelFormatForDevice(decoder->hw_device_type_, *fmt)) {
            decoder->hw_pix_fmt_ = *fmt;
            return *fmt;
        }
    }

    while (*pix_fmts != AV_PIX_FMT_NONE) {
        if (*pix_fmts != AV_PIX_FMT_D3D11 && *pix_fmts != AV_PIX_FMT_D3D11VA_VLD && *pix_fmts != AV_PIX_FMT_DXVA2_VLD) {
            return *pix_fmts;
        }
        ++pix_fmts;
    }

    decoder->disableHardwareDecoding();
    return AV_PIX_FMT_NONE;
}

void HevcDecoder::disableHardwareDecoding()
{
    hw_enabled_ = false;
    hw_pix_fmt_ = AV_PIX_FMT_NONE;
    hw_device_type_ = AV_HWDEVICE_TYPE_NONE;
    if (codec_ctx_) {
        codec_ctx_->opaque = nullptr;
        codec_ctx_->get_format = nullptr;
        if (codec_ctx_->hw_device_ctx) av_buffer_unref(&codec_ctx_->hw_device_ctx);
    }
    if (hw_device_ctx_) av_buffer_unref(&hw_device_ctx_);
}

bool HevcDecoder::initHardwareDevice()
{
    struct HardwareCandidate { AVHWDeviceType device_type; AVPixelFormat pixel_format; };
    static const HardwareCandidate candidates[] = {
        {AV_HWDEVICE_TYPE_D3D11VA, AV_PIX_FMT_D3D11},
        {AV_HWDEVICE_TYPE_DXVA2, AV_PIX_FMT_DXVA2_VLD},
    };

    for (const auto &candidate : candidates) {
        AVBufferRef *device_ctx = nullptr;
        if (av_hwdevice_ctx_create(&device_ctx, candidate.device_type, nullptr, nullptr, 0) < 0) continue;
        AVBufferRef *codec_hw_ctx = av_buffer_ref(device_ctx);
        if (!codec_hw_ctx) {
            av_buffer_unref(&device_ctx);
            continue;
        }
        hw_device_ctx_ = device_ctx;
        codec_ctx_->hw_device_ctx = codec_hw_ctx;
        hw_device_type_ = candidate.device_type;
        hw_pix_fmt_ = candidate.pixel_format;
        hw_enabled_ = true;
        codec_ctx_->opaque = this;
        codec_ctx_->get_format = getHwFormat;
        return true;
    }

    disableHardwareDecoding();
    return false;
}

bool HevcDecoder::init()
{
    codec_ = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    if (!codec_) return false;

    codec_ctx_ = avcodec_alloc_context3(codec_);
    if (!codec_ctx_) return false;

    initHardwareDevice();
    codec_ctx_->flags |= AV_CODEC_FLAG_LOW_DELAY;
    codec_ctx_->flags2 |= AV_CODEC_FLAG2_FAST;

    int open_ret = avcodec_open2(codec_ctx_, codec_, nullptr);
    if (open_ret < 0 && hw_enabled_) {
        disableHardwareDecoding();
        open_ret = avcodec_open2(codec_ctx_, codec_, nullptr);
    }
    if (open_ret < 0) {
        avcodec_free_context(&codec_ctx_);
        return false;
    }

    packet_ = av_packet_alloc();
    frame_ = av_frame_alloc();
    sw_frame_ = av_frame_alloc();
    return packet_ && frame_ && sw_frame_;
}

bool HevcDecoder::frameToRgbImage(const video_interfaces::msg::EncodedFrame &input,
                                  AVFrame *frame,
                                  sensor_msgs::msg::Image &image)
{
    AVFrame *src_frame = frame;
    if (hw_enabled_ && static_cast<AVPixelFormat>(frame->format) == hw_pix_fmt_) {
        av_frame_unref(sw_frame_);
        if (av_hwframe_transfer_data(sw_frame_, frame, 0) < 0) return false;
        sw_frame_->width = frame->width;
        sw_frame_->height = frame->height;
        src_frame = sw_frame_;
    }

    const int width = src_frame->width;
    const int height = src_frame->height;
    if (width <= 0 || height <= 0) return false;

    const AVPixelFormat src_fmt = static_cast<AVPixelFormat>(src_frame->format);
    if (!rgb_sws_ctx_ || rgb_sws_width_ != width || rgb_sws_height_ != height || rgb_sws_src_fmt_ != src_fmt) {
        if (rgb_sws_ctx_) sws_freeContext(rgb_sws_ctx_);
        rgb_sws_ctx_ = sws_getContext(width, height, src_fmt, width, height, AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
        rgb_sws_width_ = width;
        rgb_sws_height_ = height;
        rgb_sws_src_fmt_ = src_fmt;
    }
    if (!rgb_sws_ctx_) return false;

    image.header = input.header;
    image.header.frame_id = input.source;
    image.width = static_cast<uint32_t>(width);
    image.height = static_cast<uint32_t>(height);
    image.encoding = "rgb8";
    image.is_bigendian = false;
    image.step = static_cast<sensor_msgs::msg::Image::_step_type>(width * 3);
    image.data.resize(static_cast<size_t>(image.step) * static_cast<size_t>(height));

    uint8_t *dst_data[1] = { image.data.data() };
    int dst_linesize[1] = { static_cast<int>(image.step) };
    sws_scale(rgb_sws_ctx_, src_frame->data, src_frame->linesize, 0, height, dst_data, dst_linesize);
    return true;
}

bool HevcDecoder::decodeAndFill(const video_interfaces::msg::EncodedFrame &input,
                                std::vector<sensor_msgs::msg::Image> &output_images)
{
    if (!initialized_) return false;

    av_packet_unref(packet_);
    if (av_new_packet(packet_, static_cast<int>(input.data.size())) < 0) return false;
    std::memcpy(packet_->data, input.data.data(), input.data.size());

    const int send_ret = avcodec_send_packet(codec_ctx_, packet_);
    if (send_ret < 0 && send_ret != AVERROR(EAGAIN)) return false;

    while (true) {
        av_frame_unref(frame_);
        const int ret = avcodec_receive_frame(codec_ctx_, frame_);
        if (ret == 0) {
            sensor_msgs::msg::Image image;
            if (frameToRgbImage(input, frame_, image)) output_images.push_back(std::move(image));
            continue;
        }
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;
        return false;
    }
    return true;
}