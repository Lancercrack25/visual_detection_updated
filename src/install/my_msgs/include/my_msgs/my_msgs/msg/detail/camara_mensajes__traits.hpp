// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_msgs:msg/CamaraMensajes.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_msgs/msg/camara_mensajes.hpp"


#ifndef MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__TRAITS_HPP_
#define MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_msgs/msg/detail/camara_mensajes__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'image'
#include "sensor_msgs/msg/detail/compressed_image__traits.hpp"

namespace my_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CamaraMensajes & msg,
  std::ostream & out)
{
  out << "{";
  // member: camera_id
  {
    out << "camera_id: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_id, out);
    out << ", ";
  }

  // member: image_format
  {
    out << "image_format: ";
    rosidl_generator_traits::value_to_yaml(msg.image_format, out);
    out << ", ";
  }

  // member: image
  {
    out << "image: ";
    to_flow_style_yaml(msg.image, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CamaraMensajes & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: camera_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "camera_id: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_id, out);
    out << "\n";
  }

  // member: image_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image_format: ";
    rosidl_generator_traits::value_to_yaml(msg.image_format, out);
    out << "\n";
  }

  // member: image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image:\n";
    to_block_style_yaml(msg.image, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CamaraMensajes & msg, bool use_flow_style = false)
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

}  // namespace my_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_msgs::msg::CamaraMensajes & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_msgs::msg::CamaraMensajes & msg)
{
  return my_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_msgs::msg::CamaraMensajes>()
{
  return "my_msgs::msg::CamaraMensajes";
}

template<>
inline const char * name<my_msgs::msg::CamaraMensajes>()
{
  return "my_msgs/msg/CamaraMensajes";
}

template<>
struct has_fixed_size<my_msgs::msg::CamaraMensajes>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<my_msgs::msg::CamaraMensajes>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<my_msgs::msg::CamaraMensajes>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__TRAITS_HPP_
