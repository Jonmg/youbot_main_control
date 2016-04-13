/*
 * StateNext.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATENEXT_H_
#define STATENEXT_H_

#include "StateBaseYoubot.h"
#include "geometry_msgs/PoseStamped.h"
#include "youbot_msgs/Task.h"

class YoubotModel;

class StateNext : public StateBaseYoubot
{
public:
	StateNext(YoubotModel* const mode);

	virtual ~StateNext();

	virtual void onEntry();

	virtual void onActive();

private:

	bool nextTask();

	youbot_msgs::Task _task;
	int _subTaskActualNumber;
	int _subTaskMaxlNumber;
	bool _firstTime;
};

#endif /* STATENEXT_H_ */
