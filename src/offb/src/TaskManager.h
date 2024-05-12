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
    CommunicationManager &communicationManager;
    bool _positionReached;
    std::vector<std::function<void()>> _taskVector;
    int _taskNum;


public:
    TaskManager(CommunicationManager& manager) :
    communicationManager(manager), _taskNum(0), _positionReached(false) {
        // ROS_INFO("OAO=%p",communicationManager);

};
    ~TaskManager() = default;
    void ExecuteTree();
    void TakeOff(double height);
    void SetPoint(double x, double y, double z);
    void Land();
    void Track();
    void CheckDeviation(geometry_msgs::PoseStamped);
    void SetTask(std::function<void()> func);
    // void Test(CommunicationManager &manager){ ROS_INFO("OAO%p",manager);
    // void TestGet(){std::cout<<"Test"<<communicationManager.GetCurrentPose()<<"\n";};




};

#endif