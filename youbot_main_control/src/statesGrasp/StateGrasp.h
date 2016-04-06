/*
 * StateGrasp.h
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#ifndef STATEGRASP_H_
#define STATEGRASP_H_

#include "../statesCommon/StateBaseYoubot.h"

class YoubotModel;

class StateGrasp: public StateBaseYoubot
{
public:
	StateGrasp(YoubotModel* const model);
	virtual ~StateGrasp();

	virtual void onEntry();
	virtual void onActive();

private:

		ros::ServiceClient _graspObjectclient;

		std::string _objectType;
};

#endif /* STATEGRASP_H_ */
