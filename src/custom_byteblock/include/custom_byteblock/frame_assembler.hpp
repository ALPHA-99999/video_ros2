#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace custom_byteblock {

struct AssembledFrame {
    std::vector<std::uint8_t> data;
    std::uint16_t frame_id = 0;
    std::uint32_t frame_size = 0;
    std::int64_t first_recv_ms = 0;
    std::int64_t assembled_ms = 0;
};

class FrameAssembler {
public:
    std::optional<AssembledFrame> ingest(std::uint16_t frame_id,
                                         std::uint16_t fragment_id,
                                         std::uint32_t frame_size,
                                         const std::vector<std::uint8_t> &fragment,
                                         std::int64_t recv_ms)
    {
        if (frame_size == 0 || frame_size > kMaxFrameSize) {
            return std::nullopt;
        }

        cleanupExpired(recv_ms);
        buffers_[frame_id][fragment_id] = fragment;
        if (!frame_sizes_.count(frame_id)) {
            frame_sizes_[frame_id] = frame_size;
        }
        if (!first_recv_ms_.count(frame_id)) {
            first_recv_ms_[frame_id] = recv_ms;
        }

        std::uint32_t received_size = 0;
        const auto &fragments = buffers_[frame_id];
        for (const auto &entry : fragments) {
            received_size += static_cast<std::uint32_t>(entry.second.size());
        }
        if (received_size < frame_size) {
            return std::nullopt;
        }

        std::vector<std::uint16_t> ids;
        ids.reserve(fragments.size());
        for (const auto &entry : fragments) {
            ids.push_back(entry.first);
        }
        std::sort(ids.begin(), ids.end());

        std::vector<std::uint8_t> complete;
        complete.reserve(static_cast<std::size_t>(frame_size));
        for (auto id : ids) {
            const auto &part = fragments.at(id);
            complete.insert(complete.end(), part.begin(), part.end());
            if (complete.size() >= frame_size) {
                complete.resize(static_cast<std::size_t>(frame_size));
                break;
            }
        }
        if (complete.size() != frame_size) {
            return std::nullopt;
        }

        AssembledFrame result;
        result.data = std::move(complete);
        result.frame_id = frame_id;
        result.frame_size = frame_size;
        result.first_recv_ms = first_recv_ms_.count(frame_id) ? first_recv_ms_[frame_id] : recv_ms;
        result.assembled_ms = recv_ms;

        buffers_.erase(frame_id);
        frame_sizes_.erase(frame_id);
        first_recv_ms_.erase(frame_id);
        return result;
    }

    void cleanupExpired(std::int64_t now_ms)
    {
        std::vector<std::uint16_t> expired;
        for (const auto &entry : first_recv_ms_) {
            if (now_ms - entry.second > kFrameTimeoutMs) {
                expired.push_back(entry.first);
            }
        }
        for (auto frame_id : expired) {
            buffers_.erase(frame_id);
            frame_sizes_.erase(frame_id);
            first_recv_ms_.erase(frame_id);
        }
    }

private:
    static constexpr std::uint32_t kMaxFrameSize = 10 * 1024 * 1024;
    static constexpr std::int64_t kFrameTimeoutMs = 250;

    std::map<std::uint16_t, std::map<std::uint16_t, std::vector<std::uint8_t>>> buffers_;
    std::map<std::uint16_t, std::uint32_t> frame_sizes_;
    std::map<std::uint16_t, std::int64_t> first_recv_ms_;
};

}  // namespace custom_byteblock
