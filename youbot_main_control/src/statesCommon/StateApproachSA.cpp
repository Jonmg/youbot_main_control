/*
 * StateApproachSA.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateApproachSA.h"
#include "../statesGrasp/StateObjectRecognition.h"
#include "../statesGrasp/StateDeliver.h"
#include "../YoubotModel.h"
#include "youbot_msgs/SubTask.h"

StateApproachSA::StateApproachSA(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string velTopic;
	std::string laserTopic;
	_prvNh->param<std::string>("vel_topic", velTopic, "cmd_vel");
	_prvNh->param<std::string>("laser_topic", laserTopic, "laser");

	_velPub = _nh->advertise<geometry_msgs::Twist>(velTopic, 10);
	_laserSub = _nh->subscribe(laserTopic, 10, &StateApproachSA::laserCallback, this);}

StateApproachSA::~StateApproachSA()
{

}

void StateApproachSA::laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan)
{
	double distance = laserScan->ranges[256];
	std::cout << "distance: " << distance << std::endl;
	if(distance<0.4)
	{
		_closeEnough = true;
		std::cout << "Under 20cm" << std::endl;
	}
	else
	{
		_closeEnough = false;
	}
}

void StateApproachSA::onEntry()
{
	_closeEnough = false;
	_vel.linear.x = 0.08;
}

void StateApproachSA::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(ApproachSA)");

	ros::spinOnce();
	if (!_closeEnough)
	{
		_velPub.publish(_vel);
	}
	else
	{
		_vel.linear.x = 0.0;
		_velPub.publish(_vel);
		youbot_msgs::SubTask actualSubTask;
		_model->getActualSubTask(actualSubTask);
		if (actualSubTask.subTasktType == "G")
		{
			ROS_INFO_STREAM("SM(ApproachSA): Close enough. Go to State ObjectRecognition");
			_agent->transitionToVolatileState(new StateObjectRecognition(_model));
		}
		else if (actualSubTask.subTasktType == "D")
		{
			ROS_INFO_STREAM("SM(ApproachSA): Close enough. Go to State Deliver Object");
			_agent->transitionToVolatileState(new StateDeliver(_model));
		}
		else
		{
			ROS_INFO_STREAM("SM(ReturnSA): Not a valid TaskType. Go to State Next");
			_agent->transitionToPersistantState(STATE_NEXT);
		}
	}
}
