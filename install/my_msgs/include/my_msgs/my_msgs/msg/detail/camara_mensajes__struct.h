// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_msgs:msg/CamaraMensajes.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_msgs/msg/camara_mensajes.h"


#ifndef MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_H_
#define MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'camera_id'
// Member 'image_format'
#include "rosidl_runtime_c/string.h"
// Member 'image'
#include "sensor_msgs/msg/detail/compressed_image__struct.h"

/// Struct defined in msg/CamaraMensajes in the package my_msgs.
typedef struct my_msgs__msg__CamaraMensajes
{
  rosidl_runtime_c__String camera_id;
  rosidl_runtime_c__String image_format;
  sensor_msgs__msg__CompressedImage image;
} my_msgs__msg__CamaraMensajes;

// Struct for a sequence of my_msgs__msg__CamaraMensajes.
typedef struct my_msgs__msg__CamaraMensajes__Sequence
{
  my_msgs__msg__CamaraMensajes * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_msgs__msg__CamaraMensajes__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_MSGS__MSG__DETAIL__CAMARA_MENSAJES__STRUCT_H_
