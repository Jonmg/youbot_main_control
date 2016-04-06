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

class YoubotModel;

class StateIdle: public StateBaseYoubot
{
public:
	StateIdle(YoubotModel* const model);
	virtual ~StateIdle();

	void onActive();

private:
	ros::ServiceClient _clientPopTaskVector;
	bool _newGoal;
	geometry_msgs::PoseStamped _goal;
};

#endif /* STATEIDLE_H_ */
