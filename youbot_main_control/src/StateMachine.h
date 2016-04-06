/*
 * StateMachine.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include "obcore/statemachine/Agent.h"

class YoubotModel;

class StateMachine {
public:
	StateMachine();
	virtual ~StateMachine();
	void start();

private:
	void run();
	bool updatePose();

	obvious::Agent _agent;
	tf::TransformListener _listener;
	std::string _tfBaseFrame;
	std::string _tfRobotFrame;
	unsigned int _robotId;

	ros::NodeHandle* _nh;
	ros::NodeHandle* _prvNh;
	YoubotModel* _model;
	ros::Rate* _loopMain;
};

#endif /* STATEMACHINE_H_ */
