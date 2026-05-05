cmake_minimum_required(VERSION 3.16)
project(mqtt_bridge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(video_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Network)
find_package(Protobuf REQUIRED)

set(qmqtt_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../third_party_qmqtt/qmqtt")
add_subdirectory("${qmqtt_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/third_party_qmqtt/qmqtt")

set(MQTT_PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proto/command.proto")
set(MQTT_PROTO_SRC "${CMAKE_CURRENT_BINARY_DIR}/command.pb.cc")
set(MQTT_PROTO_HDR "${CMAKE_CURRENT_BINARY_DIR}/command.pb.h")

add_custom_command(
  OUTPUT "${MQTT_PROTO_SRC}" "${MQTT_PROTO_HDR}"
  COMMAND "${Protobuf_PROTOC_EXECUTABLE}"
          --experimental_allow_proto3_optional
          --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
          -I "${CMAKE_CURRENT_SOURCE_DIR}/proto"
          "${MQTT_PROTO_FILE}"
  DEPENDS "${MQTT_PROTO_FILE}"
  COMMENT "Generating protobuf sources for mqtt_bridge"
  VERBATIM
)

add_executable(mqtt_bridge_node
  src/mqtt_bridge_node.cpp
  "${MQTT_PROTO_SRC}"
)
target_include_directories(mqtt_bridge_node PRIVATE
  proto
  ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(mqtt_bridge_node
  Qt6::Core
  Qt6::Network
  qmqtt
  ${Protobuf_LIBRARIES}
)
ament_target_dependencies(mqtt_bridge_node rclcpp video_interfaces std_msgs)

install(TARGETS mqtt_bridge_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_package()
