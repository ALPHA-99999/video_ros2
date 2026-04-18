#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <QLabel>
#include <QWidget>

class ImageWidget;

class ViewerWindow : public QWidget {
    Q_OBJECT
public:
    explicit ViewerWindow(QWidget *parent = nullptr);
    ~ViewerWindow() override = default;

    rclcpp::Node::SharedPtr node() const { return node_; }

private:
    void onImage(const sensor_msgs::msg::Image &msg);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    ImageWidget *image_widget_ = nullptr;
    QLabel *status_label_ = nullptr;
    qint64 frame_count_ = 0;
    qint64 fps_window_start_ms_ = 0;
    double fps_ = 0.0;
};