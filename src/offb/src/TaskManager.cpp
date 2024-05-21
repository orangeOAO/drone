#include "TaskManager.h"


void TaskManager::ExecuteTree() {
    if (_taskVector.empty()) {
        ROS_INFO("No Tasks");
        return;
    }

    _taskVector[_taskNum]();

    if (_positionReached) {
        _taskNum++;
        _positionReached = false; 
        if (_taskNum >= _taskVector.size()) {
            ROS_INFO("All tasks completed");
            _taskNum = 0;
        }
    }
}

void TaskManager::SetTask(std::function<void()> func)
{
    _taskVector.push_back(func);
}

void TaskManager::TakeOff(double height)
{
    _targetPose.header.frame_id = "Set takeoff altitude";
    _targetPose.header.stamp = ros::Time();
    _targetPose.pose.position.z = height;
    CheckDeviation(communicationManager.GetCurrentPose());
    communicationManager.SendPose(_targetPose);
    // std::cout<<"OAO\n"<<communicationManager.GetCurrentPose()<<"\n";

}

void TaskManager::Land()
{
    communicationManager.CallLand();
}

void TaskManager::SetPoint(double x, double y, double z)
{
    _targetPose.header.frame_id = "Set takeoff altitude";
    _targetPose.header.stamp = ros::Time();
    _targetPose.pose.position.x = x;
    _targetPose.pose.position.y = y;
    _targetPose.pose.position.z = z;
    CheckDeviation(communicationManager.GetCurrentPose());
    communicationManager.SendPose(_targetPose);

}

void TaskManager::Track()
{
    
    const float dt = 0.1; // 控制周期，假设为0.1秒，实际应该与你的更新频率一致

    sensor_msgs::CameraInfo cameraInfo = communicationManager.GetCameraInfo();
    hog_haar_person_detection::Pedestrians pedestrianInfo = communicationManager.GetPedestrainCoordination();
    if (!pedestrianInfo.pedestrians.empty())
    {
        _pedestrianDataVector.push_back(pedestrianInfo.pedestrians[0]);
        _pedestrianDataVector[0] = pedestrianInfo.pedestrians[0];
        //  std::cout<<"OAO"<<pedestrianInfo.pedestrians[0].center<<"\n";
    }
    
    geometry_msgs::Twist velMsg;
    if (!pedestrianInfo.pedestrians.empty())
    {

        const int MID_PLACE = 0;//_pedestrianDataVector.size() / 2;
        double errorX = (cameraInfo.width / 2 - _pedestrianDataVector[MID_PLACE].center.x) * 0.1;
        double errorZ = (cameraInfo.height /2 +30 - _pedestrianDataVector[MID_PLACE].center.y) * 0.1;

        _integralX += errorX * dt;
        _integralZ += errorZ * dt;

        double derivativeX = (errorX - _previousErrorX) / dt;
        double derivativeZ = (errorZ - _previousErrorZ) / dt;
        // std::cout<<"errorZ = "<<_pedestrianDataVector[MID_PLACE].center.y <<"\n";
        double outputX = _Kp * errorX + _Ki * _integralX + _Kd * derivativeX;
        double outputZ = _Kp * errorZ + _Ki  * _integralZ + _Kd * derivativeZ;

        velMsg.linear.y = outputX;
        velMsg.linear.z = outputZ; 

        _previousErrorX = errorX;
        _previousErrorZ = errorZ;
        std::cout<<"errorX ="<<errorX<<" errorZ="<< errorZ<<"\n";
        if(abs(errorX)<=10)
        {
            velMsg.linear.y = 0;
            
            ROS_INFO("complete Z");
            // _positionReached = true;
        }
        if(abs(errorZ) <=10)
        {
            velMsg.linear.z = 0;
            ROS_INFO("complete Z");
        }

        _pedestrianDataVector.clear();
    }
    else
    {
        velMsg.linear.x = 0;
        velMsg.linear.z = 0;
    }
    communicationManager.SendVelocity(velMsg);

    
    
}

void TaskManager::CheckDeviation(geometry_msgs::PoseStamped currentPose)
{
    // ROS_INFO("x=%f, y=%f, z=%f",currentPose.pose.position.x,currentPose.pose.position.y,currentPose.pose.position.z);
    if (std::fabs(_targetPose.pose.position.x - currentPose.pose.position.x) < 0.1 &&
        std::fabs(_targetPose.pose.position.y - currentPose.pose.position.y) < 0.1 &&
        std::fabs(_targetPose.pose.position.z - currentPose.pose.position.z) < 0.1) {
        _positionReached = true;
        return;
    }
    _positionReached = false;
}

void TaskManager::TrackInGazebo()
{
    _pose = communicationManager.GetModelPose("pedestrian");
    // ROS_INFO("Model Pose: [x: %f, y: %f, z: %f, qx: %f, qy: %f, qz: %f, qw: %f]\n",
    //             _pose.position.x, _pose.position.y, _pose.position.z,
    //             _pose.orientation.x, _pose.orientation.y, _pose.orientation.z, _pose.orientation.w);
    geometry_msgs::PoseStamped sendPose;
    sendPose.header.frame_id = "send model-pose to UAC";
    sendPose.header.stamp = ros::Time();
    sendPose.pose.position.y = _pose.position.y;
    sendPose.pose.position.z = _pose.position.z+1.0;
    communicationManager.SendPose(sendPose);

}



