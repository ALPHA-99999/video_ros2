// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from video_interfaces:msg/EncodedFrame.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__BUILDER_HPP_
#define VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "video_interfaces/msg/detail/encoded_frame__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace video_interfaces
{

namespace msg
{

namespace builder
{

class Init_EncodedFrame_data
{
public:
  explicit Init_EncodedFrame_data(::video_interfaces::msg::EncodedFrame & msg)
  : msg_(msg)
  {}
  ::video_interfaces::msg::EncodedFrame data(::video_interfaces::msg::EncodedFrame::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

class Init_EncodedFrame_codec
{
public:
  explicit Init_EncodedFrame_codec(::video_interfaces::msg::EncodedFrame & msg)
  : msg_(msg)
  {}
  Init_EncodedFrame_data codec(::video_interfaces::msg::EncodedFrame::_codec_type arg)
  {
    msg_.codec = std::move(arg);
    return Init_EncodedFrame_data(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

class Init_EncodedFrame_frame_size
{
public:
  explicit Init_EncodedFrame_frame_size(::video_interfaces::msg::EncodedFrame & msg)
  : msg_(msg)
  {}
  Init_EncodedFrame_codec frame_size(::video_interfaces::msg::EncodedFrame::_frame_size_type arg)
  {
    msg_.frame_size = std::move(arg);
    return Init_EncodedFrame_codec(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

class Init_EncodedFrame_frame_id
{
public:
  explicit Init_EncodedFrame_frame_id(::video_interfaces::msg::EncodedFrame & msg)
  : msg_(msg)
  {}
  Init_EncodedFrame_frame_size frame_id(::video_interfaces::msg::EncodedFrame::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_EncodedFrame_frame_size(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

class Init_EncodedFrame_source
{
public:
  explicit Init_EncodedFrame_source(::video_interfaces::msg::EncodedFrame & msg)
  : msg_(msg)
  {}
  Init_EncodedFrame_frame_id source(::video_interfaces::msg::EncodedFrame::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_EncodedFrame_frame_id(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

class Init_EncodedFrame_header
{
public:
  Init_EncodedFrame_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EncodedFrame_source header(::video_interfaces::msg::EncodedFrame::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_EncodedFrame_source(msg_);
  }

private:
  ::video_interfaces::msg::EncodedFrame msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::video_interfaces::msg::EncodedFrame>()
{
  return video_interfaces::msg::builder::Init_EncodedFrame_header();
}

}  // namespace video_interfaces

#endif  // VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__BUILDER_HPP_
