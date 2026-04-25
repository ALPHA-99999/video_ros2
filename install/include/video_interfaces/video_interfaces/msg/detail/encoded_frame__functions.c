// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from video_interfaces:msg/EncodedFrame.idl
// generated code does not contain a copyright notice
#include "video_interfaces/msg/detail/encoded_frame__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `source`
// Member `codec`
#include "rosidl_runtime_c/string_functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
video_interfaces__msg__EncodedFrame__init(video_interfaces__msg__EncodedFrame * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    video_interfaces__msg__EncodedFrame__fini(msg);
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__init(&msg->source)) {
    video_interfaces__msg__EncodedFrame__fini(msg);
    return false;
  }
  // frame_id
  // frame_size
  // codec
  if (!rosidl_runtime_c__String__init(&msg->codec)) {
    video_interfaces__msg__EncodedFrame__fini(msg);
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0)) {
    video_interfaces__msg__EncodedFrame__fini(msg);
    return false;
  }
  return true;
}

void
video_interfaces__msg__EncodedFrame__fini(video_interfaces__msg__EncodedFrame * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // source
  rosidl_runtime_c__String__fini(&msg->source);
  // frame_id
  // frame_size
  // codec
  rosidl_runtime_c__String__fini(&msg->codec);
  // data
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

bool
video_interfaces__msg__EncodedFrame__are_equal(const video_interfaces__msg__EncodedFrame * lhs, const video_interfaces__msg__EncodedFrame * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source), &(rhs->source)))
  {
    return false;
  }
  // frame_id
  if (lhs->frame_id != rhs->frame_id) {
    return false;
  }
  // frame_size
  if (lhs->frame_size != rhs->frame_size) {
    return false;
  }
  // codec
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->codec), &(rhs->codec)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
video_interfaces__msg__EncodedFrame__copy(
  const video_interfaces__msg__EncodedFrame * input,
  video_interfaces__msg__EncodedFrame * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__copy(
      &(input->source), &(output->source)))
  {
    return false;
  }
  // frame_id
  output->frame_id = input->frame_id;
  // frame_size
  output->frame_size = input->frame_size;
  // codec
  if (!rosidl_runtime_c__String__copy(
      &(input->codec), &(output->codec)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

video_interfaces__msg__EncodedFrame *
video_interfaces__msg__EncodedFrame__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  video_interfaces__msg__EncodedFrame * msg = (video_interfaces__msg__EncodedFrame *)allocator.allocate(sizeof(video_interfaces__msg__EncodedFrame), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(video_interfaces__msg__EncodedFrame));
  bool success = video_interfaces__msg__EncodedFrame__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
video_interfaces__msg__EncodedFrame__destroy(video_interfaces__msg__EncodedFrame * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    video_interfaces__msg__EncodedFrame__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
video_interfaces__msg__EncodedFrame__Sequence__init(video_interfaces__msg__EncodedFrame__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  video_interfaces__msg__EncodedFrame * data = NULL;

  if (size) {
    data = (video_interfaces__msg__EncodedFrame *)allocator.zero_allocate(size, sizeof(video_interfaces__msg__EncodedFrame), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = video_interfaces__msg__EncodedFrame__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        video_interfaces__msg__EncodedFrame__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
video_interfaces__msg__EncodedFrame__Sequence__fini(video_interfaces__msg__EncodedFrame__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      video_interfaces__msg__EncodedFrame__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

video_interfaces__msg__EncodedFrame__Sequence *
video_interfaces__msg__EncodedFrame__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  video_interfaces__msg__EncodedFrame__Sequence * array = (video_interfaces__msg__EncodedFrame__Sequence *)allocator.allocate(sizeof(video_interfaces__msg__EncodedFrame__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = video_interfaces__msg__EncodedFrame__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
video_interfaces__msg__EncodedFrame__Sequence__destroy(video_interfaces__msg__EncodedFrame__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    video_interfaces__msg__EncodedFrame__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
video_interfaces__msg__EncodedFrame__Sequence__are_equal(const video_interfaces__msg__EncodedFrame__Sequence * lhs, const video_interfaces__msg__EncodedFrame__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!video_interfaces__msg__EncodedFrame__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
video_interfaces__msg__EncodedFrame__Sequence__copy(
  const video_interfaces__msg__EncodedFrame__Sequence * input,
  video_interfaces__msg__EncodedFrame__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(video_interfaces__msg__EncodedFrame);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    video_interfaces__msg__EncodedFrame * data =
      (video_interfaces__msg__EncodedFrame *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!video_interfaces__msg__EncodedFrame__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          video_interfaces__msg__EncodedFrame__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!video_interfaces__msg__EncodedFrame__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
