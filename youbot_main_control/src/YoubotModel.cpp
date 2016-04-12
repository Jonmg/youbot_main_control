/*
 * YoubotModel.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "YoubotModel.h"

YoubotModel::YoubotModel(const geometry_msgs::PoseStamped& initPose, ros::NodeHandle* const nh, ros::NodeHandle* const prvNh):
_pose(initPose),
_nh(nh),
_prvNh(prvNh),
_lastPoseUpdate(NULL)
{
	_actualTask.resize(2);
	_actualTask = "  ";
}
YoubotModel::~YoubotModel() {
	// TODO Auto-generated destructor stub
}

bool YoubotModel::isPoseUpToDate(const double interval)
{
	if(!_lastPoseUpdate)
		return false;
	return (ros::Time::now() - *_lastPoseUpdate).toSec() < interval;
}

void YoubotModel::setPose(const geometry_msgs::PoseStamped& pose)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	if(!_lastPoseUpdate)
		_lastPoseUpdate = new ros::Time(ros::Time::now());
	else
		*_lastPoseUpdate = ros::Time::now();
	_pose = pose;
}

bool YoubotModel::getCurrentPose(geometry_msgs::PoseStamped* const pose, const double age)
{
	if(!(this->isPoseUpToDate(age))){
		ROS_ERROR_STREAM("YoubotModel::getCurrentPose: No pose");
		return false;}
	else
	{
		*pose = _pose;
		return true;
	}
}

void YoubotModel::addTask(const youbot_msgs::Task taskVector)
{
	_taskVector.push_back(taskVector);
}

bool YoubotModel::getNextTask(youbot_msgs::Task& taskVector)
{
	if(!_taskVector.size())
	{
		return false;
	}
	taskVector = *_taskVector.begin();
	//_taskVector.erase(_taskVector.begin());
	return true;
}

bool YoubotModel::deleteNextTask()
{
	if(!_taskVector.size())
	{
		return false;
	}
	_taskVector.erase(_taskVector.begin());
	return true;
}


void YoubotModel::getSingleTask(youbot_msgs::Task& task)
{
	task = _task;
}

void YoubotModel::setSingleTask(youbot_msgs::Task task)
{
	_task = task;
}
