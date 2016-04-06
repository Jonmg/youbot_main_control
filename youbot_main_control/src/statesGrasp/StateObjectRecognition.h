/*
 * StateObjectRecognition.h
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#ifndef STATEOBJECTRECOGNITION_H_
#define STATEOBJECTRECOGNITION_H_

#include "../statesCommon/StateBaseYoubot.h"

class YoubotModel;

class StateObjectRecognition: public StateBaseYoubot
{
public:
	StateObjectRecognition(YoubotModel* const model);
	virtual ~StateObjectRecognition();

	virtual void onEntry();
	virtual void onActive();

private:

	ros::ServiceClient _SetPoseArmclient;
	ros::ServiceClient _SearchObjectclient;

	std::string _objectType;
};

#endif /* STATEOBJECTRECOGNITION_H_ */



