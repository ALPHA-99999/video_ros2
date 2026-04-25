#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "video_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__msg__EncodedFrame() -> *const std::ffi::c_void;
}

#[link(name = "video_interfaces__rosidl_generator_c")]
extern "C" {
    fn video_interfaces__msg__EncodedFrame__init(msg: *mut EncodedFrame) -> bool;
    fn video_interfaces__msg__EncodedFrame__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EncodedFrame>, size: usize) -> bool;
    fn video_interfaces__msg__EncodedFrame__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EncodedFrame>);
    fn video_interfaces__msg__EncodedFrame__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EncodedFrame>, out_seq: *mut rosidl_runtime_rs::Sequence<EncodedFrame>) -> bool;
}

// Corresponds to video_interfaces__msg__EncodedFrame
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EncodedFrame {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_size: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub codec: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: rosidl_runtime_rs::Sequence<u8>,

}



impl Default for EncodedFrame {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !video_interfaces__msg__EncodedFrame__init(&mut msg as *mut _) {
        panic!("Call to video_interfaces__msg__EncodedFrame__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EncodedFrame {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__msg__EncodedFrame__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__msg__EncodedFrame__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__msg__EncodedFrame__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EncodedFrame {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EncodedFrame where Self: Sized {
  const TYPE_NAME: &'static str = "video_interfaces/msg/EncodedFrame";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__msg__EncodedFrame() }
  }
}


