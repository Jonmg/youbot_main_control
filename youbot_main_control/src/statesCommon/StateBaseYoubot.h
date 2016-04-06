/*
 * StateBaseYoubot.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEBASEYOUBOT_H_
#define STATEBASEYOUBOT_H_

#include <ros/ros.h>
#include "obcore/statemachine/states/StateBase.h"

class YoubotModel;

class StateBaseYoubot : public obvious::StateBase
{
public:
	/**
		 * Constructor
		 * @param model : YoubotModel
		 */
	StateBaseYoubot(YoubotModel* const model);

	/**
		 * Destructor
		 */
	virtual ~StateBaseYoubot();

protected:
	YoubotModel* const _model;

	ros::NodeHandle* const _nh;
	ros::NodeHandle* const _prvNh;

	enum IdStatePersistant
	{
		STATE_NEXT = 0
	};
};

#endif /* STATEBASEYOUBOT_H_ */
