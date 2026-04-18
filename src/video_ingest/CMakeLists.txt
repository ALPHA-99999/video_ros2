cmake_minimum_required(VERSION 3.16)
project(video_ingest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(video_interfaces REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(QMQTT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../third_party_qmqtt")
add_library(qmqtt SHARED IMPORTED GLOBAL)
set_target_properties(qmqtt PROPERTIES
  IMPORTED_IMPLIB "${QMQTT_ROOT}/lib/Qt6Qmqtt.lib"
  IMPORTED_LOCATION "${QMQTT_ROOT}/bin/Qt6Qmqtt.dll"
  INTERFACE_INCLUDE_DIRECTORIES "${QMQTT_ROOT}/include"
)

add_executable(udp_ingest_node
  src/udp_ingest_node.cpp
)
target_include_directories(udp_ingest_node PRIVATE include)
target_link_libraries(udp_ingest_node PRIVATE Qt6::Core Qt6::Network)
ament_target_dependencies(udp_ingest_node rclcpp video_interfaces)

add_executable(mqtt_ingest_node
  src/mqtt_ingest_node.cpp
  src/generated/command.pb.cc
)
target_include_directories(mqtt_ingest_node PRIVATE include src/generated)
target_link_libraries(mqtt_ingest_node PRIVATE Qt6::Core Qt6::Network Protobuf::libprotobuf qmqtt)
ament_target_dependencies(mqtt_ingest_node rclcpp video_interfaces)

install(TARGETS udp_ingest_node mqtt_ingest_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
install(FILES
  ${QMQTT_ROOT}/bin/Qt6Qmqtt.dll
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()