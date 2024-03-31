#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/AttitudeTarget.h>


geometry_msgs::TwistStamped vel_msg;
void vel_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
        vel_msg = *msg;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "twist_test");
    ros::NodeHandle nh;
    
    
    // 2.订阅话题
    ros::Subscriber vel_sub = nh.subscribe<geometry_msgs::TwistStamped>
                ("/mavros/local_position/velocity_local",10,vel_cb);
    ros::Publisher thrust_pub = nh.advertise<mavros_msgs::AttitudeTarget>
			("/mavros/setpoint_raw/attitude",10);
    mavros_msgs::AttitudeTarget thrust_msg;
    thrust_msg.thrust = 0.7;
    thrust_msg.body_rate.y = 1;

    thrust_pub.publish(thrust_msg);

    // 3.打印话题内容
    std::cout << vel_msg.twist.linear.x << std::endl;
    std::cout << vel_msg.twist.linear.y << std::endl;
    std::cout << vel_msg.twist.linear.z << std::endl;
}