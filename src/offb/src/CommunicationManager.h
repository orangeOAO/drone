#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/CameraInfo.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>
#include <gazebo_msgs/GetModelState.h>
#include <gazebo_msgs/GetModelStateRequest.h>
#include <gazebo_msgs/GetModelStateResponse.h>
#include <geometry_msgs/Pose.h>

#include <hog_haar_person_detection/Faces.h>
#include <hog_haar_person_detection/Pedestrians.h>
#include <hog_haar_person_detection/BoundingBox.h>

class CommunicationManager {
private:
    ros::NodeHandle nh;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;
    ros::ServiceClient land_client;
    ros::ServiceClient gazebo_client;


    mavros_msgs::CommandBool arm_cmd;
    mavros_msgs::SetMode offb_set_mode;
    ros::Subscriber state_sub;
    ros::Subscriber _pedestrain_sub;
    ros::Subscriber _cameraInfoSub;
    ros::Subscriber _pos_sub;
    ros::Publisher local_pos_pub;
    ros::Publisher vel_pub;

    mavros_msgs::State _current_state;
    hog_haar_person_detection::Pedestrians _pedestrianData;
    sensor_msgs::CameraInfo _cameraInfo;
    ros::Time last_request;
    geometry_msgs::PoseStamped _current_pose;
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
        _current_pose = *msg;
        // ROS_INFO("OAO=%f, %f ,%f",_current_pose.pose.position.x, _current_pose.pose.position.y, _current_pose.pose.position.z);
    }
    void state_cb(const mavros_msgs::State::ConstPtr& msg)
    {
        _current_state = *msg;
    }

    void pedestrain_cb(const hog_haar_person_detection::Pedestrians::ConstPtr& msg)
    {
        _pedestrianData = *msg;
    }


public:
    CommunicationManager();
    ~CommunicationManager() = default;
    void SendVelocity(const geometry_msgs::Twist& vel);
    void SendPose(const geometry_msgs::PoseStamped& Pose);
    void CallLand();
    void CallState(std::string state){this->ServiceCall(state);};

    void ArmVehicle();
    void OffboardVehicle(std::string mode);

    void ServiceCall(const std::string& mode= "OFFBOARD");
    geometry_msgs::Pose GetModelPose(const std::string modelName="pedestrian");

    geometry_msgs::PoseStamped GetCurrentPose();
    hog_haar_person_detection::Pedestrians GetPedestrainCoordination();
    sensor_msgs::CameraInfo GetCameraInfo(){return _cameraInfo;};

        
};

#endif