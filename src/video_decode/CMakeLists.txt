cmake_minimum_required(VERSION 3.16)
project(video_decode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(video_interfaces REQUIRED)

if(WIN32)
  set(VCPKG_ROOT_HINT "$ENV{VCPKG_ROOT}")
  if(NOT VCPKG_ROOT_HINT)
    set(VCPKG_ROOT_HINT "D:/GitHub/vcpkg")
  endif()
  set(FFMPEG_ROOT "${VCPKG_ROOT_HINT}/packages/ffmpeg_x64-windows")

  find_path(FFMPEG_INCLUDE_DIR libavcodec/avcodec.h PATHS "${FFMPEG_ROOT}/include" NO_DEFAULT_PATH REQUIRED)
  find_library(AVCODEC_LIBRARY avcodec PATHS "${FFMPEG_ROOT}/lib" NO_DEFAULT_PATH REQUIRED)
  find_library(AVFORMAT_LIBRARY avformat PATHS "${FFMPEG_ROOT}/lib" NO_DEFAULT_PATH REQUIRED)
  find_library(AVUTIL_LIBRARY avutil PATHS "${FFMPEG_ROOT}/lib" NO_DEFAULT_PATH REQUIRED)
  find_library(SWSCALE_LIBRARY swscale PATHS "${FFMPEG_ROOT}/lib" NO_DEFAULT_PATH REQUIRED)
else()
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(LIBAVCODEC REQUIRED IMPORTED_TARGET libavcodec)
  pkg_check_modules(LIBAVFORMAT REQUIRED IMPORTED_TARGET libavformat)
  pkg_check_modules(LIBAVUTIL REQUIRED IMPORTED_TARGET libavutil)
  pkg_check_modules(LIBSWSCALE REQUIRED IMPORTED_TARGET libswscale)
endif()

add_executable(decoder_node
  src/hevc_decoder.cpp
  src/decoder_node.cpp
)
target_include_directories(decoder_node PRIVATE include)
if(WIN32)
  target_include_directories(decoder_node PRIVATE ${FFMPEG_INCLUDE_DIR})
  target_link_libraries(decoder_node
    ${AVCODEC_LIBRARY}
    ${AVFORMAT_LIBRARY}
    ${AVUTIL_LIBRARY}
    ${SWSCALE_LIBRARY}
    user32 secur32 bcrypt ws2_32
  )
else()
  target_link_libraries(decoder_node
    PkgConfig::LIBAVCODEC
    PkgConfig::LIBAVFORMAT
    PkgConfig::LIBAVUTIL
    PkgConfig::LIBSWSCALE
  )
endif()
ament_target_dependencies(decoder_node rclcpp sensor_msgs video_interfaces)

install(TARGETS decoder_node RUNTIME DESTINATION lib/${PROJECT_NAME})
if(WIN32)
  install(DIRECTORY "${FFMPEG_ROOT}/bin/" DESTINATION lib/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.dll")
endif()

ament_package()
