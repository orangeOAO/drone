#include "CommunicationManager.h"
#include "TaskManager.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "node_name");
    ROS_INFO("Main start\n");
    CommunicationManager communicationManager;
    TaskManager taskManager(communicationManager);
    ros::Rate _rate(10);
    taskManager.SetTask(std::bind(&TaskManager::TakeOff,&taskManager,2.5));
    taskManager.SetTask(std::bind(&TaskManager::TrackInGazebo,&taskManager));
    taskManager.SetTask(std::bind(&TaskManager::Land,&taskManager));

    while(ros::ok())
    {
        communicationManager.ServiceCall();
        taskManager.ExecuteTree();

        ros::spinOnce();
        _rate.sleep();

    }
    return 0;
}