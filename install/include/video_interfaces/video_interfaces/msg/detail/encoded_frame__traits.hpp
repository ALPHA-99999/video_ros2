// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from video_interfaces:msg/EncodedFrame.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__TRAITS_HPP_
#define VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "video_interfaces/msg/detail/encoded_frame__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace video_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const EncodedFrame & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: source
  {
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << ", ";
  }

  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: frame_size
  {
    out << "frame_size: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_size, out);
    out << ", ";
  }

  // member: codec
  {
    out << "codec: ";
    rosidl_generator_traits::value_to_yaml(msg.codec, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EncodedFrame & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << "\n";
  }

  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: frame_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_size: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_size, out);
    out << "\n";
  }

  // member: codec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "codec: ";
    rosidl_generator_traits::value_to_yaml(msg.codec, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EncodedFrame & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace video_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use video_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const video_interfaces::msg::EncodedFrame & msg,
  std::ostream & out, size_t indentation = 0)
{
  video_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use video_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const video_interfaces::msg::EncodedFrame & msg)
{
  return video_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<video_interfaces::msg::EncodedFrame>()
{
  return "video_interfaces::msg::EncodedFrame";
}

template<>
inline const char * name<video_interfaces::msg::EncodedFrame>()
{
  return "video_interfaces/msg/EncodedFrame";
}

template<>
struct has_fixed_size<video_interfaces::msg::EncodedFrame>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<video_interfaces::msg::EncodedFrame>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<video_interfaces::msg::EncodedFrame>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__TRAITS_HPP_
