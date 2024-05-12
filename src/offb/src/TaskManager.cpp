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
    const float KP = 0.1;
    sensor_msgs::CameraInfo cameraInfo = communicationManager.GetCameraInfo();
    hog_haar_person_detection::Pedestrians pedestrianInfo = communicationManager.GetPedestrainCoordination();
    
    geometry_msgs::Twist velMsg;
    if(!pedestrianInfo.pedestrians.empty())
    {
        double dx = cameraInfo.width/2 - pedestrianInfo.pedestrians[0].center.x;

        if(abs(dx)<=10)
        {
            velMsg.linear.y = 0;
            velMsg.linear.x = 0;
            velMsg.linear.z = 0;
            ROS_INFO("goodgoodgood");
            _positionReached = true;
        }
        else
        {
            velMsg.linear.y = KP * dx * 0.05;
        }
        // std::cout<<"OAO"<<pedestrianInfo.pedestrians[0].center<<"\n";

    }
    else
    {
        velMsg.linear.y = 0;
        velMsg.linear.x = 0;
        velMsg.linear.z = 0;
        ROS_INFO("badbadbad");
    }
    
    communicationManager.SendVelocity(velMsg);
    


    ROS_INFO("TRACK");
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




