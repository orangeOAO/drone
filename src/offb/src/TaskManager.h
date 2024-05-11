#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include "CommunicationManager.h"
#include <hog_haar_person_detection/BoundingBox.h>
#include <geometry_msgs/PoseStamped.h>

enum Task {
    TAKEOFF,
    GO_TO_POSITION,
    TRACK,
    LAND
};

class TaskManager
{
private:
    geometry_msgs::PoseStamped _targetPose;
    CommunicationManager communicationManager;
    bool _positionReached;


public:
    TaskManager(const CommunicationManager& manager):communicationManager(manager){;};
    ~TaskManager() = default;
    void ExecuteTree();
    void TakeOff(double height);
    void SetPoint();
    void Land();
    void Track(hog_haar_person_detection::BoundingBox targetCoordinate);
    void CheckDeviation(geometry_msgs::PoseStamped);


};

#endif