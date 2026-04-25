#include <cstdint>
#include <chrono>
#include <memory>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

#include "video_decode/hevc_decoder.hpp"

class DecoderNode : public rclcpp::Node {
public:
    DecoderNode()
        : rclcpp::Node("decoder_node")
    {
        publisher_ = create_publisher<sensor_msgs::msg::Image>("video/rgb", 10);
        subscription_ = create_subscription<video_interfaces::msg::EncodedFrame>(
            "video/encoded", 10,
            std::bind(&DecoderNode::onFrame, this, std::placeholders::_1));

        if (!decoder_.initialized()) {
            RCLCPP_ERROR(get_logger(), "FFmpeg HEVC decoder failed to initialize");
        } else {
            RCLCPP_INFO(get_logger(), "Decoder node ready");
        }
    }

private:
    void onFrame(const video_interfaces::msg::EncodedFrame &msg)
    {
        ++encoded_frame_count_;

        std::vector<sensor_msgs::msg::Image> images;
        if (!decoder_.decodeAndFill(msg, images)) {
            RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000, "Failed to decode incoming HEVC frame");
            return;
        }
        for (auto &image : images) {
            ++decoded_image_count_;
            ++decoded_images_this_second_;
            logFpsIfDue();
            publisher_->publish(image);
        }
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
        const double fps = static_cast<double>(decoded_images_this_second_) * 1000.0 /
                           static_cast<double>(elapsed_ms);
        RCLCPP_INFO(get_logger(),
                    "Decoded FPS: %.2f total_decoded=%llu total_encoded=%llu",
                    fps,
                    static_cast<unsigned long long>(decoded_image_count_),
                    static_cast<unsigned long long>(encoded_frame_count_));
        decoded_images_this_second_ = 0;
        fps_window_start_ = now;
    }

    HevcDecoder decoder_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::Subscription<video_interfaces::msg::EncodedFrame>::SharedPtr subscription_;
    std::uint64_t encoded_frame_count_ = 0;
    std::uint64_t decoded_image_count_ = 0;
    std::uint64_t decoded_images_this_second_ = 0;
    std::chrono::steady_clock::time_point fps_window_start_ = std::chrono::steady_clock::now();
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DecoderNode>());
    rclcpp::shutdown();
    return 0;
}
