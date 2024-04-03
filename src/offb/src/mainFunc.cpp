#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>

class DroneAction {
public:
    mavros_msgs::State current_state;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;
    DroneAction()
    { // 初始化频率为10Hz
        // Advertise and Subscribe初始化
        local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
        local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose",10, &DroneAction::location_cb, this);
        state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &DroneAction::state_cb, this);

        takeoff_attempted = false;

        // 客户端初始化
        arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
        set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

        
    }

    void takeOff(float altitude) {
        
        if(!current_state.armed) {
            // while(!arm()) {
            //     ROS_INFO("UAV not Armed.");  
            // }
            arm();
        }
        if(current_state.mode != "OFFBOARD" && setMode("OFFBOARD")) {
            ROS_INFO("Offboard enabled");
        }
        

        if(!takeoff_attempted && current_state.armed) 
        {
            ROS_INFO("UVA takeOff");
            geometry_msgs::PoseStamped _newPose;
            _newPose.pose.position.x = current_location.pose.position.x;
            _newPose.pose.position.y = current_location.pose.position.y;
            _newPose.pose.position.z = altitude + current_location.pose.position.z;
            local_pos_pub.publish(_newPose);
            takeoff_attempted = true;
        }
        else{
            ROS_WARN("Fail to takeOff");
        }
    }

private:
    ros::NodeHandle nh;
    // ros::Rate rate;

    ros::Publisher local_pos_pub;
    ros::Subscriber local_pos_sub;
    ros::Subscriber state_sub;


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

    ros::Rate rate(2.0);
    // 等待无人机连接
    ROS_INFO("Waiting for UAV connection...");
    while(ros::ok()){
        ros::spinOnce();
        rate.sleep();
    }
    
    while(ros::ok())
    {
        droneAction.takeOff(3);
        ros::spinOnce();
        rate.sleep();
    }
    

    return 0;
}
