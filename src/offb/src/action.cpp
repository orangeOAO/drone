#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>



class ActionTest
{
    public:
        ActionTest(ros::NodeHandle x):nh(x)
        {
            arm_cmd.request.value = true;
            _attempedTakeoff = false;
            arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
            state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, &ActionTest::state_cb, this);

            set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

            local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);


            offb_set_mode.request.custom_mode ="OFFBOARD";
            arm_cmd.request.value = true;

            last_request = ros::Time::now();



        };
        ~ActionTest() = default;
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

        void test(double altitude)
        {
            _pose.pose.position.x = _pose.pose.position.x;
            _pose.pose.position.y = _pose.pose.position.y;
            _pose.pose.position.z = altitude;
            local_pos_pub.publish(_pose);
            // ROS_INFO("%f",altitude);
        }

    private:
        ros::NodeHandle nh;
        ros::ServiceClient arming_client;
        ros::ServiceClient set_mode_client;

        mavros_msgs::CommandBool arm_cmd;
        mavros_msgs::SetMode offb_set_mode;

        ros::Subscriber state_sub;
        ros::Publisher local_pos_pub;

        mavros_msgs::State _current_state;
        ros::Time last_request;
        geometry_msgs::PoseStamped _pose;

        bool _attempedTakeoff;


        void state_cb(const mavros_msgs::State::ConstPtr& msg)
        {
            _current_state = *msg;
        }

 

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "arm_node");
    ros::NodeHandle nh;
    int param;
    ros::Rate _rate(2.0);
    ActionTest _actionTest(nh);
    ros::Time _landTimeTest = ros::Time::now();
    while(ros::ok())
    {
        nh.getParam("height", param);

        _actionTest.serviceCall();
        
        _actionTest.test(param);
        // ROS_INFO("%f",_landTimeTest.toSec());
        ros::spinOnce();
        _rate.sleep();

    }
    
    
    // 4.请求服务
    
    return 0;
}
