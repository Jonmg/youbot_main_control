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
#include "youbot_msgs/SubTaskVector.h"

class YoubotModel;

class StateIdle: public StateBaseYoubot
{
public:
	StateIdle(YoubotModel* const model);
	virtual ~StateIdle();

	void onActive();

private:
	void taskCallback(const youbot_msgs::SubTaskVector::ConstPtr& task);

	ros::Subscriber _taskSub;
	ros::ServiceClient _subTaskVectorClient;

	bool _firstTime;
};

#endif /* STATEIDLE_H_ */
