/*
 * StateDrive.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateDrive.h"
#include "StateWait.h"
#include "../statesCommon/StateIdle.h"
#include "../YoubotModel.h"
#include "tf/tf.h"
#include "ats_msgs/CreatePath.h"
#include "ats_msgs/SendPath.h"

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

void StateDrive::statusPathControlCallback(const ats_msgs::path_ctrl_status& status)
{
	_statusPathControl = status;
}

void StateDrive::onEntry()
{
	if(!_model->getNextTask(_task))
	{
		ROS_ERROR_STREAM("SM(drive): Error! Could not load task out of model");
		//_agent->transitionToVolatileState(new StateIdle(_model));
		return;
	}
	else
		ROS_INFO_STREAM("SM(drive): Task: " << _task);

	//interpretatePosition();
	readFromTXTfile();

	ROS_INFO_STREAM("SM(drive): Goal: " << _goal);

	/*NavigationStack*/
	ros::Rate rate(100);
	_goal.header.frame_id = "map";
	while(!_goalPub.getNumSubscribers())
	{
		rate.sleep();
	}
	_goalPub.publish(_goal);

}

void StateDrive::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(drive)");
	if(_statusNavStack.status_list.size() != 0)
	{
		if((_statusNavStack.status_list.at(0).status == 3)) //Succeed
		{
			ROS_INFO_STREAM("SM(drive): Goal reached. Go to StateNext");
			_agent->transitionToVolatileState(new StateWait(_model));
		}

	}
}

void StateDrive::interpretatePosition ()
{
	std::string sPose = _task.sequences.at(0).destination_location;
	std::string sOrientation = _task.sequences.at(0).orientation;

	if (sPose == "S1")
	{
		_goal.pose.position.x = 2.75;
		_goal.pose.position.y = 5.5;
	}
	else if (sPose == "S2")
	{
		_goal.pose.position.x = 2.75;
		_goal.pose.position.y = 7.5;
	}
	else
	{
		ROS_ERROR_STREAM("SM(next): Fatal error unknown command ");
		return;
	}

	double zd = 0;
	if (sOrientation == "N")
		zd = (0);
	else if (sOrientation == "W")
		zd = (1.57);
	else if (sOrientation == "S")
		zd = (3.14);
	else if (sOrientation == "E")
		zd = (-1.57);
	//const tfScalar z(zd);
	tf::Quaternion pose_quat;//(0,0,z);
	pose_quat.setEuler(0,0,zd);
	_goal.pose.orientation.w = pose_quat.w();
	_goal.pose.orientation.z = pose_quat.z();
}

void StateDrive::readFromTXTfile()
{
	std::string sPose = _task.sequences.at(0).destination_location;

	std::string word;
	std::vector<std::string> zeile;

	const char *charFilename = _filepath.c_str();

	std::fstream file;
	file.open(charFilename, std::ios::in);
	if(!file.is_open())
	{
		ROS_INFO_STREAM("file could not be open. Path: " << _filepath);
		return;
	}

	while (file >> word)
	{
		if (sPose == word)
		{
			for (unsigned i=0; i<8; i++)
			{
				if (i == 2)
				{
					_goal.pose.position.x = stringToDouble(word);
				}
				if (i == 4)
				{
					_goal.pose.position.y = stringToDouble(word);
				}
				if (i == 6)
				{
					tf::Quaternion pose_quat;//(0,0,z);
					pose_quat.setEuler(0,0,stringToDouble(word));
					_goal.pose.orientation.w = pose_quat.w();
					_goal.pose.orientation.z = pose_quat.z();
					break;
				}

				file >> word;
			}
			break;
		}
	}
	ROS_INFO_STREAM("The resultant _goal is:" << _goal);

	file.close();
}

double StateDrive::stringToDouble(std::string s) {
	double d;
	std::stringstream ss(s); //turn the string into a stream
	ss >> d; //convert
	return d;
}
