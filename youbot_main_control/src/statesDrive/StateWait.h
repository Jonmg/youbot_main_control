/*
 * StateWait.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEWAIT_H_
#define STATEWAIT_H_

#include "../statesCommon/StateBaseYoubot.h"
#include "youbot_msgs/SubTask.h"

class YoubotModel;

class StateWait : public StateBaseYoubot
{
public:
	StateWait(YoubotModel* const model);
	virtual ~StateWait();

	virtual void onEntry();
	virtual void onActive();

private:
	ros::Time _initialTime;
	ros::Time _finalTime;

	youbot_msgs::SubTask _subTask;
};

#endif /* STATEWAIT_H_ */
