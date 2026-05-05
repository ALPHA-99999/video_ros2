#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "video_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__srv__RobotLogin_Request() -> *const std::ffi::c_void;
}

#[link(name = "video_interfaces__rosidl_generator_c")]
extern "C" {
    fn video_interfaces__srv__RobotLogin_Request__init(msg: *mut RobotLogin_Request) -> bool;
    fn video_interfaces__srv__RobotLogin_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Request>, size: usize) -> bool;
    fn video_interfaces__srv__RobotLogin_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Request>);
    fn video_interfaces__srv__RobotLogin_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RobotLogin_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Request>) -> bool;
}

// Corresponds to video_interfaces__srv__RobotLogin_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RobotLogin_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub action: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_id: rosidl_runtime_rs::String,

}



impl Default for RobotLogin_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !video_interfaces__srv__RobotLogin_Request__init(&mut msg as *mut _) {
        panic!("Call to video_interfaces__srv__RobotLogin_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RobotLogin_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RobotLogin_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RobotLogin_Request where Self: Sized {
  const TYPE_NAME: &'static str = "video_interfaces/srv/RobotLogin_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__srv__RobotLogin_Request() }
  }
}


#[link(name = "video_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__srv__RobotLogin_Response() -> *const std::ffi::c_void;
}

#[link(name = "video_interfaces__rosidl_generator_c")]
extern "C" {
    fn video_interfaces__srv__RobotLogin_Response__init(msg: *mut RobotLogin_Response) -> bool;
    fn video_interfaces__srv__RobotLogin_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Response>, size: usize) -> bool;
    fn video_interfaces__srv__RobotLogin_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Response>);
    fn video_interfaces__srv__RobotLogin_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RobotLogin_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RobotLogin_Response>) -> bool;
}

// Corresponds to video_interfaces__srv__RobotLogin_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RobotLogin_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for RobotLogin_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !video_interfaces__srv__RobotLogin_Response__init(&mut msg as *mut _) {
        panic!("Call to video_interfaces__srv__RobotLogin_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RobotLogin_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { video_interfaces__srv__RobotLogin_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RobotLogin_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RobotLogin_Response where Self: Sized {
  const TYPE_NAME: &'static str = "video_interfaces/srv/RobotLogin_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__video_interfaces__srv__RobotLogin_Response() }
  }
}






#[link(name = "video_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__video_interfaces__srv__RobotLogin() -> *const std::ffi::c_void;
}

// Corresponds to video_interfaces__srv__RobotLogin
#[allow(missing_docs, non_camel_case_types)]
pub struct RobotLogin;

impl rosidl_runtime_rs::Service for RobotLogin {
    type Request = RobotLogin_Request;
    type Response = RobotLogin_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__video_interfaces__srv__RobotLogin() }
    }
}


