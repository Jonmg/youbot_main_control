/*
 * StateInit.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEINIT_H_
#define STATEINIT_H_

#include "StateBaseYoubot.h"
#include "geometry_msgs/PoseStamped.h"
#include <string>

class YoubotModel;

class StateInit: public StateBaseYoubot
{
public:
	StateInit(YoubotModel* const model, const unsigned int robotId);

	virtual ~StateInit();

	//ToDo: void onEntry();

	void onActive();

private:

	unsigned int _robotId;
};

#endif /* STATEINIT_H_ */
