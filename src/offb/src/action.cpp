#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <hog_haar_person_detection/Faces.h>
#include <hog_haar_person_detection/Pedestrians.h>
#include <hog_haar_person_detection/BoundingBox.h>
#include <sensor_msgs/CameraInfo.h>
#include <geometry_msgs/Twist.h>




class ActionUAV
{
    public:
        ActionUAV(ros::NodeHandle x):nh(x)
        {
            arm_cmd.request.value = true;
            _attempedTakeoff = false;
            _attempedTrack = false;
            arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
            state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &ActionUAV::state_cb, this);
            _cameraInfoSub = nh.subscribe<sensor_msgs::CameraInfo>("/iris/camera/depth/camera_info", 10,
            [this](const sensor_msgs::CameraInfo::ConstPtr &msg)
            {
                this->_cameraInfo = *msg;
            }
            );
    

            set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

            local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
            vel_pub = nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped",10);
            _pedestrain_sub = nh.subscribe<hog_haar_person_detection::BoundingBox>("/person_detection/pedestrian/data", 100, &ActionUAV::pedestrain_cb, this);

            offb_set_mode.request.custom_mode ="OFFBOARD";
            arm_cmd.request.value = true;

            last_request = ros::Time::now();



        };
        ~ActionUAV() = default;
        void serviceCall()
        {
            if(ros::Time::now() - last_request > ros::Duration(5.0))
            {
                ROS_INFO("Detect");
                if(_current_state.mode != "OFFBOARD")
                {
                    if( arming_client.call(arm_cmd) && arm_cmd.response.success){
                        ROS_INFO("Vehicle armed");
                    }
                }
                if(!_current_state.armed ){
                    if(set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
                    {
                        ROS_INFO("Offboard mode enabled");
                    }
                } 
                
                last_request = ros::Time::now();
            }
            
        }
        void takeOff(double altitude)
        {

            if(!_attempedTakeoff){
                _pose.pose.position.x = _pose.pose.position.x;
                _pose.pose.position.y = _pose.pose.position.y;
                _pose.pose.position.z = _pose.pose.position.z + altitude;
                
                _attempedTakeoff = true;
            }
            local_pos_pub.publish(_pose);

        }

        bool waitToUnlock()
        {
            return _current_state.armed && _current_state.mode == "OFFBOARD";
        }

        void land()
        {
            _pose.pose.position.z = 0;
            local_pos_pub.publish(_pose);
        }


        void test(bool altitude)
        {
            _attempedTrack = altitude;
            // ROS_INFO("%f",altitude);
        }

    private:
        ros::NodeHandle nh;
        ros::ServiceClient arming_client;
        ros::ServiceClient set_mode_client;

        mavros_msgs::CommandBool arm_cmd;
        mavros_msgs::SetMode offb_set_mode;

        ros::Subscriber state_sub;
        ros::Subscriber _pedestrain_sub;
        ros::Subscriber _cameraInfoSub;
        ros::Publisher local_pos_pub;
        ros::Publisher vel_pub;

        mavros_msgs::State _current_state;
        hog_haar_person_detection::BoundingBox _pedestrainData;
        sensor_msgs::CameraInfo _cameraInfo;



        ros::Time last_request;
        geometry_msgs::PoseStamped _pose;
        geometry_msgs::Twist _velMsg;


        bool _attempedTakeoff;
        bool _attempedTrack;


        void state_cb(const mavros_msgs::State::ConstPtr& msg)
        {
            _current_state = *msg;
        }

        void pedestrain_cb(const hog_haar_person_detection::BoundingBox::ConstPtr &msg)
        {
            _pedestrainData = *msg;
            track();
            // ROS_INFO("x=%f, y=%f",_pedestrainData.center.x, _pedestrainData.center.y);
        }

        void track()
        {
            const double PID_P = 0.2;
            if(_attempedTrack){
                double dx = _cameraInfo.width/2 - _pedestrainData.center.x;
                // int dy = _cameraInfo.height/2 - _pedestrainData.center.y;
                // _velMsg.linear.x = MAX_SPEED / dx * -20;
                
                if(abs(_cameraInfo.width/2 - _pedestrainData.center.x)<=50)
                {
                    _velMsg.linear.y = 0;
                    _velMsg.linear.x = 0;
                    _velMsg.linear.z = 0;
                }
                else
                {
                    _velMsg.linear.y = PID_P * dx * 0.05;
                }
                ROS_INFO("dx=%f p=%f", dx, _velMsg.linear.y);
            }
            vel_pub.publish(_velMsg);
        }

 

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "arm_node");
    ros::NodeHandle nh;
    int param;
    ros::Rate _rate(2.0);
    ActionUAV _ActionUAV(nh);
    ros::Time _landTimeTest = ros::Time::now();

    while(ros::ok())
    {
        nh.getParam("height", param);

        _ActionUAV.serviceCall();
        if(_ActionUAV.waitToUnlock())
        {
            _ActionUAV.takeOff(1);
            _ActionUAV.test(true);
        }
        
        // _ActionUAV.test(param);
        // ROS_INFO("%f",_landTimeTest.toSec());
        ros::spinOnce();
        _rate.sleep();

    }
    
    
    // 4.请求服务
    
    return 0;
}
