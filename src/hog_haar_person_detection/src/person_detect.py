#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
from ultralytics import YOLO
from hog_haar_person_detection.msg import Pedestrians, BoundingBox

class YOLOPersonDetection:
    def __init__(self):
        self.bridge = CvBridge()
        self.model = YOLO("yolov8n.pt")  # Load YOLO model
        self.model.fuse()
        camera_topic = rospy.get_param("image_topic", "/camera/rgb/image_raw")
        self.image_sub = rospy.Subscriber(camera_topic, Image, self.callback)
        self.image_pub = rospy.Publisher("/camera_person_tracker/output_video", Image, queue_size=1)
        self.pedestrians_pub = rospy.Publisher("/person_detection/pedestrians", Pedestrians, queue_size=10)

    def callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            # rospy.loginfo("Received image")
        except CvBridgeError as e:
            rospy.logerr(f"CvBridge error: {e}")
            return

        # YOLO inference
        
        results = self.model(cv_image)

        pedestrians_msg = Pedestrians()
        for result in results:
            for box in result.boxes:
                cls = box.cls.item()  # Convert tensor to float
                if self.model.names[int(cls)] == "person":
                    xyxy = box.xyxy.cpu().numpy()[0]
                    conf = box.conf.item()  # Convert tensor to float

                    label = f'{self.model.names[int(cls)]} {conf:.2f}'
                    cv2.rectangle(cv_image, (int(xyxy[0]), int(xyxy[1])), (int(xyxy[2]), int(xyxy[3])), (255, 0, 0), 2)
                    cv2.putText(cv_image, label, (int(xyxy[0]), int(xyxy[1]) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)

                    pedestrian = BoundingBox()
                    pedestrian.center.x = int((xyxy[0] + xyxy[2]) / 2)
                    pedestrian.center.y = int((xyxy[1] + xyxy[3]) / 2)
                    pedestrian.width = int(xyxy[2] - xyxy[0])
                    pedestrian.height = int(xyxy[3] - xyxy[1])
                    pedestrians_msg.pedestrians.append(pedestrian)

        self.pedestrians_pub.publish(pedestrians_msg)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
            # rospy.loginfo("Published image")
        except CvBridgeError as e:
            rospy.logerr(f"CvBridge error: {e}")

        cv2.imshow("YOLOv8", cv_image)
        cv2.waitKey(3)

if __name__ == '__main__':
    rospy.init_node('yolo_person_detection', anonymous=True)
    yp = YOLOPersonDetection()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        rospy.loginfo("Shutting down")
    cv2.destroyAllWindows()
