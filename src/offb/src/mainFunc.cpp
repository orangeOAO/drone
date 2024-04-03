#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>

class DroneAction {
public:
    DroneAction() : rate(2.0) { // 初始化频率为10Hz
        // Advertise and Subscribe初始化
        local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
        local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose",10, &DroneAction::location_cb, this);
        state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &DroneAction::state_cb, this);

        takeoff_attempted = false;

        // 客户端初始化
        arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
        set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
        takeoff_cl = nh.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff");

        // 等待无人机连接
        ROS_INFO("Waiting for UAV connection...");
        while(ros::ok() && !current_state.connected){
            ros::spinOnce();
            rate.sleep();
        }
        ROS_INFO("UAV connected.");
    }

    void takeOff(float altitude) {
        
        if(!current_state.armed) {
            if(arm()) {
                ROS_INFO("UAV Armed.");
            }
        }
        if(current_state.mode != "OFFBOARD" && setMode("OFFBOARD")) {
            ROS_INFO("Offboard enabled");
        }

        if(!takeoff_attempted) 
        {
            geometry_msgs::PoseStamped _newPose;
            _newPose.pose.position.x = 0;
            _newPose.pose.position.y = 0;
            _newPose.pose.position.z = altitude + current_location.pose.position.z;
            local_pos_pub.publish(_newPose);
            takeoff_attempted = true;
        }
    }

    void spin() {
        while(ros::ok()) {
            if(!takeoff_attempted) {
                takeOff(5.0); // 假设起飞高度为5米
                ROS_INFO("TAKE OFF");
            }
            ros::spinOnce();
            rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;
    ros::Rate rate;

    ros::Publisher local_pos_pub;
    ros::Subscriber local_pos_sub;
    ros::Subscriber state_sub;

    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;
    ros::ServiceClient takeoff_cl;

    mavros_msgs::State current_state;
    geometry_msgs::PoseStamped current_location;
    bool takeoff_attempted;

    void state_cb(const mavros_msgs::State::ConstPtr& msg) {
        current_state = *msg;
    }
    
    void location_cb(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        current_location = *msg;
    }

    bool arm() {
        mavros_msgs::CommandBool arm_srv;
        arm_srv.request.value = true;
        return arming_client.call(arm_srv) && arm_srv.response.success;
    }

    bool setMode(const std::string &mode) {
        mavros_msgs::SetMode set_mode_srv;
        set_mode_srv.request.custom_mode = mode;
        return set_mode_client.call(set_mode_srv) && set_mode_srv.response.mode_sent;
    }



};

int main(int argc, char **argv) {
    ros::init(argc, argv, "drone_action_node");
    DroneAction droneAction;

    droneAction.spin(); // 主循环

    return 0;
}
