#pragma once

#include <chrono>
#include <cstdint>
#include <mutex>
#include <string>

#include <QObject>
#include <QImage>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <video_interfaces/srv/robot_login.hpp>

class ViewerBackend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText NOTIFY stateChanged)
    Q_PROPERTY(QString source READ source NOTIFY stateChanged)
    Q_PROPERTY(int frameWidth READ frameWidth NOTIFY stateChanged)
    Q_PROPERTY(int frameHeight READ frameHeight NOTIFY stateChanged)
    Q_PROPERTY(double fps READ fps NOTIFY stateChanged)
    Q_PROPERTY(QString loginStatusText READ loginStatusText NOTIFY stateChanged)
    Q_PROPERTY(bool loginPending READ loginPending NOTIFY stateChanged)
    Q_PROPERTY(bool hasFrame READ hasFrame NOTIFY frameUpdated)
    Q_PROPERTY(quint64 frameRevision READ frameRevision NOTIFY frameUpdated)

public:
    explicit ViewerBackend(QObject *parent = nullptr);

    rclcpp::Node::SharedPtr node() const { return node_; }
    Q_INVOKABLE void requestMqttConnect(const QString &clientId);
    Q_INVOKABLE void requestMqttDisconnect();
    void handleImage(const sensor_msgs::msg::Image &msg);

    QString statusText() const;
    QString source() const;
    int frameWidth() const;
    int frameHeight() const;
    double fps() const;
    QString loginStatusText() const;
    bool loginPending() const;
    bool hasFrame() const;
    quint64 frameRevision() const;
    QImage latestImage() const;

signals:
    void stateChanged();
    void frameUpdated();

private:
    void updateStatusLocked(const QString &status);
    void updateFpsLocked(qint64 now_ms);
    void updateLoginStatusLocked(const QString &status);
    void requestMqttAction(const QString &action, const QString &clientId);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Client<video_interfaces::srv::RobotLogin>::SharedPtr login_client_;
    mutable std::mutex mutex_;
    QImage latest_image_;
    QString status_text_ = "Waiting for video/rgb ...";
    QString source_ = "video/rgb";
    int frame_width_ = 0;
    int frame_height_ = 0;
    double fps_ = 0.0;
    QString login_status_text_ = "MQTT: disconnected";
    bool login_pending_ = false;
    qint64 frame_count_ = 0;
    qint64 fps_window_start_ms_ = 0;
    quint64 frame_revision_ = 0;
    bool has_frame_ = false;
};
