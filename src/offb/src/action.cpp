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
            local_pos_pub.publish(_pose);

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
            _attempedTrack = true;
            track();
            // ROS_INFO("x=%f, y=%f",_pedestrainData.center.x, _pedestrainData.center.y);
        }

        void track()
        {
            const double PID_P = 0.2;
            if(_attempedTrack){
                // geometry_msgs::PointStamped boxCoordinate, targetCoordinate;
                // boxCoordinate.point.x = 0;
                double dx = _cameraInfo.width/2 - _pedestrainData.center.x;
                // int dy = _cameraInfo.height/2 - _pedestrainData.center.y;
                // _velMsg.linear.x = MAX_SPEED / dx * -20;
                // boxCoordinate.header.frame_id = "camera_link";
                
                // listener.transformPoint("iris::base_link", boxCoordinate, targetCoordinate);
                ROS_INFO("dx=%f p=%f", dx, _velMsg.linear.y);
                
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
                
                // geometry_msgs::PoseStamped targetPose;
                // targetPose.header.stamp = ros::Time::now();
                // targetPose.header.frame_id = "base_link";  // 使用 base_link 坐标系
                // targetPose.pose.position.x = targetCoordinate.point.x;
                // targetPose.pose.position.y = targetCoordinate.point.y;
                // targetPose.pose.position.z = targetCoordinate.point.z;
                // local_pos_pub.publish(targetPose);
                // ROS_INFO("Position -> x: %f, y: %f, z: %f", 
                //             targetPose.pose.position.x, 
                //             targetPose.pose.position.y, 
                //             targetPose.pose.position.z);


            }
            // vel_pub.publish(_velMsg);
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
    ROS_INFO("START!");

    while(ros::ok())
    {
        _ActionUAV.serviceCall();
        _ActionUAV.takeOff(2.5);
        ros::spinOnce();
        _rate.sleep();
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
