#include "CommunicationManager.h"

CommunicationManager::CommunicationManager()
{
    set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &CommunicationManager::state_cb, this);
    _cameraInfoSub = nh.subscribe<sensor_msgs::CameraInfo>("/iris_depth_camera/camera/depth/camera_info", 10,
    [this](const sensor_msgs::CameraInfo::ConstPtr &msg)
    {
        this->_cameraInfo = *msg;
    }
    );
    gazebo_client = nh.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");

    land_client = nh.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/land");
    _pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 10, &CommunicationManager::positionCallback, this);
    local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped",10);
    _pedestrain_sub = nh.subscribe<hog_haar_person_detection::Pedestrians>("/person_detection/pedestrians", 10, &CommunicationManager::pedestrain_cb, this);


    last_request = ros::Time::now();

    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && _current_state.connected){
        ros::spinOnce();
        rate.sleep();
        ROS_INFO("connecting to FCT...");
    }

    arm_cmd.request.value = true;

}


void CommunicationManager::SendVelocity(const geometry_msgs::Twist& vel) 
{
    vel_pub.publish(vel);
    std::cout<<vel<<"\n";
}

void CommunicationManager::SendPose(const geometry_msgs::PoseStamped& pose)
{
    local_pos_pub.publish(pose);
}

void CommunicationManager::CallLand()
{
    std::string mode = "AUTO.LAND";
    if(_current_state.mode != mode){
        offb_set_mode.request.custom_mode = mode;
        if(set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
        {
            ROS_INFO("%s mode enabled", mode.c_str());
        }
    } 
            
        
}

void CommunicationManager::ServiceCall(const std::string& mode)
{

    if(ros::Time::now() - last_request > ros::Duration(5.0))
    {
        ROS_INFO("Detect");
        if(!_current_state.armed )
        {
            arm_cmd.request.value = true;
            if( arming_client.call(arm_cmd) && arm_cmd.response.success){
                ROS_INFO("Vehicle armed");
            }
        }
        if(_current_state.mode != mode){
            offb_set_mode.request.custom_mode = mode;
            if(set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
            {
                ROS_INFO("%s mode enabled", mode.c_str());
            }
        } 
        
        last_request = ros::Time::now();
    }
    
}

geometry_msgs::PoseStamped CommunicationManager::GetCurrentPose()
{
    // ROS_INFO("%f, %f ,%f",_current_pose.pose.position.x, _current_pose.pose.position.y, _current_pose.pose.position.z);
    return _current_pose;
}

hog_haar_person_detection::Pedestrians CommunicationManager::GetPedestrainCoordination()
{
    return _pedestrianData;
}

geometry_msgs::Pose CommunicationManager::GetModelPose(const std::string modelName)
{

    gazebo_msgs::GetModelState srv;
    srv.request.model_name = modelName;
    srv.request.relative_entity_name = "world";

    if (gazebo_client.call(srv)) {
        return srv.response.pose;
    } else {
        ROS_ERROR("Failed to call service get_model_state");
        return geometry_msgs::Pose();
    }
}

