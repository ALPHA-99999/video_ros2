#include "video_viewer_qt/viewer_backend.hpp"

#include <QDateTime>
#include <functional>

ViewerBackend::ViewerBackend(QObject *parent)
    : QObject(parent),
      node_(std::make_shared<rclcpp::Node>("video_viewer_qt"))
{
    login_client_ = node_->create_client<video_interfaces::srv::RobotLogin>("/mqtt_bridge/control_mqtt");
    subscription_ = node_->create_subscription<sensor_msgs::msg::Image>(
        "video/rgb", 10,
        std::bind(&ViewerBackend::handleImage, this, std::placeholders::_1));
}

void ViewerBackend::requestMqttConnect(const QString &clientId)
{
    const QString trimmed = clientId.trimmed();
    if (trimmed.isEmpty()) {
        std::lock_guard<std::mutex> lock(mutex_);
        updateLoginStatusLocked("MQTT: client_id 不能为空");
        emit stateChanged();
        return;
    }

    requestMqttAction("connect", trimmed);
}

void ViewerBackend::requestMqttDisconnect()
{
    requestMqttAction("disconnect", QString());
}

void ViewerBackend::requestMqttAction(const QString &action, const QString &clientId)
{
    bool should_emit = false;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (login_pending_) {
            updateLoginStatusLocked("MQTT 请求处理中，请稍后");
            should_emit = true;
        }
    }
    if (should_emit) {
        emit stateChanged();
        return;
    }

    if (!login_client_ || !login_client_->wait_for_service(std::chrono::seconds(2))) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            updateLoginStatusLocked("MQTT 控制服务不可用");
        }
        emit stateChanged();
        return;
    }

    {
        std::lock_guard<std::mutex> lock(mutex_);
        login_pending_ = true;
        should_emit = true;
    }
    if (should_emit) {
        emit stateChanged();
    }

    auto request = std::make_shared<video_interfaces::srv::RobotLogin::Request>();
    request->action = action.toStdString();
    request->client_id = clientId.toStdString();
    login_client_->async_send_request(
        request,
        [this](rclcpp::Client<video_interfaces::srv::RobotLogin>::SharedFuture future) {
            const auto response = future.get();
            {
                std::lock_guard<std::mutex> lock(mutex_);
                updateLoginStatusLocked(QString("MQTT: %1").arg(QString::fromStdString(response->message)));
                login_pending_ = false;
            }
            emit stateChanged();
        });
}

void ViewerBackend::handleImage(const sensor_msgs::msg::Image &msg)
{
    bool changed = false;
    bool frame_updated = false;

    if (msg.encoding != "rgb8") {
        std::lock_guard<std::mutex> lock(mutex_);
        updateStatusLocked(QString("Unsupported encoding: %1").arg(QString::fromStdString(msg.encoding)));
        changed = true;
    } else if (msg.data.empty() || msg.width == 0 || msg.height == 0) {
        return;
    } else {
        QImage image(msg.data.data(),
                     static_cast<int>(msg.width),
                     static_cast<int>(msg.height),
                     static_cast<int>(msg.step),
                     QImage::Format_RGB888);
        if (image.isNull()) {
            return;
        }

        const qint64 now_ms = QDateTime::currentMSecsSinceEpoch();
        std::lock_guard<std::mutex> lock(mutex_);
        latest_image_ = image.copy();
        frame_width_ = static_cast<int>(msg.width);
        frame_height_ = static_cast<int>(msg.height);
        source_ = QString::fromStdString(msg.header.frame_id);
        has_frame_ = true;
        frame_revision_ += 1;
        updateFpsLocked(now_ms);
        updateStatusLocked(QString("topic=video/rgb  source=%1  size=%2x%3  fps=%4")
                               .arg(source_)
                               .arg(frame_width_)
                               .arg(frame_height_)
                               .arg(fps_, 0, 'f', 2));
        changed = true;
        frame_updated = true;
    }

    if (frame_updated) {
        emit frameUpdated();
    }
    if (changed) {
        emit stateChanged();
    }
}

QString ViewerBackend::statusText() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return status_text_;
}

QString ViewerBackend::source() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return source_;
}

int ViewerBackend::frameWidth() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return frame_width_;
}

int ViewerBackend::frameHeight() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return frame_height_;
}

double ViewerBackend::fps() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return fps_;
}

QString ViewerBackend::loginStatusText() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return login_status_text_;
}

bool ViewerBackend::loginPending() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return login_pending_;
}

bool ViewerBackend::hasFrame() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return has_frame_;
}

quint64 ViewerBackend::frameRevision() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return frame_revision_;
}

QImage ViewerBackend::latestImage() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return latest_image_;
}

void ViewerBackend::updateStatusLocked(const QString &status)
{
    status_text_ = status;
}

void ViewerBackend::updateFpsLocked(qint64 now_ms)
{
    if (fps_window_start_ms_ == 0) {
        fps_window_start_ms_ = now_ms;
    }
    ++frame_count_;
    const qint64 elapsed_ms = now_ms - fps_window_start_ms_;
    if (elapsed_ms >= 1000) {
        fps_ = static_cast<double>(frame_count_) * 1000.0 / static_cast<double>(elapsed_ms);
        frame_count_ = 0;
        fps_window_start_ms_ = now_ms;
    }
}

void ViewerBackend::updateLoginStatusLocked(const QString &status)
{
    login_status_text_ = status;
}
