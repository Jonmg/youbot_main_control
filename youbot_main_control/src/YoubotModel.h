/*
 * YoubotModel.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef YOUBOTMODEL_H_
#define YOUBOTMODEL_H_

#include <ros/ros.h>
#include "nav_msgs/Path.h"
#include <vector>
#include "obcore/statemachine/AgentModel.h"
#include "youbot_msgs/Task.h"

class YoubotModel : public obvious::AgentModel
{

public:
	/**
	 * Constructor
	 * @param pos 3D position, orientation is set to (0, 0, 0)
	 * @param public and private node handler
	 */
	YoubotModel(const geometry_msgs::PoseStamped& initPose, ros::NodeHandle* const nh, ros::NodeHandle* const prvNh);

	/**
	 * Destructor
	 */
	virtual ~YoubotModel();

	/**
	 * Check whether pose was updated within given interval in ms
	 * @param interval time interval in seconds
	 */
	bool isPoseUpToDate(const double interval);

	/**
	 * Set position
	 * @param pos position (x, y, z)
	 */
	void setPose(const geometry_msgs::PoseStamped& pose);

	/**
	 * Access current position
	 * @param pos position (x, y, z)
	 */
	bool getCurrentPose(geometry_msgs::PoseStamped* const pose, const double age);

	/**
	 * Get the complete task
	 */
	void getTask(youbot_msgs::Task& task);

	/**
	 * Set the complete task
	 */
	void setTask(youbot_msgs::Task task);

	ros::NodeHandle* const nodeHandle(void)const{return _nh;}

	ros::NodeHandle* const paramNodeHandle(void)const{return _prvNh;}

private:

	geometry_msgs::PoseStamped _pose;

	ros::NodeHandle* const _nh;

	ros::NodeHandle* const _prvNh;

	ros::Time* _lastPoseUpdate;

	std::string _actualTask;

	youbot_msgs::Task _task;
};

#endif /* YOUBOTMODEL_H_ */
