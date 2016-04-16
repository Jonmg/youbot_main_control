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

#include "youbot_msgs/SubTask.h"
#include "youbot_msgs/SubTaskVector.h"

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
	 * Add TaskVecdtor
	 * @param target target
	 */
	void addTask(const youbot_msgs::Task taskVector);

	/**
	 * Get next taskVector. If no target is assigned, NULL is returned.
	 * @param taskVector next taskVector
	 * @return success
	 */
	bool getNextTask(youbot_msgs::Task& taskVector);

	/**
	 * Delete next taskVector. If no target is assigned, NULL is returned.
	 * @param taskVector next taskVector
	 * @return success
	 */
	bool deleteNextTask();

	/**
	 * Get the Single task
	 */
	void getSingleTask(youbot_msgs::Task& task);

	/**
	 * Set the Single task
	 */
	void setSingleTask(youbot_msgs::Task task);

	/**
		 * set subTasks.
		 * @param SubTaskVector
		 * @return success
		 */
	void addSubTasks(const youbot_msgs::SubTaskVector SubTaskVector);

	/**
	 * Get subTasks.
	 * @param SubTaskVector
	 * @return success
	 */
	bool getSubTasks(youbot_msgs::SubTaskVector& SubTaskVector);


	/**
	 * Set the Actual Task
	 */
	void setActualSubTask(youbot_msgs::SubTask actualSubTask);

	/**
	 * Get the Actual Task
	 */
	void getActualSubTask(youbot_msgs::SubTask& actualSubTask);



	ros::NodeHandle* const nodeHandle(void)const{return _nh;}

	ros::NodeHandle* const paramNodeHandle(void)const{return _prvNh;}

private:

	geometry_msgs::PoseStamped _pose;

	ros::NodeHandle* const _nh;

	ros::NodeHandle* const _prvNh;

	ros::Time* _lastPoseUpdate;

	std::string _actualTask;

	youbot_msgs::Task _task;

	std::vector<youbot_msgs::Task> _taskVector;

	youbot_msgs::SubTask _actualSubTask;

	youbot_msgs::SubTaskVector _subTaskVector;

};

#endif /* YOUBOTMODEL_H_ */
