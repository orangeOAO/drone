;; Auto-generated. Do not edit!


(when (boundp 'hog_haar_person_detection::Pedestrians)
  (if (not (find-package "HOG_HAAR_PERSON_DETECTION"))
    (make-package "HOG_HAAR_PERSON_DETECTION"))
  (shadow 'Pedestrians (find-package "HOG_HAAR_PERSON_DETECTION")))
(unless (find-package "HOG_HAAR_PERSON_DETECTION::PEDESTRIANS")
  (make-package "HOG_HAAR_PERSON_DETECTION::PEDESTRIANS"))

(in-package "ROS")
;;//! \htmlinclude Pedestrians.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hog_haar_person_detection::Pedestrians
  :super ros::object
  :slots (_header _pedestrians ))

(defmethod hog_haar_person_detection::Pedestrians
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pedestrians __pedestrians) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _pedestrians __pedestrians)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pedestrians
   (&rest __pedestrians)
   (if (keywordp (car __pedestrians))
       (send* _pedestrians __pedestrians)
     (progn
       (if __pedestrians (setq _pedestrians (car __pedestrians)))
       _pedestrians)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; hog_haar_person_detection/BoundingBox[] _pedestrians
    (apply #'+ (send-all _pedestrians :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; hog_haar_person_detection/BoundingBox[] _pedestrians
     (write-long (length _pedestrians) s)
     (dolist (elem _pedestrians)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; hog_haar_person_detection/BoundingBox[] _pedestrians
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pedestrians (let (r) (dotimes (i n) (push (instance hog_haar_person_detection::BoundingBox :init) r)) r))
     (dolist (elem- _pedestrians)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get hog_haar_person_detection::Pedestrians :md5sum-) "aa953661beff944b160295ead7064755")
(setf (get hog_haar_person_detection::Pedestrians :datatype-) "hog_haar_person_detection/Pedestrians")
(setf (get hog_haar_person_detection::Pedestrians :definition-)
      "Header header
hog_haar_person_detection/BoundingBox[] pedestrians

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



(provide :hog_haar_person_detection/Pedestrians "aa953661beff944b160295ead7064755")


