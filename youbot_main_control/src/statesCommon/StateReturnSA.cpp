/*
 * StateReturnSA.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateReturnSA.h"
#include "../statesCommon/StateNext.h"
#include "../YoubotModel.h"

StateReturnSA::StateReturnSA(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string velTopic;
	std::string laserTopic;
	_prvNh->param<std::string>("vel_topic", velTopic, "cmd_vel");
	_prvNh->param<std::string>("laser_topic", laserTopic, "laser");

	_velPub = _nh->advertise<geometry_msgs::Twist>(velTopic, 10);
	_laserSub = _nh->subscribe(laserTopic, 10, &StateReturnSA::laserCallback, this);
}

StateReturnSA::~StateReturnSA()
{
	// TODO Auto-generated destructor stub
}

void StateReturnSA::laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan)
{
	double distance = laserScan->ranges[256];
		std::cout << "distance: " << distance << std::endl;
		if(distance > 0.6)
	{
		_farEnough = true;
		std::cout << "over 60cm" << std::endl;
	}
	else
	{
		_farEnough = false;
	}
}

void StateReturnSA::onEntry()
{
	_farEnough = false;
	_vel.linear.x = -0.1;
}

void StateReturnSA::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(ReturnSA)");

	ros::spinOnce();
	if (!_farEnough)
	{
		_velPub.publish(_vel);
	}
	else
	{
		_vel.linear.x = 0.0;
		_velPub.publish(_vel);
		ROS_INFO_STREAM("SM(ReturnSA): Far enough. Go to State Next");
		_agent->transitionToPersistantState(STATE_NEXT);
	}
}
