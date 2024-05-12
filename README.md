# FlyingOrange

The PX4-Autopilot folder must  use "make" command, otherwise gazebo can not find iris.sdf file.

```cmd 
cd ~/PX4-Autopilot
DONT_RUN=1 make px4_sitl_default
cd ~/orange_ws
bash test.sh
rosrun offb main
```
