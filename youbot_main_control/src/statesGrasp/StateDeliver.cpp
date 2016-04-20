/*
 * StateDeliver.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: jon
 */

#include "StateDeliver.h"
#include "../statesCommon/StateReturnSA.h"
#include "../YoubotModel.h"

StateDeliver::StateDeliver(YoubotModel* const model) :
StateBaseYoubot(model)
{
	std::string deliverObjectTopic;
	_prvNh->param<std::string>("deliver_object_topic", deliverObjectTopic, "deliverObject");

	//_deliverObjectclient = _nh->serviceClient<youbot_msgs::grabObject>(deliverObjectTopic);
}

StateDeliver::~StateDeliver()
{

}

void StateDeliver::onEntry()
{
	_model->getActualSubTask(_subTask);
}

void StateDeliver::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(Deliver)");

	sleep(3);
	_agent->transitionToVolatileState(new StateReturnSA(_model));
	return;


}
