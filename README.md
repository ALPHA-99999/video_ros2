# video_ros2

ROS 2 workspace for the `video` client refactor, updated for Ubuntu.

## Architecture
- `video_interfaces`: shared ROS 2 messages
- `video_ingest`: UDP adapter that publishes encoded HEVC frames
- `mqtt_bridge`: MQTT + protobuf bridge that publishes raw byte blocks into ROS
- `custom_byteblock`: HEVC byte-block assembler for MQTT-fed streams
- `video_decode`: FFmpeg HEVC decoder node that publishes `sensor_msgs/Image`
- `video_viewer_qt`: Qt viewer node that subscribes to decoded RGB images
- `third_party_qmqtt`: bundled QMQTT source used by `mqtt_bridge`

## Ubuntu build
1. Install ROS 2 Desktop for Ubuntu and source it.
2. Install build dependencies:

```bash
sudo apt update
sudo apt install -y \
  build-essential cmake pkg-config protobuf-compiler libprotobuf-dev \
  ffmpeg libavcodec-dev libavformat-dev libavutil-dev libswscale-dev \
  qt6-base-dev
```

3. Build from the workspace root:

```bash
./scripts/build_ros2.sh
```

## Run three tasks
The helper script starts the UDP path by default: ingest, decode, and viewer.

```bash
./scripts/run_three_tasks.sh
```

MQTT mode starts `mqtt_bridge`, `custom_byteblock`, `video_decode`, and `video_viewer_qt`:

```bash
./scripts/run_three_tasks.sh mqtt
```

Extra ROS arguments for the ingest node can be passed after `--`:

```bash
./scripts/run_three_tasks.sh udp -- --ros-args -p port:=3334
```

## Notes
- Default mode is `udp`; the three tasks are `video_ingest`, `video_decode`, and `video_viewer_qt`.
- MQTT mode uses the separate `mqtt_bridge` and `custom_byteblock` packages, with protobuf handled inside `mqtt_bridge`.
- If the workspace lives under a non-ASCII path such as a Chinese directory name, the helper scripts automatically build and run through `/tmp/video_ros2_ws` to avoid a `rosidl` path bug seen on ROS 2 Humble.
- This machine did not have `ros2` or `colcon` installed, so the Ubuntu changes were updated statically and not fully build-verified here.
