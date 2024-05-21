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
    std::vector<hog_haar_person_detection::BoundingBox> _pedestrianDataVector;
    float _integralX , _integralZ; // 用于积分项的存储
    float _previousErrorX , _previousErrorZ; // 上一次的误差，用于微分项
    float _Kp, _Ki, _Kd; // PID 控制器的增益，需要根据实际情况调整
    geometry_msgs::Pose _pose;


public:
    TaskManager(CommunicationManager& manager) :
    communicationManager(manager), _taskNum(0), _positionReached(false) {
        _integralX = 0.0;
        _integralZ = 0.0;
        _previousErrorX = 0.0;
        _previousErrorZ = 0.0;
        _Kp = 0.05; _Ki = 0; _Kd = 0.001;
        // ROS_INFO("OAO=%p",communicationManager);

};
    ~TaskManager() = default;
    void ExecuteTree();
    void TakeOff(double height);
    void SetPoint(double x, double y, double z);
    void Land();
    void Track();
    void TrackInGazebo();
    void CheckDeviation(geometry_msgs::PoseStamped);
    void SetTask(std::function<void()> func);
    // void Test(CommunicationManager &manager){ ROS_INFO("OAO%p",manager);
    // void TestGet(){std::cout<<"Test"<<communicationManager.GetCurrentPose()<<"\n";};




};

#endif