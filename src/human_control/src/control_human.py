#!/usr/bin/env python3
import rospy
from gazebo_msgs.srv import GetModelState, GetModelStateRequest
from geometry_msgs.msg import Pose

def get_model_pose(model_name):
    rospy.init_node('get_gazebo_model_pose', anonymous=True)
    rospy.wait_for_service('/gazebo/get_model_state')
    try:
        get_model_state = rospy.ServiceProxy('/gazebo/get_model_state', GetModelState)
        request = GetModelStateRequest()
        request.model_name = model_name
        response = get_model_state(request)
        return response.pose
    except rospy.ServiceException as e:
        rospy.logerr("Service call failed: %s" % e)
        return None

if __name__ == "__main__":
    model_name = 'pedestrian'  # Replace with your model's name in Gazebo
    while(not rospy.is_shutdown()):
        pose = get_model_pose(model_name)
        if pose:
            rospy.loginfo("Model Pose: \n%s" % pose)
        else:
            rospy.logwarn("Failed to get model pose.")
