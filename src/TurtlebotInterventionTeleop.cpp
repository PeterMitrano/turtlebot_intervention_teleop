#include "TurtlebotInterventionTeleop.h"

#include <cstdio>
#include <unistd.h>

#include <ros/console.h>
#include <ros/ros.h>

TurtlebotInterventionTeleop::TurtlebotInterventionTeleop(int argc,
                                                         char **argv) {
  tcgetattr(STDIN_FILENO, &t); // get the current terminal I/O structure
  t.c_lflag &= ~ICANON; // Manipulate the flag bits to do what you want it to do
  tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply the new settings

  ros::init(argc, argv, "turtlebot_intervention_teleop");
  ros::NodeHandle nh;

  ROS_INFO("Press [Enter] after using Ctrl+C.");

  while (ros::ok()) {
    std::getchar(); // non-blocking
    ROS_INFO("getchar returned.\n");
  }
}

int main(int argc, char **argv) { TurtlebotInterventionTeleop(argc, argv); }
