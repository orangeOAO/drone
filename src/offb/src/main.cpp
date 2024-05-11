#include "CommunicationManager.h"
#include "TaskManager.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "node_name");
    ROS_INFO("Main start\n");
    CommunicationManager communicationManager;
    TaskManager taskManager(communicationManager);
    ros::Rate _rate(10);
    while(ros::ok())
    {
        communicationManager.ServiceCall();
        taskManager.TakeOff(2.4);
        ros::spinOnce();
        _rate.sleep();

    }



    return 0;
}