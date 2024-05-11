#include "TaskManager.h"

void TaskManager::ExecuteTree()
{

}

void TaskManager::TakeOff(double height)
{
    _targetPose.header.frame_id = "Set takeoff altitude";
    _targetPose.header.stamp = ros::Time();
    _targetPose.pose.position.x = _targetPose.pose.position.x ;
    _targetPose.pose.position.y = _targetPose.pose.position.y ;
    _targetPose.pose.position.z = height;
    communicationManager.SendPose(_targetPose);
}

void TaskManager::Land()
{
    
}

void TaskManager::SetPoint()
{

}

void TaskManager::Track(hog_haar_person_detection::BoundingBox targetCoordinate)
{

}

void TaskManager::CheckDeviation(geometry_msgs::PoseStamped currentPose)
{
    if (std::fabs(_targetPose.pose.position.x - currentPose.pose.position.x) < 0.1 &&
        std::fabs(_targetPose.pose.position.y - currentPose.pose.position.y) < 0.1 &&
        std::fabs(_targetPose.pose.position.z - currentPose.pose.position.z) < 0.1) {
        _positionReached = true;
    }
}


