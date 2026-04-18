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
        std::vector<sensor_msgs::msg::Image> images;
        if (!decoder_.decodeAndFill(msg, images)) {
            RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000, "Failed to decode incoming HEVC frame");
            return;
        }
        for (auto &image : images) {
            publisher_->publish(std::move(image));
        }
    }

    HevcDecoder decoder_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::Subscription<video_interfaces::msg::EncodedFrame>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DecoderNode>());
    rclcpp::shutdown();
    return 0;
}