#include <QCoreApplication>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QTimer>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

#include <qmqtt.h>

#include "command.pb.h"

class MqttBridgeNode : public QObject {
    Q_OBJECT
public:
    explicit MqttBridgeNode(QObject *parent = nullptr)
        : QObject(parent),
          node_(std::make_shared<rclcpp::Node>("mqtt_bridge_node")),
          publisher_(node_->create_publisher<std_msgs::msg::UInt8MultiArray>("video/raw_byte_block", 10))
    {
        const auto host = QString::fromStdString(node_->declare_parameter<std::string>("host", "127.0.0.1"));
        const auto port = static_cast<quint16>(node_->declare_parameter<int>("port", 3333));
        const auto client_id = QString::fromStdString(node_->declare_parameter<std::string>("client_id", "1"));
        const auto username = QString::fromStdString(node_->declare_parameter<std::string>("username", "33"));
        topic_ = QString::fromStdString(node_->declare_parameter<std::string>("topic", "CustomByteBlock"));

        client_ = new QMQTT::Client(host, port, false, false, this);
        client_->setClientId(client_id);
        client_->setUsername(username);
        client_->setCleanSession(true);
        client_->setVersion(QMQTT::V3_1_1);

        connect(client_, &QMQTT::Client::connected, this, &MqttBridgeNode::onConnected);
        connect(client_, &QMQTT::Client::received, this, &MqttBridgeNode::onReceived);
        connect(client_, &QMQTT::Client::disconnected, this, &MqttBridgeNode::onDisconnected);

        client_->connectToHost();
        RCLCPP_INFO(node_->get_logger(), "Connecting to MQTT broker %s:%u",
                    host.toStdString().c_str(), static_cast<unsigned>(port));
    }

    rclcpp::Node::SharedPtr node() const { return node_; }

private slots:
    void onConnected()
    {
        client_->subscribe(topic_, 1);
        RCLCPP_INFO(node_->get_logger(), "Connected to MQTT broker and subscribed to %s",
                    topic_.toStdString().c_str());
    }

    void onDisconnected()
    {
        RCLCPP_WARN(node_->get_logger(), "MQTT disconnected");
    }

    void onReceived(const QMQTT::Message &message)
    {
        if (message.topic() != topic_) {
            return;
        }

        robomaster::CustomByteBlock block;
        const QByteArray payload = message.payload();
        if (!block.ParseFromArray(payload.constData(), payload.size())) {
            RCLCPP_WARN(node_->get_logger(), "Failed to parse CustomByteBlock payload");
            return;
        }

        const std::string &block_data = block.data();
        std_msgs::msg::UInt8MultiArray msg;
        msg.data.assign(block_data.begin(), block_data.end());
        publisher_->publish(std::move(msg));
    }

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr publisher_;
    QMQTT::Client *client_ = nullptr;
    QString topic_;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    rclcpp::init(argc, argv);

    MqttBridgeNode bridge;
    QTimer spin_timer;
    QObject::connect(&spin_timer, &QTimer::timeout, [&]() {
        if (!rclcpp::ok()) {
            app.quit();
            return;
        }
        rclcpp::spin_some(bridge.node());
    });
    spin_timer.start(5);

    const int rc = app.exec();
    rclcpp::shutdown();
    return rc;
}

#include "mqtt_bridge_node.moc"
