#include <QCoreApplication>
#include <QDateTime>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QObject>
#include <QElapsedTimer>
#include <QTimer>
#include <QUdpSocket>

#include <rclcpp/rclcpp.hpp>
#include <video_interfaces/msg/encoded_frame.hpp>

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

class UdpIngestNode : public QObject {
    Q_OBJECT
public:
    UdpIngestNode(QObject *parent = nullptr)
        : QObject(parent),
          node_(std::make_shared<rclcpp::Node>("udp_ingest_node")),
          publisher_(node_->create_publisher<video_interfaces::msg::EncodedFrame>("video/encoded", 10)),
          socket_(new QUdpSocket(this))
    {
        fps_timer_.start();
        const auto port = node_->declare_parameter<int>("port", 3334);
        if (!socket_->bind(QHostAddress::Any, static_cast<quint16>(port), QUdpSocket::ShareAddress)) {
            RCLCPP_ERROR(node_->get_logger(), "Failed to bind UDP port %ld: %s", port, socket_->errorString().toStdString().c_str());
        } else {
            socket_->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 3080 * 2160 * 10);
            connect(socket_, &QUdpSocket::readyRead, this, &UdpIngestNode::readPendingDatagrams);
            RCLCPP_INFO(node_->get_logger(), "Listening for UDP HEVC fragments on port %ld", port);
        }
    }

    rclcpp::Node::SharedPtr node() const { return node_; }

private slots:
    void readPendingDatagrams()
    {
        while (socket_->hasPendingDatagrams()) {
            const qint64 recv_ms = QDateTime::currentMSecsSinceEpoch();
            const auto datagram = socket_->receiveDatagram();
            const QByteArray data = datagram.data();     
            if (data.size() <= 8) {
                continue;
            }

            const FrameHeader header = parseHeader(data);
            ++datagram_count_;
            const auto assembled = assembler_.ingest(header.frame_id,
                                                     header.fragment_id,
                                                     header.frame_size,
                                                     data.mid(8),
                                                     recv_ms);
            if (!assembled) {
                continue;
            }

            ++assembled_frame_count_;
            ++assembled_frames_this_second_;
            logFpsIfDue();

            video_interfaces::msg::EncodedFrame msg;
            msg.header.stamp = node_->now();
            msg.header.frame_id = "udp";
            msg.source = "udp";
            msg.frame_id = assembled->frame_id;
            msg.frame_size = assembled->frame_size;
            msg.codec = "hevc";
            msg.data.assign(assembled->data.begin(), assembled->data.end());
            publisher_->publish(std::move(msg));
        }
    }

private:
    void logFpsIfDue()
    {
        const qint64 elapsed_ms = fps_timer_.elapsed();
        if (elapsed_ms < 1000) {
            return;
        }

        const double fps = static_cast<double>(assembled_frames_this_second_) * 1000.0 /
                           static_cast<double>(elapsed_ms);
        RCLCPP_INFO(node_->get_logger(),
                    "Assembled FPS: %.2f total_frames=%llu total_datagrams=%llu",
                    fps,
                    static_cast<unsigned long long>(assembled_frame_count_),
                    static_cast<unsigned long long>(datagram_count_));
        assembled_frames_this_second_ = 0;
        fps_timer_.restart();
    }

    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<video_interfaces::msg::EncodedFrame>::SharedPtr publisher_;
    QUdpSocket *socket_ = nullptr;
    video_ingest::FrameAssembler assembler_;
    std::uint64_t datagram_count_ = 0;
    std::uint64_t assembled_frame_count_ = 0;
    std::uint64_t assembled_frames_this_second_ = 0;
    QElapsedTimer fps_timer_;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    rclcpp::init(argc, argv);

    UdpIngestNode ingest;
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

#include "udp_ingest_node.moc"
