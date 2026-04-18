# video_ros2 Architecture

## Data flow
1. `udp_ingest_node` or `mqtt_ingest_node` receives fragmented HEVC payloads from the legacy sender.
2. Fragments are reassembled into complete encoded frames and published on `video/encoded`.
3. `decoder_node` subscribes to `video/encoded`, decodes HEVC with FFmpeg, and publishes `video/rgb` as `sensor_msgs/Image` (`rgb8`).
4. `video_viewer_qt` subscribes to `video/rgb` and renders frames in a Qt window.

## Topics
- `video/encoded` (`video_interfaces/msg/EncodedFrame`)
- `video/rgb` (`sensor_msgs/msg/Image`)

## Legacy compatibility
- UDP framing stays byte-compatible with the current sender.
- MQTT path still expects topic `CustomByteBlock` with payload packed through `robomaster.CustomByteBlock` protobuf.