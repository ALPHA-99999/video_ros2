#include "video_viewer_qt/viewer_window.hpp"

#include "video_viewer_qt/image_widget.hpp"

#include <QDateTime>
#include <QImage>
#include <QVBoxLayout>

ViewerWindow::ViewerWindow(QWidget *parent)
    : QWidget(parent),
      node_(std::make_shared<rclcpp::Node>("video_viewer_qt"))
{
    setWindowTitle("video_ros2 viewer");
    resize(1280, 720);

    auto *layout = new QVBoxLayout(this);
    image_widget_ = new ImageWidget(this);
    status_label_ = new QLabel("Waiting for video/rgb ...", this);
    layout->addWidget(image_widget_, 1);
    layout->addWidget(status_label_);
    setLayout(layout);

    subscription_ = node_->create_subscription<sensor_msgs::msg::Image>(
        "video/rgb", 10,
        std::bind(&ViewerWindow::onImage, this, std::placeholders::_1));
}

void ViewerWindow::onImage(const sensor_msgs::msg::Image &msg)
{
    if (msg.encoding != "rgb8") {
        status_label_->setText(QString("Unsupported encoding: %1").arg(QString::fromStdString(msg.encoding)));
        return;
    }
    if (msg.data.empty() || msg.width == 0 || msg.height == 0) {
        return;
    }

    QImage image(msg.data.data(),
                 static_cast<int>(msg.width),
                 static_cast<int>(msg.height),
                 static_cast<int>(msg.step),
                 QImage::Format_RGB888);
    image_widget_->setImage(image);

    const qint64 nowMs = QDateTime::currentMSecsSinceEpoch();
    if (fps_window_start_ms_ == 0) {
        fps_window_start_ms_ = nowMs;
    }
    ++frame_count_;
    const qint64 elapsedMs = nowMs - fps_window_start_ms_;
    if (elapsedMs >= 1000) {
        fps_ = static_cast<double>(frame_count_) * 1000.0 / static_cast<double>(elapsedMs);
        frame_count_ = 0;
        fps_window_start_ms_ = nowMs;
    }

    status_label_->setText(QString("topic=video/rgb  source=%1  size=%2x%3  fps=%4")
                               .arg(QString::fromStdString(msg.header.frame_id))
                               .arg(msg.width)
                               .arg(msg.height)
                               .arg(fps_, 0, 'f', 2));
}