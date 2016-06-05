#include "TurtlebotInterventionTeleop.h"

#include <unistd.h>
#include <cstdio>

#include <ros/console.h>
#include <ros/ros.h>

TurtlebotInterventionTeleop::TurtlebotInterventionTeleop(int argc,
                                                         char **argv) {
  // get the current terminal I/O structure,
  // Manipulate the flag bits to do what you want it to do,
  // and Apply the new settings
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);

  ros::init(argc, argv, "turtlebot_intervention_teleop");
  ros::NodeHandle nh;

  ROS_INFO("Press [Enter] after using Ctrl+C.");

  while (ros::ok()) {
    std::getchar();  // non-blocking
    ROS_INFO("getchar returned.\n");
  }
}

int main(int argc, char **argv) { TurtlebotInterventionTeleop(argc, argv); }
