#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
from gazebo_msgs.srv import GetModelState, SetModelState
from gazebo_msgs.msg import ModelState

class HumanController:
    def __init__(self):
        rospy.init_node('human_controller')

        self.model_name = 'pedestrian'  # Gazebo中人的模型名称
        self.cmd_vel_sub = rospy.Subscriber('/cmd_vel', Twist, self.cmd_vel_callback)
        self.set_model_state = rospy.ServiceProxy('/gazebo/set_model_state', SetModelState)
        self.get_model_state = rospy.ServiceProxy('/gazebo/get_model_state', GetModelState)

        self.current_twist = Twist()

    def cmd_vel_callback(self, msg):
        self.current_twist = msg

    def update_human_state(self):
        try:
            model_state = self.get_model_state(self.model_name, 'world')
            new_state = ModelState()
            new_state.model_name = self.model_name
            new_state.pose = model_state.pose
            new_state.twist = self.current_twist
            new_state.reference_frame = 'world'
            self.set_model_state(new_state)
        except rospy.ServiceException as e:
            rospy.logerr("Service call failed: %s" % e)

    def run(self):
        rate = rospy.Rate(10)  # 10Hz
        while not rospy.is_shutdown():
            self.update_human_state()
            rate.sleep()

if __name__ == '__main__':
    controller = HumanController()
    controller.run()
