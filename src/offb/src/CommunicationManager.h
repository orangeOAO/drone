#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/CameraInfo.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>

#include <hog_haar_person_detection/Faces.h>
#include <hog_haar_person_detection/Pedestrians.h>
#include <hog_haar_person_detection/BoundingBox.h>

class CommunicationManager {
private:
    ros::NodeHandle nh;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;
    ros::ServiceClient land_client;

    mavros_msgs::CommandBool arm_cmd;
    mavros_msgs::SetMode offb_set_mode;
    ros::Subscriber state_sub;
    ros::Subscriber _pedestrain_sub;
    ros::Subscriber _cameraInfoSub;
    ros::Subscriber _pos_sub;
    ros::Publisher local_pos_pub;
    ros::Publisher vel_pub;

    mavros_msgs::State _current_state;
    hog_haar_person_detection::BoundingBox _pedestrainData;
    sensor_msgs::CameraInfo _cameraInfo;
    ros::Time last_request;
    geometry_msgs::PoseStamped _current_pose;
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
        _current_pose = *msg;
    }
    void state_cb(const mavros_msgs::State::ConstPtr& msg)
    {
        _current_state = *msg;
    }


public:
    CommunicationManager();
    ~CommunicationManager() = default;
    void SendVelocity(const geometry_msgs::Twist& vel);

    void SendPose(const geometry_msgs::PoseStamped& Pose);

    void ArmVehicle();
    void OffboardVehicle(std::string mode);

    void ServiceCall(const std::string& mode= "OFFBOARD");

    geometry_msgs::PoseStamped GetCurrentPose()
    {
        return _current_pose;
    }
        
};

#endif