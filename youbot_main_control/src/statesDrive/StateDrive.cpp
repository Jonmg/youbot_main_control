/*
 * StateDrive.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateDrive.h"
#include "StateWait.h"
#include "../YoubotModel.h"

StateDrive::StateDrive(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string sendGoalTopic;
	std::string statusTopic;
	_prvNh->param<std::string>("status_topic", statusTopic, "send_path");
	_prvNh->param<std::string>("sed_goal_topic", sendGoalTopic, "status");

	_goalPub = _nh->advertise<geometry_msgs::PoseStamped>(sendGoalTopic, 1);
	_statusSub = _nh->subscribe(statusTopic, 1, &StateDrive::statusCallback, this);
}

StateDrive::~StateDrive()
{

}

void StateDrive::statusCallback(const actionlib_msgs::GoalStatusArray& status)
{
	_status = status;
}

void StateDrive::onEntry()
{
	//that should be done before:

	_goal.pose.position.x = 0.0;
	_goal.pose.position.y = 0.0;
	ros::Rate rate(100);
	while(!_goalPub.getNumSubscribers())
	{
		rate.sleep();
	}
	_goalPub.publish(_goal);
	//this will start the navigationStack: PathPlanning + Navigation(PathController)
}

void StateDrive::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(drive)");

	if(_status.status_list.at(0).status == 3) //Succeed
	{
		ROS_INFO_STREAM("SM(drive): Goal reached. Go to StateNext");
		_agent->transitionToVolatileState(new StateWait(_model));
	}
}
