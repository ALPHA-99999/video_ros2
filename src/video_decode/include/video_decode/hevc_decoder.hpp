#pragma once

#include <vector>

#include <sensor_msgs/msg/image.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libswscale/swscale.h>
}

class HevcDecoder {
public:
    HevcDecoder();
    ~HevcDecoder();

    bool initialized() const { return initialized_; }
    bool decodeAndFill(const video_interfaces::msg::EncodedFrame &input,
                       std::vector<sensor_msgs::msg::Image> &output_images);

private:
    bool init();
    bool initHardwareDevice();
    void disableHardwareDecoding();
    bool frameToRgbImage(const video_interfaces::msg::EncodedFrame &input,
                         AVFrame *frame,
                         sensor_msgs::msg::Image &image);
    static AVPixelFormat getHwFormat(AVCodecContext *ctx, const AVPixelFormat *pix_fmts);

    bool initialized_ = false;
    const AVCodec *codec_ = nullptr;
    AVCodecContext *codec_ctx_ = nullptr;
    AVPacket *packet_ = nullptr;
    AVFrame *frame_ = nullptr;
    AVFrame *sw_frame_ = nullptr;
    AVPixelFormat hw_pix_fmt_ = AV_PIX_FMT_NONE;
    AVHWDeviceType hw_device_type_ = AV_HWDEVICE_TYPE_NONE;
    AVBufferRef *hw_device_ctx_ = nullptr;
    bool hw_enabled_ = false;
    SwsContext *rgb_sws_ctx_ = nullptr;
    int rgb_sws_width_ = 0;
    int rgb_sws_height_ = 0;
    AVPixelFormat rgb_sws_src_fmt_ = AV_PIX_FMT_NONE;
};
