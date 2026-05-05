#include <QCoreApplication>
#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QTimer>

#include <functional>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <video_interfaces/srv/robot_login.hpp>

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
        broker_host_ = QString::fromStdString(node_->declare_parameter<std::string>("host", "127.0.0.1"));
        broker_port_ = static_cast<quint16>(node_->declare_parameter<int>("port", 3333));
        current_client_id_ = QString::fromStdString(node_->declare_parameter<std::string>("client_id", "1"));
        mqtt_username_ = QString::fromStdString(node_->declare_parameter<std::string>("username", "33"));
        topic_ = QString::fromStdString(node_->declare_parameter<std::string>("topic", "CustomByteBlock"));

        client_ = new QMQTT::Client(broker_host_, broker_port_, false, false, this);
        client_->setClientId(current_client_id_);
        client_->setUsername(mqtt_username_);
        client_->setCleanSession(true);
        client_->setVersion(QMQTT::V3_1_1);

        connect(client_, &QMQTT::Client::connected, this, &MqttBridgeNode::onConnected);
        connect(client_, &QMQTT::Client::received, this, &MqttBridgeNode::onReceived);
        connect(client_, &QMQTT::Client::disconnected, this, &MqttBridgeNode::onDisconnected);

        mqtt_control_service_ = node_->create_service<video_interfaces::srv::RobotLogin>(
            "/mqtt_bridge/control_mqtt",
            std::bind(&MqttBridgeNode::onControlMqtt,
                      this,
                      std::placeholders::_1,
                      std::placeholders::_2));

        RCLCPP_INFO(node_->get_logger(), "MQTT bridge ready, broker %s:%u will connect on demand with client_id=%s",
                    broker_host_.toStdString().c_str(),
                    static_cast<unsigned>(broker_port_),
                    current_client_id_.toStdString().c_str());
    }

    rclcpp::Node::SharedPtr node() const { return node_; }

private slots:
    void onConnected()
    {
        mqtt_connecting_ = false;
        client_->subscribe(topic_, 1);
        RCLCPP_INFO(node_->get_logger(), "Connected to MQTT broker and subscribed to %s",
                    topic_.toStdString().c_str());
    }

    void onDisconnected()
    {
        mqtt_connecting_ = false;
        RCLCPP_WARN(node_->get_logger(), "MQTT disconnected");
    }

    void onControlMqtt(const std::shared_ptr<video_interfaces::srv::RobotLogin::Request> request,
                       std::shared_ptr<video_interfaces::srv::RobotLogin::Response> response)
    {
        const QString action = QString::fromStdString(request->action).trimmed().toLower();
        const QString client_id = QString::fromStdString(request->client_id).trimmed();
        constexpr int kTimeoutMs = 5000;

        if (action != "connect" && action != "disconnect") {
            response->success = false;
            response->message = "action 必须是 connect 或 disconnect";
            return;
        }

        if (action == "connect" && client_id.isEmpty()) {
            response->success = false;
            response->message = "client_id 不能为空";
            return;
        }

        if (action == "disconnect" && !client_->isConnectedToHost()) {
            response->success = true;
            response->message = "disconnected";
            RCLCPP_INFO(node_->get_logger(), "Disconnect requested while MQTT is already disconnected");
            return;
        }

        if (action == "connect") {
            if (client_->isConnectedToHost() && current_client_id_ == client_id) {
                response->success = true;
                response->message = "connected";
                RCLCPP_INFO(node_->get_logger(), "Already connected with client_id=%s",
                            current_client_id_.toStdString().c_str());
                return;
            }

            if (client_->isConnectedToHost()) {
                QString observed_state;
                mqtt_connecting_ = true;
                if (!waitForClientStateAfterAction(
                        "disconnected",
                        kTimeoutMs,
                        [&]() { client_->disconnectFromHost(); },
                        &observed_state)) {
                    mqtt_connecting_ = false;
                    response->success = false;
                    response->message = observed_state.startsWith("error:")
                                            ? observed_state.toStdString()
                                            : std::string("error: disconnect timeout");
                    return;
                }
            }

            current_client_id_ = client_id;
            client_->setClientId(current_client_id_);
            mqtt_connecting_ = true;

            QString observed_state;
            if (!waitForClientStateAfterAction(
                    "connected",
                    kTimeoutMs,
                    [&]() { client_->connectToHost(); },
                    &observed_state)) {
                if (client_->isConnectedToHost()) {
                    mqtt_connecting_ = true;
                    client_->disconnectFromHost();
                }
                mqtt_connecting_ = false;
                response->success = false;
                response->message = observed_state.startsWith("error:")
                                        ? observed_state.toStdString()
                                        : std::string("error: connect timeout");
                return;
            }

            response->success = true;
            response->message = "connected";
            RCLCPP_INFO(node_->get_logger(), "Connect requested, client_id=%s",
                        current_client_id_.toStdString().c_str());
            return;
        }

        mqtt_connecting_ = true;
        QString observed_state;
        if (!waitForClientStateAfterAction(
                "disconnected",
                kTimeoutMs,
                [&]() { client_->disconnectFromHost(); },
                &observed_state)) {
            mqtt_connecting_ = false;
            response->success = false;
            response->message = observed_state.startsWith("error:")
                                    ? observed_state.toStdString()
                                    : std::string("error: disconnect timeout");
            return;
        }

        response->success = true;
        response->message = "disconnected";
        RCLCPP_INFO(node_->get_logger(), "Disconnect requested for client_id=%s",
                    current_client_id_.toStdString().c_str());
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
    bool waitForClientStateAfterAction(const QString &expected_state,
                                       int timeout_ms,
                                       const std::function<void()> &action,
                                       QString *observed_state)
    {
        if (expected_state == "connected" && client_->isConnectedToHost()) {
            if (observed_state) {
                *observed_state = "connected";
            }
            return true;
        }
        if (expected_state == "disconnected" && !client_->isConnectedToHost() && !mqtt_connecting_) {
            if (observed_state) {
                *observed_state = "disconnected";
            }
            return true;
        }

        QEventLoop loop;
        QTimer timer;
        QString state;

        const auto connected_connection = QObject::connect(
            client_, &QMQTT::Client::connected, &loop, [&]() {
                state = "connected";
                loop.quit();
            });
        const auto disconnected_connection = QObject::connect(
            client_, &QMQTT::Client::disconnected, &loop, [&]() {
                state = "disconnected";
                loop.quit();
            });
        QObject::connect(&timer, &QTimer::timeout, &loop, [&]() {
            state = "error: timeout";
            loop.quit();
        });

        timer.setSingleShot(true);
        timer.start(timeout_ms);
        action();
        loop.exec();

        QObject::disconnect(connected_connection);
        QObject::disconnect(disconnected_connection);

        if (observed_state) {
            *observed_state = state;
        }
        return state == expected_state;
    }

    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr publisher_;
    rclcpp::Service<video_interfaces::srv::RobotLogin>::SharedPtr mqtt_control_service_;
    QMQTT::Client *client_ = nullptr;
    QString broker_host_;
    quint16 broker_port_ = 0;
    QString mqtt_username_;
    QString current_client_id_;
    QString topic_;
    bool mqtt_connecting_ = false;
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
