// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from video_interfaces:srv/RobotLogin.idl
// generated code does not contain a copyright notice

#ifndef VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__BUILDER_HPP_
#define VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "video_interfaces/srv/detail/robot_login__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace video_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotLogin_Request_client_id
{
public:
  explicit Init_RobotLogin_Request_client_id(::video_interfaces::srv::RobotLogin_Request & msg)
  : msg_(msg)
  {}
  ::video_interfaces::srv::RobotLogin_Request client_id(::video_interfaces::srv::RobotLogin_Request::_client_id_type arg)
  {
    msg_.client_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::video_interfaces::srv::RobotLogin_Request msg_;
};

class Init_RobotLogin_Request_action
{
public:
  Init_RobotLogin_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotLogin_Request_client_id action(::video_interfaces::srv::RobotLogin_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_RobotLogin_Request_client_id(msg_);
  }

private:
  ::video_interfaces::srv::RobotLogin_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::video_interfaces::srv::RobotLogin_Request>()
{
  return video_interfaces::srv::builder::Init_RobotLogin_Request_action();
}

}  // namespace video_interfaces


namespace video_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotLogin_Response_message
{
public:
  explicit Init_RobotLogin_Response_message(::video_interfaces::srv::RobotLogin_Response & msg)
  : msg_(msg)
  {}
  ::video_interfaces::srv::RobotLogin_Response message(::video_interfaces::srv::RobotLogin_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::video_interfaces::srv::RobotLogin_Response msg_;
};

class Init_RobotLogin_Response_success
{
public:
  Init_RobotLogin_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotLogin_Response_message success(::video_interfaces::srv::RobotLogin_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RobotLogin_Response_message(msg_);
  }

private:
  ::video_interfaces::srv::RobotLogin_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::video_interfaces::srv::RobotLogin_Response>()
{
  return video_interfaces::srv::builder::Init_RobotLogin_Response_success();
}

}  // namespace video_interfaces

#endif  // VIDEO_INTERFACES__SRV__DETAIL__ROBOT_LOGIN__BUILDER_HPP_
