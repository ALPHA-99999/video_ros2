#include <QCoreApplication>
#include <QDateTime>
#include <QHostAddress>
#include <QObject>
#include <QTimer>

#include <rclcpp/rclcpp.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

#include "command.pb.h"
#include "qmqtt.h"
#include "video_ingest/frame_assembler.hpp"

namespace {
struct FrameHeader {
    quint16 frame_id = 0;
    quint16 fragment_id = 0;
    quint32 frame_size = 0;
};

FrameHeader parseHeader(const QByteArray &data)
{
    FrameHeader header;
    if (data.size() < 8) {
        return header;
    }
    const auto *ptr = reinterpret_cast<const quint8 *>(data.constData());
    header.frame_id = static_cast<quint16>((ptr[0] << 8) | ptr[1]);
    header.fragment_id = static_cast<quint16>((ptr[2] << 8) | ptr[3]);
    header.frame_size = (static_cast<quint32>(ptr[4]) << 24) |
                        (static_cast<quint32>(ptr[5]) << 16) |
                        (static_cast<quint32>(ptr[6]) << 8) |
                        static_cast<quint32>(ptr[7]);
    return header;
}
}  // namespace

class MqttIngestNode : public QObject {
    Q_OBJECT
public:
    MqttIngestNode(QObject *parent = nullptr)
        : QObject(parent),
          node_(std::make_shared<rclcpp::Node>("mqtt_ingest_node")),
          publisher_(node_->create_publisher<video_interfaces::msg::EncodedFrame>("video/encoded", 10))
    {
        const auto host = QString::fromStdString(node_->declare_parameter<std::string>("host", "192.168.12.1"));
        const auto port = static_cast<quint16>(node_->declare_parameter<int>("port", 3333));
        const auto client_id = QString::fromStdString(node_->declare_parameter<std::string>("client_id", "1"));
        const auto username = QString::fromStdString(node_->declare_parameter<std::string>("username", "33"));

        client_ = new QMQTT::Client(QHostAddress(host), port, this);
        client_->setClientId(client_id);
        client_->setUsername(username);
        client_->setCleanSession(true);

        connect(client_, &QMQTT::Client::connected, this, &MqttIngestNode::onConnected);
        connect(client_, &QMQTT::Client::received, this, &MqttIngestNode::onReceived);
        connect(client_, &QMQTT::Client::disconnected, this, &MqttIngestNode::onDisconnected);

        client_->connectToHost();
        RCLCPP_INFO(node_->get_logger(), "Connecting to MQTT broker %s:%u", host.toStdString().c_str(), static_cast<unsigned>(port));
    }

    rclcpp::Node::SharedPtr node() const { return node_; }

private slots:
    void onConnected()
    {
        client_->subscribe("CustomByteBlock", 1);
        RCLCPP_INFO(node_->get_logger(), "Connected to MQTT broker and subscribed to CustomByteBlock");
    }

    void onDisconnected()
    {
        RCLCPP_WARN(node_->get_logger(), "MQTT disconnected");
    }

    void onReceived(const QMQTT::Message &message)
    {
        if (message.topic() != "CustomByteBlock") {
            return;
        }

        robomaster::CustomByteBlock block;
        const QByteArray payload = message.payload();
        if (!block.ParseFromArray(payload.constData(), payload.size())) {
            RCLCPP_WARN(node_->get_logger(), "Failed to parse CustomByteBlock payload");
            return;
        }

        const std::string &block_data = block.data();
        QByteArray raw(block_data.data(), static_cast<int>(block_data.size()));
        if (raw.size() <= 8) {
            return;
        }

        const qint64 recv_ms = QDateTime::currentMSecsSinceEpoch();
        const FrameHeader header = parseHeader(raw);
        const auto assembled = assembler_.ingest(header.frame_id,
                                                 header.fragment_id,
                                                 header.frame_size,
                                                 raw.mid(8),
                                                 recv_ms);
        if (!assembled) {
            return;
        }

        video_interfaces::msg::EncodedFrame msg;
        msg.header.stamp = node_->now();
        msg.header.frame_id = "mqtt";
        msg.source = "mqtt";
        msg.frame_id = assembled->frame_id;
        msg.frame_size = assembled->frame_size;
        msg.codec = "hevc";
        msg.data.assign(assembled->data.begin(), assembled->data.end());
        publisher_->publish(std::move(msg));
    }

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<video_interfaces::msg::EncodedFrame>::SharedPtr publisher_;
    QMQTT::Client *client_ = nullptr;
    video_ingest::FrameAssembler assembler_;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    rclcpp::init(argc, argv);

    MqttIngestNode ingest;
    QTimer spin_timer;
    QObject::connect(&spin_timer, &QTimer::timeout, [&]() {
        if (!rclcpp::ok()) {
            app.quit();
            return;
        }
        rclcpp::spin_some(ingest.node());
    });
    spin_timer.start(5);

    const int rc = app.exec();
    rclcpp::shutdown();
    return rc;
}

#include "mqtt_ingest_node.moc"