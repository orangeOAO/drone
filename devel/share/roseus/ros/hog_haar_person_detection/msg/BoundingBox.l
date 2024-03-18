;; Auto-generated. Do not edit!


(when (boundp 'hog_haar_person_detection::BoundingBox)
  (if (not (find-package "HOG_HAAR_PERSON_DETECTION"))
    (make-package "HOG_HAAR_PERSON_DETECTION"))
  (shadow 'BoundingBox (find-package "HOG_HAAR_PERSON_DETECTION")))
(unless (find-package "HOG_HAAR_PERSON_DETECTION::BOUNDINGBOX")
  (make-package "HOG_HAAR_PERSON_DETECTION::BOUNDINGBOX"))

(in-package "ROS")
;;//! \htmlinclude BoundingBox.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass hog_haar_person_detection::BoundingBox
  :super ros::object
  :slots (_center _width _height ))

(defmethod hog_haar_person_detection::BoundingBox
  (:init
   (&key
    ((:center __center) (instance geometry_msgs::Point :init))
    ((:width __width) 0)
    ((:height __height) 0)
    )
   (send-super :init)
   (setq _center __center)
   (setq _width (round __width))
   (setq _height (round __height))
   self)
  (:center
   (&rest __center)
   (if (keywordp (car __center))
       (send* _center __center)
     (progn
       (if __center (setq _center (car __center)))
       _center)))
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _center
    (send _center :serialization-length)
    ;; uint32 _width
    4
    ;; uint32 _height
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _center
       (send _center :serialize s)
     ;; uint32 _width
       (write-long _width s)
     ;; uint32 _height
       (write-long _height s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _center
     (send _center :deserialize buf ptr-) (incf ptr- (send _center :serialization-length))
   ;; uint32 _width
     (setq _width (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _height
     (setq _height (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hog_haar_person_detection::BoundingBox :md5sum-) "848ee5efc3139d88c5674f66671d9625")
(setf (get hog_haar_person_detection::BoundingBox :datatype-) "hog_haar_person_detection/BoundingBox")
(setf (get hog_haar_person_detection::BoundingBox :definition-)
      "geometry_msgs/Point center
uint32 width
uint32 height

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :hog_haar_person_detection/BoundingBox "848ee5efc3139d88c5674f66671d9625")


