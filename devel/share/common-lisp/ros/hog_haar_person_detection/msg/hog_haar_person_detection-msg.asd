
(cl:in-package :asdf)

(defsystem "hog_haar_person_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "BoundingBox" :depends-on ("_package_BoundingBox"))
    (:file "_package_BoundingBox" :depends-on ("_package"))
    (:file "Faces" :depends-on ("_package_Faces"))
    (:file "_package_Faces" :depends-on ("_package"))
    (:file "Pedestrians" :depends-on ("_package_Pedestrians"))
    (:file "_package_Pedestrians" :depends-on ("_package"))
  ))