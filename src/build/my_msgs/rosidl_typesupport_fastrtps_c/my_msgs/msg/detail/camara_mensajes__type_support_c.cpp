// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from my_msgs:msg/CamaraMensajes.idl
// generated code does not contain a copyright notice
#include "my_msgs/msg/detail/camara_mensajes__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "my_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "my_msgs/msg/detail/camara_mensajes__struct.h"
#include "my_msgs/msg/detail/camara_mensajes__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // camera_id, image_format
#include "rosidl_runtime_c/string_functions.h"  // camera_id, image_format
#include "sensor_msgs/msg/detail/compressed_image__functions.h"  // image

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
bool cdr_serialize_sensor_msgs__msg__CompressedImage(
  const sensor_msgs__msg__CompressedImage * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
bool cdr_deserialize_sensor_msgs__msg__CompressedImage(
  eprosima::fastcdr::Cdr & cdr,
  sensor_msgs__msg__CompressedImage * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
size_t get_serialized_size_sensor_msgs__msg__CompressedImage(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
size_t max_serialized_size_sensor_msgs__msg__CompressedImage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
bool cdr_serialize_key_sensor_msgs__msg__CompressedImage(
  const sensor_msgs__msg__CompressedImage * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
size_t get_serialized_size_key_sensor_msgs__msg__CompressedImage(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
size_t max_serialized_size_key_sensor_msgs__msg__CompressedImage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_my_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, CompressedImage)();


using _CamaraMensajes__ros_msg_type = my_msgs__msg__CamaraMensajes;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
bool cdr_serialize_my_msgs__msg__CamaraMensajes(
  const my_msgs__msg__CamaraMensajes * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: camera_id
  {
    const rosidl_runtime_c__String * str = &ros_message->camera_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: image_format
  {
    const rosidl_runtime_c__String * str = &ros_message->image_format;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: image
  {
    cdr_serialize_sensor_msgs__msg__CompressedImage(
      &ros_message->image, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
bool cdr_deserialize_my_msgs__msg__CamaraMensajes(
  eprosima::fastcdr::Cdr & cdr,
  my_msgs__msg__CamaraMensajes * ros_message)
{
  // Field name: camera_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->camera_id.data) {
      rosidl_runtime_c__String__init(&ros_message->camera_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->camera_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'camera_id'\n");
      return false;
    }
  }

  // Field name: image_format
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->image_format.data) {
      rosidl_runtime_c__String__init(&ros_message->image_format);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->image_format,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'image_format'\n");
      return false;
    }
  }

  // Field name: image
  {
    cdr_deserialize_sensor_msgs__msg__CompressedImage(cdr, &ros_message->image);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
size_t get_serialized_size_my_msgs__msg__CamaraMensajes(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CamaraMensajes__ros_msg_type * ros_message = static_cast<const _CamaraMensajes__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: camera_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->camera_id.size + 1);

  // Field name: image_format
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->image_format.size + 1);

  // Field name: image
  current_alignment += get_serialized_size_sensor_msgs__msg__CompressedImage(
    &(ros_message->image), current_alignment);

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
size_t max_serialized_size_my_msgs__msg__CamaraMensajes(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: camera_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: image_format
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: image
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_sensor_msgs__msg__CompressedImage(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = my_msgs__msg__CamaraMensajes;
    is_plain =
      (
      offsetof(DataType, image) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
bool cdr_serialize_key_my_msgs__msg__CamaraMensajes(
  const my_msgs__msg__CamaraMensajes * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: camera_id
  {
    const rosidl_runtime_c__String * str = &ros_message->camera_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: image_format
  {
    const rosidl_runtime_c__String * str = &ros_message->image_format;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: image
  {
    cdr_serialize_key_sensor_msgs__msg__CompressedImage(
      &ros_message->image, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
size_t get_serialized_size_key_my_msgs__msg__CamaraMensajes(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CamaraMensajes__ros_msg_type * ros_message = static_cast<const _CamaraMensajes__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: camera_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->camera_id.size + 1);

  // Field name: image_format
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->image_format.size + 1);

  // Field name: image
  current_alignment += get_serialized_size_key_sensor_msgs__msg__CompressedImage(
    &(ros_message->image), current_alignment);

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_msgs
size_t max_serialized_size_key_my_msgs__msg__CamaraMensajes(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: camera_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: image_format
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: image
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_sensor_msgs__msg__CompressedImage(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = my_msgs__msg__CamaraMensajes;
    is_plain =
      (
      offsetof(DataType, image) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _CamaraMensajes__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const my_msgs__msg__CamaraMensajes * ros_message = static_cast<const my_msgs__msg__CamaraMensajes *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_my_msgs__msg__CamaraMensajes(ros_message, cdr);
}

static bool _CamaraMensajes__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  my_msgs__msg__CamaraMensajes * ros_message = static_cast<my_msgs__msg__CamaraMensajes *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_my_msgs__msg__CamaraMensajes(cdr, ros_message);
}

static uint32_t _CamaraMensajes__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_my_msgs__msg__CamaraMensajes(
      untyped_ros_message, 0));
}

static size_t _CamaraMensajes__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_my_msgs__msg__CamaraMensajes(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_CamaraMensajes = {
  "my_msgs::msg",
  "CamaraMensajes",
  _CamaraMensajes__cdr_serialize,
  _CamaraMensajes__cdr_deserialize,
  _CamaraMensajes__get_serialized_size,
  _CamaraMensajes__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _CamaraMensajes__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_CamaraMensajes,
  get_message_typesupport_handle_function,
  &my_msgs__msg__CamaraMensajes__get_type_hash,
  &my_msgs__msg__CamaraMensajes__get_type_description,
  &my_msgs__msg__CamaraMensajes__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_msgs, msg, CamaraMensajes)() {
  return &_CamaraMensajes__type_support;
}

#if defined(__cplusplus)
}
#endif
