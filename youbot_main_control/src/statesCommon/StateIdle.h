/*
 * StateIdle.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEIDLE_H_
#define STATEIDLE_H_

#include "StateBaseYoubot.h"
#include "geometry_msgs/PoseStamped.h"
#include "youbot_msgs/Task.h"

class YoubotModel;

class StateIdle: public StateBaseYoubot
{
public:
	StateIdle(YoubotModel* const model);
	virtual ~StateIdle();

	void onActive();

private:
	void taskCallback(const youbot_msgs::Task::ConstPtr& task);

	ros::Subscriber _taskSub;

	bool _newGoal;
	bool _firstTime;
	geometry_msgs::PoseStamped _goal;
};

#endif /* STATEIDLE_H_ */
