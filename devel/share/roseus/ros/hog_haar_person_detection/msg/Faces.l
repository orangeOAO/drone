;; Auto-generated. Do not edit!


(when (boundp 'hog_haar_person_detection::Faces)
  (if (not (find-package "HOG_HAAR_PERSON_DETECTION"))
    (make-package "HOG_HAAR_PERSON_DETECTION"))
  (shadow 'Faces (find-package "HOG_HAAR_PERSON_DETECTION")))
(unless (find-package "HOG_HAAR_PERSON_DETECTION::FACES")
  (make-package "HOG_HAAR_PERSON_DETECTION::FACES"))

(in-package "ROS")
;;//! \htmlinclude Faces.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hog_haar_person_detection::Faces
  :super ros::object
  :slots (_header _faces ))

(defmethod hog_haar_person_detection::Faces
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:faces __faces) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _faces __faces)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:faces
   (&rest __faces)
   (if (keywordp (car __faces))
       (send* _faces __faces)
     (progn
       (if __faces (setq _faces (car __faces)))
       _faces)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; hog_haar_person_detection/BoundingBox[] _faces
    (apply #'+ (send-all _faces :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; hog_haar_person_detection/BoundingBox[] _faces
     (write-long (length _faces) s)
     (dolist (elem _faces)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; hog_haar_person_detection/BoundingBox[] _faces
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _faces (let (r) (dotimes (i n) (push (instance hog_haar_person_detection::BoundingBox :init) r)) r))
     (dolist (elem- _faces)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get hog_haar_person_detection::Faces :md5sum-) "c83860b56162627e0249615ae27f05a0")
(setf (get hog_haar_person_detection::Faces :datatype-) "hog_haar_person_detection/Faces")
(setf (get hog_haar_person_detection::Faces :definition-)
      "Header header
hog_haar_person_detection/BoundingBox[] faces

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: hog_haar_person_detection/BoundingBox
geometry_msgs/Point center
uint32 width
uint32 height

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :hog_haar_person_detection/Faces "c83860b56162627e0249615ae27f05a0")


