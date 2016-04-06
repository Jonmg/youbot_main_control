/*
 * youbot_control_node.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include <ros/ros.h>
#include "StateMachine.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "youbot_control_node");
  StateMachine stateMachine;
  stateMachine.start();
}
