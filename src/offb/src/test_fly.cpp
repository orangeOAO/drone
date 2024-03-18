#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <tf2/LinearMath/Quaternion.h>

// 全局变量来存储当前状态
mavros_msgs::State current_state;

struct Robot_settings{
    double x;
    double y;
    double z;
};

// 状态回调函数
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    // 状态、位置发布和服务客户端设置
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    // 设定点发布率必须快于2Hz
    ros::Rate rate(20.0);

    // 等待与飞控单元的连接
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    geometry_msgs::PoseStamped pose;
    Robot_settings robot_setting;
    

    //param
    // pose.pose.position.x = ros::param::get("/");  // 示例位置
    // pose.pose.position.y = 1;
    // pose.pose.position.z = 2;


    // 四元数初始化和规范化
    tf2::Quaternion quat;
    quat.setRPY(0, 0, M_PI);  // 指定角度
    quat.normalize();  // 四元数规范化

    // 应用规范化后的四元数
    pose.pose.orientation.x = quat.x();
    pose.pose.orientation.y = quat.y();
    pose.pose.orientation.z = quat.z();
    pose.pose.orientation.w = quat.w();

    // // 在启用离线模式前发送一些设定点
    // for(int i = 100; ros::ok() && i > 0; --i){
    //     local_pos_pub.publish(pose);
    //     ros::spinOnce();
    //     rate.sleep();
    // }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();
    ROS_INFO("OAO\n");
    while(ros::ok()){
        
        nh.getParam("robot_settings/x",robot_setting.x);
        nh.getParam("robot_settings/y", robot_setting.y);
        nh.getParam("robot_settings/z",robot_setting.z );
        pose.pose.position.x = robot_setting.x;
        pose.pose.position.y = robot_setting.y;
        pose.pose.position.z = robot_setting.z;

        //ROS_INFO("x=%.f, y=%.f, z=%.f\n",robot_setting.x, robot_setting.y, robot_setting.z);

        //ROS_INFO("%lf", (ros::Time::now() - last_request).toSec());
        //ROS_INFO("%s", current_state.mode.c_str());
        if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(1.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard mode enabled");
            }
            last_request = ros::Time::now();
        } else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(1.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }

        // 更新位置
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
