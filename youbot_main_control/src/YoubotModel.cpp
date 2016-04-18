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


void YoubotModel::addSubTasks(const youbot_msgs::SubTaskVector subTaskVector)
{
	_subTaskVector = subTaskVector;
}

bool YoubotModel::getSubTasks(youbot_msgs::SubTaskVector& subTaskVector)
{
	if(!_subTaskVector.subtasks.size())
	{
		return false;
	}
	subTaskVector = _subTaskVector;
	return true;
}

void YoubotModel::setActualSubTask(youbot_msgs::SubTask task)
{
	_actualSubTask = task;
}

void YoubotModel::getActualSubTask(youbot_msgs::SubTask& task)
{
	task = _actualSubTask;
}


