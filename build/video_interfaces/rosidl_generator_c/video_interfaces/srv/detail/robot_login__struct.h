// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from video_interfaces:srv/RobotLogin.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_H_
#define VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'action'
// Member 'client_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RobotLogin in the package video_interfaces.
typedef struct video_interfaces__srv__RobotLogin_Request
{
  rosidl_runtime_c__String action;
  rosidl_runtime_c__String client_id;
} video_interfaces__srv__RobotLogin_Request;

// Struct for a sequence of video_interfaces__srv__RobotLogin_Request.
typedef struct video_interfaces__srv__RobotLogin_Request__Sequence
{
  video_interfaces__srv__RobotLogin_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} video_interfaces__srv__RobotLogin_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RobotLogin in the package video_interfaces.
typedef struct video_interfaces__srv__RobotLogin_Response
{
  bool success;
  rosidl_runtime_c__String message;
} video_interfaces__srv__RobotLogin_Response;

// Struct for a sequence of video_interfaces__srv__RobotLogin_Response.
typedef struct video_interfaces__srv__RobotLogin_Response__Sequence
{
  video_interfaces__srv__RobotLogin_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} video_interfaces__srv__RobotLogin_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_H_
