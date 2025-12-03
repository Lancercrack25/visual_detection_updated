// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_msgs:msg/CamaraMensajes.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_msgs/msg/camara_mensajes.hpp"


#ifndef MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__BUILDER_HPP_
#define MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_msgs/msg/detail/camara_mensajes__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_msgs
{

namespace msg
{

namespace builder
{

class Init_CamaraMensajes_image
{
public:
  explicit Init_CamaraMensajes_image(::my_msgs::msg::CamaraMensajes & msg)
  : msg_(msg)
  {}
  ::my_msgs::msg::CamaraMensajes image(::my_msgs::msg::CamaraMensajes::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_msgs::msg::CamaraMensajes msg_;
};

class Init_CamaraMensajes_image_format
{
public:
  explicit Init_CamaraMensajes_image_format(::my_msgs::msg::CamaraMensajes & msg)
  : msg_(msg)
  {}
  Init_CamaraMensajes_image image_format(::my_msgs::msg::CamaraMensajes::_image_format_type arg)
  {
    msg_.image_format = std::move(arg);
    return Init_CamaraMensajes_image(msg_);
  }

private:
  ::my_msgs::msg::CamaraMensajes msg_;
};

class Init_CamaraMensajes_camera_id
{
public:
  Init_CamaraMensajes_camera_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CamaraMensajes_image_format camera_id(::my_msgs::msg::CamaraMensajes::_camera_id_type arg)
  {
    msg_.camera_id = std::move(arg);
    return Init_CamaraMensajes_image_format(msg_);
  }

private:
  ::my_msgs::msg::CamaraMensajes msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_msgs::msg::CamaraMensajes>()
{
  return my_msgs::msg::builder::Init_CamaraMensajes_camera_id();
}

}  // namespace my_msgs

#endif  // MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__BUILDER_HPP_
