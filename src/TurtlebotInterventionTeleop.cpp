#include "TurtlebotInterventionTeleop.h"

#include <unistd.h>
#include <cstdio>

#include <geometry_msgs/Twist.h>
#include <ros/console.h>
#include <ros/ros.h>

TurtlebotInterventionTeleop::TurtlebotInterventionTeleop(int argc,
                                                         char **argv) {
  // get the current terminal I/O structure,
  // Manipulate the flag bits to do what you want it to do,
  // and Apply the new settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  ros::init(argc, argv, "turtlebot_intervention_teleop");
  ros::NodeHandle nh;

  ros::Publisher cmd_vel_pub =
      nh.advertise<geometry_msgs::Twist>("teleop_cmd_vel", 0, false);

  ROS_INFO("Press [Enter] after using Ctrl+C.");

  nh.param<int>("move_speed", move_speed, 1);
  nh.param<int>("rotation_speed", rotation_speed, 1);

  while (ros::ok()) {
    char c = std::getchar();  // non-blocking

    geometry_msgs::Twist new_msg;

    switch (c) {
      case 'w':  // fwd
        new_msg.linear.x = move_speed;
        break;
      case 'q':  // fwd-ccw arc
        new_msg.linear.x = move_speed;
        new_msg.angular.z = -rotation_speed;
        break;
      case 'e':  // fwd-cw arc
        new_msg.linear.x = move_speed;
        new_msg.angular.z = rotation_speed;
        break;
      case 'a':  // ccw rotate
        new_msg.angular.z = -rotation_speed;
        break;
      case 's':  // stop
        break;
      case 'd':  // cw rotate
        new_msg.angular.z = rotation_speed;
        break;
      case 'z':  // left translate
        new_msg.angular.y = -move_speed;
        break;
      case 'x':  // reverse
        new_msg.linear.x = -move_speed;
        break;
      case 'c':  // right translate
        new_msg.angular.y = move_speed;
        break;
    }

    cmd_vel_pub.publish(new_msg);
  }

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

}

int main(int argc, char **argv) { TurtlebotInterventionTeleop(argc, argv); }
