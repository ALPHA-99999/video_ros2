// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from video_interfaces:srv/RobotLogin.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_HPP_
#define VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__video_interfaces__srv__RobotLogin_Request __attribute__((deprecated))
#else
# define DEPRECATED__video_interfaces__srv__RobotLogin_Request __declspec(deprecated)
#endif

namespace video_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotLogin_Request_
{
  using Type = RobotLogin_Request_<ContainerAllocator>;

  explicit RobotLogin_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
      this->client_id = "";
    }
  }

  explicit RobotLogin_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_alloc),
    client_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
      this->client_id = "";
    }
  }

  // field types and members
  using _action_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _action_type action;
  using _client_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _client_id_type client_id;

  // setters for named parameter idiom
  Type & set__action(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->action = _arg;
    return *this;
  }
  Type & set__client_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->client_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__video_interfaces__srv__RobotLogin_Request
    std::shared_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__video_interfaces__srv__RobotLogin_Request
    std::shared_ptr<video_interfaces::srv::RobotLogin_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotLogin_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    if (this->client_id != other.client_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotLogin_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotLogin_Request_

// alias to use template instance with default allocator
using RobotLogin_Request =
  video_interfaces::srv::RobotLogin_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace video_interfaces


#ifndef _WIN32
# define DEPRECATED__video_interfaces__srv__RobotLogin_Response __attribute__((deprecated))
#else
# define DEPRECATED__video_interfaces__srv__RobotLogin_Response __declspec(deprecated)
#endif

namespace video_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotLogin_Response_
{
  using Type = RobotLogin_Response_<ContainerAllocator>;

  explicit RobotLogin_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit RobotLogin_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__video_interfaces__srv__RobotLogin_Response
    std::shared_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__video_interfaces__srv__RobotLogin_Response
    std::shared_ptr<video_interfaces::srv::RobotLogin_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotLogin_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotLogin_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotLogin_Response_

// alias to use template instance with default allocator
using RobotLogin_Response =
  video_interfaces::srv::RobotLogin_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace video_interfaces

namespace video_interfaces
{

namespace srv
{

struct RobotLogin
{
  using Request = video_interfaces::srv::RobotLogin_Request;
  using Response = video_interfaces::srv::RobotLogin_Response;
};

}  // namespace srv

}  // namespace video_interfaces

#endif  // VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__STRUCT_HPP_
