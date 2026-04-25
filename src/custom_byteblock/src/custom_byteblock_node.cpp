#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

#include "custom_byteblock/frame_assembler.hpp"

namespace {
struct FrameHeader {
    std::uint16_t frame_id = 0;
    std::uint16_t fragment_id = 0;
    std::uint32_t frame_size = 0;
};

FrameHeader parseHeader(const std::vector<std::uint8_t> &data)
{
    FrameHeader header;
    if (data.size() < 8) {
        return header;
    }
    header.frame_id = static_cast<std::uint16_t>((static_cast<std::uint16_t>(data[0]) << 8) | data[1]);
    header.fragment_id = static_cast<std::uint16_t>((static_cast<std::uint16_t>(data[2]) << 8) | data[3]);
    header.frame_size = (static_cast<std::uint32_t>(data[4]) << 24) |
                        (static_cast<std::uint32_t>(data[5]) << 16) |
                        (static_cast<std::uint32_t>(data[6]) << 8) |
                        static_cast<std::uint32_t>(data[7]);
    return header;
}
}  // namespace

class CustomByteBlockNode : public rclcpp::Node {
public:
    CustomByteBlockNode()
        : rclcpp::Node("custom_byteblock_node")
    {
        publisher_ = create_publisher<video_interfaces::msg::EncodedFrame>("video/encoded", 10);
        subscription_ = create_subscription<std_msgs::msg::UInt8MultiArray>(
            "video/raw_byte_block", 10,
            std::bind(&CustomByteBlockNode::onBlock, this, std::placeholders::_1));
    }

private:
    void onBlock(const std_msgs::msg::UInt8MultiArray &msg)
    {
        ++raw_block_count_;

        const auto recv_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 std::chrono::steady_clock::now().time_since_epoch())
                                 .count();
        const std::vector<std::uint8_t> &data = msg.data;
        if (data.size() <= 8) {
            return;
        }

        const FrameHeader header = parseHeader(data);
        const std::vector<std::uint8_t> fragment(data.begin() + 8, data.end());
        const auto assembled = assembler_.ingest(header.frame_id,
                                                 header.fragment_id,
                                                 header.frame_size,
                                                 fragment,
                                                 recv_ms);
        if (!assembled) {
            return;
        }

        ++assembled_frame_count_;
        ++assembled_frames_this_second_;
        logFpsIfDue();

        video_interfaces::msg::EncodedFrame out;
        out.header.stamp = now();
        out.header.frame_id = "custom_byteblock";
        out.source = "mqtt";
        out.frame_id = assembled->frame_id;
        out.frame_size = assembled->frame_size;
        out.codec = "hevc";
        out.data = std::move(assembled->data);
        publisher_->publish(std::move(out));
    }

    void logFpsIfDue()
    {
        const auto now = std::chrono::steady_clock::now();
        const auto elapsed = now - fps_window_start_;
        if (elapsed < std::chrono::seconds(1)) {
            return;
        }

        const auto elapsed_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        const double fps = static_cast<double>(assembled_frames_this_second_) * 1000.0 /
                           static_cast<double>(elapsed_ms);
        RCLCPP_INFO(get_logger(),
                    "CustomByteBlock FPS: %.2f total_frames=%llu total_blocks=%llu",
                    fps,
                    static_cast<unsigned long long>(assembled_frame_count_),
                    static_cast<unsigned long long>(raw_block_count_));
        assembled_frames_this_second_ = 0;
        fps_window_start_ = now;
    }

    rclcpp::Publisher<video_interfaces::msg::EncodedFrame>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr subscription_;
    custom_byteblock::FrameAssembler assembler_;
    std::uint64_t raw_block_count_ = 0;
    std::uint64_t assembled_frame_count_ = 0;
    std::uint64_t assembled_frames_this_second_ = 0;
    std::chrono::steady_clock::time_point fps_window_start_ = std::chrono::steady_clock::now();
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CustomByteBlockNode>());
    rclcpp::shutdown();
    return 0;
}
