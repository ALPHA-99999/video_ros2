# video_ros2

ROS 2 workspace for the `video` client refactor.

## Architecture
- `video_interfaces`: shared ROS 2 messages
- `video_ingest`: UDP/MQTT adapters that publish encoded HEVC frames
- `video_decode`: FFmpeg HEVC decoder node that publishes `sensor_msgs/Image`
- `video_viewer_qt`: Qt viewer node that subscribes to decoded RGB images
- `third_party_qmqtt`: copied QMQTT headers and binaries from the legacy project

## Build
1. Install a ROS 2 desktop distribution for Windows and source its environment.
2. Ensure Qt6, FFmpeg, protobuf, and the QMQTT binary dependencies are available.
3. From this workspace root run:

```powershell
colcon build --merge-install --cmake-args -DCMAKE_BUILD_TYPE=Release
```

## Notes
- This machine did not have `ros2` / `colcon` available during implementation, so the workspace is created but not build-verified here.
- Legacy project at `C:\Users\24981\Desktop\UI\video` is left untouched.