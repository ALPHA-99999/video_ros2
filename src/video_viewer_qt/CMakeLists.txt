cmake_minimum_required(VERSION 3.16)
project(video_viewer_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(video_interfaces REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_executable(video_viewer_qt
  include/video_viewer_qt/viewer_backend.hpp
  include/video_viewer_qt/viewer_image_provider.hpp
  src/main.cpp
  src/viewer_backend.cpp
  src/viewer_image_provider.cpp
  src/qml.qrc
)
target_include_directories(video_viewer_qt PRIVATE include)
target_link_libraries(video_viewer_qt Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)
ament_target_dependencies(video_viewer_qt rclcpp sensor_msgs video_interfaces)

install(TARGETS video_viewer_qt RUNTIME DESTINATION lib/${PROJECT_NAME})
ament_package()
