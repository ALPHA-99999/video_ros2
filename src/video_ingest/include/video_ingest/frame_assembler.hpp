#pragma once

#include <QByteArray>
#include <QDateTime>
#include <QMap>
#include <QVector>
#include <algorithm>
#include <optional>

namespace video_ingest {

struct AssembledFrame {
    QByteArray data;
    quint16 frame_id = 0;
    quint32 frame_size = 0;
    qint64 first_recv_ms = 0;
    qint64 assembled_ms = 0;
};

class FrameAssembler {
public:
    std::optional<AssembledFrame> ingest(quint16 frame_id,
                                         quint16 fragment_id,
                                         quint32 frame_size,
                                         const QByteArray &fragment,
                                         qint64 recv_ms)
    {
        if (frame_size == 0 || frame_size > kMaxFrameSize) {
            return std::nullopt;
        }

        cleanupExpired(recv_ms);
        buffers_[frame_id][fragment_id] = fragment;
        if (!frame_sizes_.contains(frame_id)) {
            frame_sizes_[frame_id] = frame_size;
        }
        if (!first_recv_ms_.contains(frame_id)) {
            first_recv_ms_[frame_id] = recv_ms;
        }

        quint32 received_size = 0;
        const auto &fragments = buffers_[frame_id];
        for (auto it = fragments.constBegin(); it != fragments.constEnd(); ++it) {
            received_size += static_cast<quint32>(it.value().size());
        }
        if (received_size < frame_size) {
            return std::nullopt;
        }

        QByteArray complete;
        complete.reserve(static_cast<int>(frame_size));
        QVector<quint16> ids;
        ids.reserve(fragments.size());
        for (auto it = fragments.constBegin(); it != fragments.constEnd(); ++it) {
            ids.push_back(it.key());
        }
        std::sort(ids.begin(), ids.end());
        for (quint16 id : ids) {
            complete.append(fragments[id]);
            if (complete.size() >= static_cast<int>(frame_size)) {
                complete.resize(static_cast<int>(frame_size));
                break;
            }
        }
        if (complete.size() != static_cast<int>(frame_size)) {
            return std::nullopt;
        }

        AssembledFrame result;
        result.data = complete;
        result.frame_id = frame_id;
        result.frame_size = frame_size;
        result.first_recv_ms = first_recv_ms_.value(frame_id, recv_ms);
        result.assembled_ms = QDateTime::currentMSecsSinceEpoch();

        buffers_.remove(frame_id);
        frame_sizes_.remove(frame_id);
        first_recv_ms_.remove(frame_id);
        return result;
    }

    void cleanupExpired(qint64 now_ms)
    {
        QVector<quint16> expired;
        for (auto it = first_recv_ms_.constBegin(); it != first_recv_ms_.constEnd(); ++it) {
            if (now_ms - it.value() > kFrameTimeoutMs) {
                expired.push_back(it.key());
            }
        }
        for (quint16 frame_id : expired) {
            buffers_.remove(frame_id);
            frame_sizes_.remove(frame_id);
            first_recv_ms_.remove(frame_id);
        }
    }

private:
    static constexpr quint32 kMaxFrameSize = 10 * 1024 * 1024;
    static constexpr qint64 kFrameTimeoutMs = 250;

    QMap<quint16, QMap<quint16, QByteArray>> buffers_;
    QMap<quint16, quint32> frame_sizes_;
    QMap<quint16, qint64> first_recv_ms_;
};

}  // namespace video_ingest