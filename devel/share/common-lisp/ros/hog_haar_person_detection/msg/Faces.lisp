; Auto-generated. Do not edit!


(cl:in-package hog_haar_person_detection-msg)


;//! \htmlinclude Faces.msg.html

(cl:defclass <Faces> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (faces
    :reader faces
    :initarg :faces
    :type (cl:vector hog_haar_person_detection-msg:BoundingBox)
   :initform (cl:make-array 0 :element-type 'hog_haar_person_detection-msg:BoundingBox :initial-element (cl:make-instance 'hog_haar_person_detection-msg:BoundingBox))))
)

(cl:defclass Faces (<Faces>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Faces>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Faces)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hog_haar_person_detection-msg:<Faces> is deprecated: use hog_haar_person_detection-msg:Faces instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Faces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hog_haar_person_detection-msg:header-val is deprecated.  Use hog_haar_person_detection-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'faces-val :lambda-list '(m))
(cl:defmethod faces-val ((m <Faces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hog_haar_person_detection-msg:faces-val is deprecated.  Use hog_haar_person_detection-msg:faces instead.")
  (faces m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Faces>) ostream)
  "Serializes a message object of type '<Faces>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'faces))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'faces))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Faces>) istream)
  "Deserializes a message object of type '<Faces>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'faces) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'faces)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'hog_haar_person_detection-msg:BoundingBox))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Faces>)))
  "Returns string type for a message object of type '<Faces>"
  "hog_haar_person_detection/Faces")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Faces)))
  "Returns string type for a message object of type 'Faces"
  "hog_haar_person_detection/Faces")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Faces>)))
  "Returns md5sum for a message object of type '<Faces>"
  "c83860b56162627e0249615ae27f05a0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Faces)))
  "Returns md5sum for a message object of type 'Faces"
  "c83860b56162627e0249615ae27f05a0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Faces>)))
  "Returns full string definition for message of type '<Faces>"
  (cl:format cl:nil "Header header~%hog_haar_person_detection/BoundingBox[] faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hog_haar_person_detection/BoundingBox~%geometry_msgs/Point center~%uint32 width~%uint32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Faces)))
  "Returns full string definition for message of type 'Faces"
  (cl:format cl:nil "Header header~%hog_haar_person_detection/BoundingBox[] faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hog_haar_person_detection/BoundingBox~%geometry_msgs/Point center~%uint32 width~%uint32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Faces>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'faces) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Faces>))
  "Converts a ROS message object to a list"
  (cl:list 'Faces
    (cl:cons ':header (header msg))
    (cl:cons ':faces (faces msg))
))
