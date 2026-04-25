// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from video_interfaces:msg/EncodedFrame.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_HPP_
#define VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__video_interfaces__msg__EncodedFrame __attribute__((deprecated))
#else
# define DEPRECATED__video_interfaces__msg__EncodedFrame __declspec(deprecated)
#endif

namespace video_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EncodedFrame_
{
  using Type = EncodedFrame_<ContainerAllocator>;

  explicit EncodedFrame_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->frame_id = 0ul;
      this->frame_size = 0ul;
      this->codec = "";
    }
  }

  explicit EncodedFrame_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    source(_alloc),
    codec(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->frame_id = 0ul;
      this->frame_size = 0ul;
      this->codec = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;
  using _frame_id_type =
    uint32_t;
  _frame_id_type frame_id;
  using _frame_size_type =
    uint32_t;
  _frame_size_type frame_size;
  using _codec_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _codec_type codec;
  using _data_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source = _arg;
    return *this;
  }
  Type & set__frame_id(
    const uint32_t & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__frame_size(
    const uint32_t & _arg)
  {
    this->frame_size = _arg;
    return *this;
  }
  Type & set__codec(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->codec = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    video_interfaces::msg::EncodedFrame_<ContainerAllocator> *;
  using ConstRawPtr =
    const video_interfaces::msg::EncodedFrame_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      video_interfaces::msg::EncodedFrame_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      video_interfaces::msg::EncodedFrame_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__video_interfaces__msg__EncodedFrame
    std::shared_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__video_interfaces__msg__EncodedFrame
    std::shared_ptr<video_interfaces::msg::EncodedFrame_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EncodedFrame_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->frame_size != other.frame_size) {
      return false;
    }
    if (this->codec != other.codec) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const EncodedFrame_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EncodedFrame_

// alias to use template instance with default allocator
using EncodedFrame =
  video_interfaces::msg::EncodedFrame_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace video_interfaces

#endif  // VIDEO_INTERFACES__MSG__DETAIL__ENCODED_FRAME__STRUCT_HPP_
