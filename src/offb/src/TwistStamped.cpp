#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/ExtendedState.h>

#include <image_transport/image_transport.h> // for publishing and subscribing to images in ROS
#include <sensor_msgs/image_encodings.h>

#include <hog_haar_person_detection/Faces.h>       //用于发布人脸检测结果
#include <hog_haar_person_detection/Pedestrians.h> //用于发布行人检测结果
#include <hog_haar_person_detection/BoundingBox.h> //用于发布bounding box结果

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

mavros_msgs::State current_state;
geometry_msgs::PoseStamped current_location;
hog_haar_person_detection::BoundingBox pedestrainData;
geometry_msgs::Twist vel_msg;
void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
    current_state = *msg;
}

void loc_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    current_location = *msg;
}

void TrackPedestrian(hog_haar_person_detection::BoundingBox::ConstPtr msg)
{
    //projection to robot-axis=0,1
    pedestrainData = *msg;
    ROS_INFO("x=%.2f, y=%.2f, z=%.2f\n",pedestrainData.center.x, pedestrainData.center.y, pedestrainData.center.z);
    // vel_msg.linear.x=
}
void TakeOff(_Float32 high)
{
    ros::NodeHandle nh;

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);

    local_pos_pub.publish(current_location.pose.position.z+high);
}

int main(int argc, char *argv[]){
    ros::init(argc, argv, "test_node");
    ros::NodeHandle nh;
    ros::Subscriber pedestrians_sub;
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);


    ros::Subscriber local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 10, loc_cb);

    // 2.发布话题
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>
                ("/mavros/setpoint_velocity/cmd_vel_unstamped",10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);

    nh.subscribe<hog_haar_person_detection::BoundingBox>("/person_detection/pedestrian/data",10, TrackPedestrian);

    // 设定点发布率必须快于2Hz
    ros::Rate rate(2.0);
    // ROS_INFO("start =%s\n",current_state.connected?"True":"False");
    // 等待与飞控单元的连接
    while(ros::ok() && !current_state.connected){
        // ROS_INFO("start =%s\n",current_state.connected?"True":"False");
        ros::spinOnce();
        rate.sleep();
    }
    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;
    
    

    ros::Time last_request = ros::Time::now();
    while(ros::ok()){
        // ROS_INFO("Current time: %.2lf", (ros::Time::now()-last_request).toSec());
        if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard mode enabled");
            }
            last_request = ros::Time::now();
        } else {
            // if (ros::Time::now() - last_request > ros::Duration(5.0)){
            //     ROS_INFO("%d",current_state.armed );
            //     ROS_INFO("OFFBOARD=%s",current_state.mode.c_str());
            //     ROS_INFO("success=%s",arming_client.call(arm_cmd)?"True":"False");
            //     ROS_INFO("response_success=%s",arm_cmd.response.success?"True":"False");

            // }
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) && arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }

                last_request = ros::Time::now();
            }
        }
        // 3.速度消息
    
    // ros::Timer timer = nh.createTimer(ros::Duration(1.0), timerCallback);
    ROS_INFO("Position=%.2f", current_location.pose.position.x);

    if(current_location.pose.position.x<-10){
        vel_msg.angular.z = 0;
        vel_msg.linear.y = 0;
        vel_msg.linear.z = 0;
        vel_msg.linear.x = 0;
    }

    // 4.发布话题
    vel_pub.publish(vel_msg);
    ros::spinOnce();
    }

    return 0;
}
