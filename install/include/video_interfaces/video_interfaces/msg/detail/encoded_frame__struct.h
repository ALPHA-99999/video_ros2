// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from video_interfaces:msg/EncodedFrame.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_H_
#define VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'source'
// Member 'codec'
#include "rosidl_runtime_c/string.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/EncodedFrame in the package video_interfaces.
typedef struct video_interfaces__msg__EncodedFrame
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String source;
  uint32_t frame_id;
  uint32_t frame_size;
  rosidl_runtime_c__String codec;
  rosidl_runtime_c__uint8__Sequence data;
} video_interfaces__msg__EncodedFrame;

// Struct for a sequence of video_interfaces__msg__EncodedFrame.
typedef struct video_interfaces__msg__EncodedFrame__Sequence
{
  video_interfaces__msg__EncodedFrame * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} video_interfaces__msg__EncodedFrame__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_H_
