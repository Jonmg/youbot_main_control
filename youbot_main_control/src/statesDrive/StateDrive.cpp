/*
 * StateDrive.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateDrive.h"
#include "StateWait.h"
#include "../statesCommon/StateNext.h"
#include "../statesCommon/StateIdle.h"
#include "../YoubotModel.h"
#include "tf/tf.h"
#include "geometry_msgs/Point.h"
#include <string>
#include <iostream>
#include <fstream>


StateDrive::StateDrive(YoubotModel* const model):
StateBaseYoubot(model),
_filepath(" ")
{
	/*Navigation Stack:*/
	std::string statusTopic;
	std::string goalTopic;
	_prvNh->param<std::string>("move_base_status_topic", statusTopic, "move_base/status");
	_prvNh->param<std::string>("move_base_goal_topic", goalTopic, "move_base_simple/goal");
	_prvNh->param<std::string>("positions_path", _filepath, "atwork2015_places.txt");

	_goalPub = _nh->advertise<geometry_msgs::PoseStamped>(goalTopic, 1);
	_statusSub = _nh->subscribe(statusTopic, 1, &StateDrive::statusNavStackCallback, this);
}

StateDrive::~StateDrive()
{

}

void StateDrive::statusNavStackCallback(const actionlib_msgs::GoalStatusArray& status)
{
	_statusNavStack = status;
}

void StateDrive::onEntry()
{
	_model->getActualSubTask(_subTask);

	geometry_msgs::PoseStamped pose;
	pose.pose.position.x = _subTask.pose.x;
	pose.pose.position.y = _subTask.pose.y;
	tf::Quaternion pose_quat;//(0,0,z);
	pose_quat.setEuler(0,0,_subTask.pose.z);
	pose.pose.orientation.w = pose_quat.w();
	pose.pose.orientation.z = pose_quat.z();

	//ROS_INFO_STREAM("SM(drive): Goal: " << pose);

	/*NavigationStack*/
	ros::Rate rate(100);
	pose.header.frame_id = "map";
	while(!_goalPub.getNumSubscribers())
	{
		rate.sleep();
	}
	_goalPub.publish(pose);
	sleep(1);
}

void StateDrive::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(drive)");
	ros::spinOnce();
	if(_statusNavStack.status_list.size() != 0)
	{
		if((_statusNavStack.status_list.back().status == 3)) //Succeed
		{

			_statusNavStack.status_list.clear();
			ROS_INFO_STREAM("SM(drive): Goal reached. Go to StateNext");
			_agent->transitionToPersistantState(STATE_NEXT);
		}
	}
}

