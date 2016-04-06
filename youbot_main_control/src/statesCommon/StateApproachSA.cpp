/*
 * StateApproachSA.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateApproachSA.h"
#include "../statesGrasp/StateObjectRecognition.h"
#include "../YoubotModel.h"

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

	if(laserScan->ranges[256]<0.07)
	{
		_closeEnough = true;
		std::cout << "Unter 6cm" << std::endl;
	}
	else
	{
		_closeEnough = false;
	}
}

void StateApproachSA::onEntry()
{
	_closeEnough = false;
	_vel.linear.x = 0.03;
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
		ROS_INFO_STREAM("SM(ApproachSA): Close enough. Go to State ObjectRecognition");
		_agent->transitionToVolatileState(new StateObjectRecognition(_model));
	}
}
