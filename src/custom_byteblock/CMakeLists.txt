cmake_minimum_required(VERSION 3.16)
project(custom_byteblock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(video_interfaces REQUIRED)

add_executable(custom_byteblock_node
  src/custom_byteblock_node.cpp
)
target_include_directories(custom_byteblock_node PRIVATE include)
ament_target_dependencies(custom_byteblock_node rclcpp video_interfaces)

install(TARGETS custom_byteblock_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_package()
