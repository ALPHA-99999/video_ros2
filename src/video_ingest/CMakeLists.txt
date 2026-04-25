cmake_minimum_required(VERSION 3.16)
project(video_ingest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(video_interfaces REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(udp_ingest_node
  src/udp_ingest_node.cpp
)
target_include_directories(udp_ingest_node PRIVATE include)
target_link_libraries(udp_ingest_node Qt6::Core Qt6::Network)
ament_target_dependencies(udp_ingest_node rclcpp video_interfaces)

install(TARGETS udp_ingest_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_package()
