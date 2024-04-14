#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/CameraInfo.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>

#include <hog_haar_person_detection/Faces.h>
#include <hog_haar_person_detection/Pedestrians.h>
#include <hog_haar_person_detection/BoundingBox.h>





class ActionUAV
{
    public:
        ActionUAV(ros::NodeHandle x):nh(x)
        {
            arm_cmd.request.value = true;
            _attempedTakeoff = false;
            _attempedTrack = false;
            _attempLand = false;
            arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
            state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &ActionUAV::state_cb, this);
            _cameraInfoSub = nh.subscribe<sensor_msgs::CameraInfo>("/iris/camera/depth/camera_info", 10,
            [this](const sensor_msgs::CameraInfo::ConstPtr &msg)
            {
                this->_cameraInfo = *msg;
            }
            );
    

            set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
            land_client = nh.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/land");

            local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
            vel_pub = nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped",10);
            _pedestrain_sub = nh.subscribe<hog_haar_person_detection::BoundingBox>("/person_detection/pedestrian/data", 1000, &ActionUAV::pedestrain_cb, this);

            // offb_set_mode.request.custom_mode ="OFFBOARD";

            last_request = ros::Time::now();

            ros::Rate rate(20.0);

            // wait for FCU connection
            while(ros::ok() && _current_state.connected){
                ros::spinOnce();
                rate.sleep();
                ROS_INFO("connecting to FCT...");
            }
            


        };
        ~ActionUAV() = default;
        void serviceCall(const std::string& mode= "OFFBOARD")
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

        void setPoint(double x, double y, double z)
        {
            _pose.header.frame_id = "Set Point";
            _pose.header.stamp = ros::Time();
            _pose.pose.position.x = x ;
            _pose.pose.position.y = y ;
            _pose.pose.position.z = z ;
            local_pos_pub.publish(_pose);
        }

        void takeOff(double altitude)
        {

            if(!_attempedTakeoff){
                _pose.header.frame_id = "Set takeoff altitude";
                _pose.header.stamp = ros::Time();
                _pose.pose.position.x = _pose.pose.position.x ;
                _pose.pose.position.y = _pose.pose.position.y ;
                _pose.pose.position.z = _pose.pose.position.z + altitude;
                
                _attempedTakeoff = true;
                
            }
            if(_controlState == "POSITION")
            {
                local_pos_pub.publish(_pose);
            }
                

        }
        void setControlState(std::string state)
        {
            ROS_INFO("%s\n",state.c_str());
            _controlState = state;
        }
        bool waitToUnlock()
        {
            return _current_state.armed && _current_state.mode == "OFFBOARD";
        }

        void land()
        {
            if(!_attempLand){
                ros::service::waitForService("/mavros/cmd/land");
                _attempLand = true;
                _landSrv.request.altitude = 0.0; // 设置起飞后的目标高度为5米
                _landSrv.request.latitude = 0;// 使用当前位置
                _landSrv.request.longitude = 0;  // 使用当前位置
                _landSrv.request.min_pitch = 0;  // 最小俯仰角，0表示忽略
                _landSrv.request.yaw = 0;        // 目标偏航角，0表示忽略

                if (land_client.call(_landSrv)) { // 调用服务
                    if (_landSrv.response.success) 
                    {
                        ROS_INFO("LANDING....");
                    } 
                    else 
                    {
                        ROS_ERROR("LAND failed");
                    }
                } 
                else 
                {
                    ROS_ERROR("Failed to call service /mavros/cmd/land");
                }
            }
        }

        void decideToOpenTrack(bool TF)
        {
            _attempedTrack = TF;
            _controlState = "TRACK";
        }
        void test()
        {

            
        }

    private:
        ros::NodeHandle nh;
        ros::ServiceClient arming_client;
        ros::ServiceClient set_mode_client;
        ros::ServiceClient land_client;

        mavros_msgs::CommandBool arm_cmd;
        mavros_msgs::SetMode offb_set_mode;

        ros::Subscriber state_sub;
        ros::Subscriber _pedestrain_sub;
        ros::Subscriber _cameraInfoSub;
        ros::Publisher local_pos_pub;
        ros::Publisher vel_pub;

        tf::TransformListener listener;

        mavros_msgs::State _current_state;
        hog_haar_person_detection::BoundingBox _pedestrainData;
        sensor_msgs::CameraInfo _cameraInfo;
        mavros_msgs::CommandTOL _landSrv;

        ros::Time last_request;
        geometry_msgs::PoseStamped _pose;
        geometry_msgs::Twist _velMsg;
        ros::Time _catchClock;

        std::string _controlState;
        bool _attempedTakeoff;
        bool _attempLand;
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
            if(_attempedTrack && ros::Time::now() - _catchClock>ros::Duration(0.5)){
                // geometry_msgs::PointStamped boxCoordinate, targetCoordinate;
                // boxCoordinate.point.x = 0;
                double dx = _cameraInfo.width/2 - _pedestrainData.center.x;
                                
                if(abs(_cameraInfo.width/2 - _pedestrainData.center.x)<=50)
                {
                    _velMsg.linear.y = 0;
                    _velMsg.linear.x = 0;
                    _velMsg.linear.z = 0;
                    ROS_INFO("goodgoodgood");
                }
                else
                {
                    _velMsg.linear.y = PID_P * dx * 0.05;
                    ROS_INFO("dx=%f p=%f", dx, _velMsg.linear.y);
                }
                _catchClock = ros::Time::now();


            }
            if(_controlState == "TRACK")
            {
                vel_pub.publish(_velMsg);
            }
            
        }

 

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "arm_node");
    ros::NodeHandle nh;
    int param;
    ros::Rate _rate(20.0);
    ActionUAV _ActionUAV(nh);
    ros::Time _landTimeTest = ros::Time::now();
    ROS_INFO("START!");
    int x =0 ;
    while(ros::ok() && x<60*10)
    {
        _ActionUAV.serviceCall();
        
        _ActionUAV.setControlState("POSITION");
        _ActionUAV.takeOff(2.5);
        
        ros::spinOnce();
        _rate.sleep();
        x++;
    }
    x=0;
    while(ros::ok() && x<50*10)
    {
        _ActionUAV.serviceCall();
        _ActionUAV.setControlState("TRACK");
        _ActionUAV.decideToOpenTrack(true);
        

        ros::spinOnce();
        _rate.sleep();
        x++;
    }
    x=0;
    while(ros::ok() && x<50*10)
    {

        _ActionUAV.serviceCall();
        _ActionUAV.setControlState("LAND");
        _ActionUAV.land();
        ros::spinOnce();
        _rate.sleep();
        x++;
    }

    // for(int i = 0; ros::ok() && i < 10*5; ++i){
    //     _ActionUAV.serviceCall("LAND");
    //     _ActionUAV.test(false);
    //     ros::spinOnce();
    //     _rate.sleep();

    // }

    
    
    
    // ros::spin();
    
    
    // 4.请求服务
    
    return 0;
}
