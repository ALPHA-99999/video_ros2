cmake_minimum_required(VERSION 3.16)
project(video_viewer_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(video_viewer_qt
  include/video_viewer_qt/image_widget.hpp
  include/video_viewer_qt/viewer_window.hpp
  src/main.cpp
  src/image_widget.cpp
  src/viewer_window.cpp
)
target_include_directories(video_viewer_qt PRIVATE include)
target_link_libraries(video_viewer_qt Qt6::Core Qt6::Gui Qt6::Widgets)
ament_target_dependencies(video_viewer_qt rclcpp sensor_msgs)

install(TARGETS video_viewer_qt RUNTIME DESTINATION lib/${PROJECT_NAME})
ament_package()
