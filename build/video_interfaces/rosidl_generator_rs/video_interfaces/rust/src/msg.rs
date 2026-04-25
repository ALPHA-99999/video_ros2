#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to video_interfaces__msg__EncodedFrame

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EncodedFrame {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_size: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub codec: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: Vec<u8>,

}



impl Default for EncodedFrame {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::EncodedFrame::default())
  }
}

impl rosidl_runtime_rs::Message for EncodedFrame {
  type RmwMsg = super::msg::rmw::EncodedFrame;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        source: msg.source.as_str().into(),
        frame_id: msg.frame_id,
        frame_size: msg.frame_size,
        codec: msg.codec.as_str().into(),
        data: msg.data.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        source: msg.source.as_str().into(),
      frame_id: msg.frame_id,
      frame_size: msg.frame_size,
        codec: msg.codec.as_str().into(),
        data: msg.data.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      source: msg.source.to_string(),
      frame_id: msg.frame_id,
      frame_size: msg.frame_size,
      codec: msg.codec.to_string(),
      data: msg.data
          .into_iter()
          .collect(),
    }
  }
}


