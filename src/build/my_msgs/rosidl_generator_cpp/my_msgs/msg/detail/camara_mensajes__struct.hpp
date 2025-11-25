// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_msgs:msg/CamaraMensajes.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_msgs/msg/camara_mensajes.hpp"


#ifndef MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_HPP_
#define MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'image'
#include "sensor_msgs/msg/detail/compressed_image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_msgs__msg__CamaraMensajes __attribute__((deprecated))
#else
# define DEPRECATED__my_msgs__msg__CamaraMensajes __declspec(deprecated)
#endif

namespace my_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CamaraMensajes_
{
  using Type = CamaraMensajes_<ContainerAllocator>;

  explicit CamaraMensajes_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : image(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->camera_id = "";
      this->image_format = "";
    }
  }

  explicit CamaraMensajes_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : camera_id(_alloc),
    image_format(_alloc),
    image(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->camera_id = "";
      this->image_format = "";
    }
  }

  // field types and members
  using _camera_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _camera_id_type camera_id;
  using _image_format_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _image_format_type image_format;
  using _image_type =
    sensor_msgs::msg::CompressedImage_<ContainerAllocator>;
  _image_type image;

  // setters for named parameter idiom
  Type & set__camera_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->camera_id = _arg;
    return *this;
  }
  Type & set__image_format(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->image_format = _arg;
    return *this;
  }
  Type & set__image(
    const sensor_msgs::msg::CompressedImage_<ContainerAllocator> & _arg)
  {
    this->image = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_msgs::msg::CamaraMensajes_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_msgs::msg::CamaraMensajes_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_msgs::msg::CamaraMensajes_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_msgs::msg::CamaraMensajes_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_msgs__msg__CamaraMensajes
    std::shared_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_msgs__msg__CamaraMensajes
    std::shared_ptr<my_msgs::msg::CamaraMensajes_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CamaraMensajes_ & other) const
  {
    if (this->camera_id != other.camera_id) {
      return false;
    }
    if (this->image_format != other.image_format) {
      return false;
    }
    if (this->image != other.image) {
      return false;
    }
    return true;
  }
  bool operator!=(const CamaraMensajes_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CamaraMensajes_

// alias to use template instance with default allocator
using CamaraMensajes =
  my_msgs::msg::CamaraMensajes_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_msgs

#endif  // MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_HPP_
