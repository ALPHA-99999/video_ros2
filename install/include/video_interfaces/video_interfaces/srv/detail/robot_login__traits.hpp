// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from video_interfaces:srv/RobotLogin.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__TRAITS_HPP_
#define VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "video_interfaces/srv/detail/robot_login__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace video_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotLogin_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: action
  {
    out << "action: ";
    rosidl_generator_traits::value_to_yaml(msg.action, out);
    out << ", ";
  }

  // member: client_id
  {
    out << "client_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotLogin_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: action
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "action: ";
    rosidl_generator_traits::value_to_yaml(msg.action, out);
    out << "\n";
  }

  // member: client_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "client_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotLogin_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace video_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use video_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const video_interfaces::srv::RobotLogin_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  video_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use video_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const video_interfaces::srv::RobotLogin_Request & msg)
{
  return video_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<video_interfaces::srv::RobotLogin_Request>()
{
  return "video_interfaces::srv::RobotLogin_Request";
}

template<>
inline const char * name<video_interfaces::srv::RobotLogin_Request>()
{
  return "video_interfaces/srv/RobotLogin_Request";
}

template<>
struct has_fixed_size<video_interfaces::srv::RobotLogin_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<video_interfaces::srv::RobotLogin_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<video_interfaces::srv::RobotLogin_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace video_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotLogin_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotLogin_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotLogin_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace video_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use video_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const video_interfaces::srv::RobotLogin_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  video_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use video_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const video_interfaces::srv::RobotLogin_Response & msg)
{
  return video_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<video_interfaces::srv::RobotLogin_Response>()
{
  return "video_interfaces::srv::RobotLogin_Response";
}

template<>
inline const char * name<video_interfaces::srv::RobotLogin_Response>()
{
  return "video_interfaces/srv/RobotLogin_Response";
}

template<>
struct has_fixed_size<video_interfaces::srv::RobotLogin_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<video_interfaces::srv::RobotLogin_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<video_interfaces::srv::RobotLogin_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<video_interfaces::srv::RobotLogin>()
{
  return "video_interfaces::srv::RobotLogin";
}

template<>
inline const char * name<video_interfaces::srv::RobotLogin>()
{
  return "video_interfaces/srv/RobotLogin";
}

template<>
struct has_fixed_size<video_interfaces::srv::RobotLogin>
  : std::integral_constant<
    bool,
    has_fixed_size<video_interfaces::srv::RobotLogin_Request>::value &&
    has_fixed_size<video_interfaces::srv::RobotLogin_Response>::value
  >
{
};

template<>
struct has_bounded_size<video_interfaces::srv::RobotLogin>
  : std::integral_constant<
    bool,
    has_bounded_size<video_interfaces::srv::RobotLogin_Request>::value &&
    has_bounded_size<video_interfaces::srv::RobotLogin_Response>::value
  >
{
};

template<>
struct is_service<video_interfaces::srv::RobotLogin>
  : std::true_type
{
};

template<>
struct is_service_request<video_interfaces::srv::RobotLogin_Request>
  : std::true_type
{
};

template<>
struct is_service_response<video_interfaces::srv::RobotLogin_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__TRAITS_HPP_
