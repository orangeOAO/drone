; Auto-generated. Do not edit!


(cl:in-package hog_haar_person_detection-msg)


;//! \htmlinclude Pedestrians.msg.html

(cl:defclass <Pedestrians> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pedestrians
    :reader pedestrians
    :initarg :pedestrians
    :type (cl:vector hog_haar_person_detection-msg:BoundingBox)
   :initform (cl:make-array 0 :element-type 'hog_haar_person_detection-msg:BoundingBox :initial-element (cl:make-instance 'hog_haar_person_detection-msg:BoundingBox))))
)

(cl:defclass Pedestrians (<Pedestrians>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Pedestrians>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Pedestrians)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hog_haar_person_detection-msg:<Pedestrians> is deprecated: use hog_haar_person_detection-msg:Pedestrians instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Pedestrians>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hog_haar_person_detection-msg:header-val is deprecated.  Use hog_haar_person_detection-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pedestrians-val :lambda-list '(m))
(cl:defmethod pedestrians-val ((m <Pedestrians>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hog_haar_person_detection-msg:pedestrians-val is deprecated.  Use hog_haar_person_detection-msg:pedestrians instead.")
  (pedestrians m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Pedestrians>) ostream)
  "Serializes a message object of type '<Pedestrians>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'pedestrians))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'pedestrians))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Pedestrians>) istream)
  "Deserializes a message object of type '<Pedestrians>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'pedestrians) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'pedestrians)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'hog_haar_person_detection-msg:BoundingBox))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Pedestrians>)))
  "Returns string type for a message object of type '<Pedestrians>"
  "hog_haar_person_detection/Pedestrians")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Pedestrians)))
  "Returns string type for a message object of type 'Pedestrians"
  "hog_haar_person_detection/Pedestrians")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Pedestrians>)))
  "Returns md5sum for a message object of type '<Pedestrians>"
  "aa953661beff944b160295ead7064755")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Pedestrians)))
  "Returns md5sum for a message object of type 'Pedestrians"
  "aa953661beff944b160295ead7064755")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Pedestrians>)))
  "Returns full string definition for message of type '<Pedestrians>"
  (cl:format cl:nil "Header header~%hog_haar_person_detection/BoundingBox[] pedestrians~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hog_haar_person_detection/BoundingBox~%geometry_msgs/Point center~%uint32 width~%uint32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Pedestrians)))
  "Returns full string definition for message of type 'Pedestrians"
  (cl:format cl:nil "Header header~%hog_haar_person_detection/BoundingBox[] pedestrians~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hog_haar_person_detection/BoundingBox~%geometry_msgs/Point center~%uint32 width~%uint32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Pedestrians>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'pedestrians) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Pedestrians>))
  "Converts a ROS message object to a list"
  (cl:list 'Pedestrians
    (cl:cons ':header (header msg))
    (cl:cons ':pedestrians (pedestrians msg))
))
