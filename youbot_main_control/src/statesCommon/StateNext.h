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

class YoubotModel;

class StateNext : public StateBaseYoubot
{
public:
	StateNext(YoubotModel* const mode);

	virtual ~StateNext();

	virtual void onEntry();

	virtual void onActive();

private:

	//TaskVector* _taskVector;
};

#endif /* STATENEXT_H_ */
