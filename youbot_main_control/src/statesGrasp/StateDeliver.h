/*
 * StateDeliver.h
 *
 *  Created on: Apr 16, 2016
 *      Author: jon
 */

#ifndef STATEDELIVER_H_
#define STATEDELIVER_H_

#include "../statesCommon/StateBaseYoubot.h"
#include "youbot_msgs/SubTask.h"

class YoubotModel;


class StateDeliver: public StateBaseYoubot
{
public:
	StateDeliver(YoubotModel* const model);
	virtual ~StateDeliver();

	virtual void onEntry();
	virtual void onActive();

private:

	ros::ServiceClient _deliverObjectclient;

	youbot_msgs::SubTask _subTask;
};

#endif /* STATEDELIVER_H_ */
