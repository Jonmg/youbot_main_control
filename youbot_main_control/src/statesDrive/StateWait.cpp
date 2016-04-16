/*
 * StateWait.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateWait.h"
#include "../YoubotModel.h"
#include "../statesCommon/StateNext.h"

StateWait::StateWait(YoubotModel* const model) :
StateBaseYoubot(model)
{

}

StateWait::~StateWait()
{

}

void StateWait::onEntry()
{
	_model->getActualSubTask(_subTask);
}

void StateWait::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(StateWait)");

	ros::Rate waitingTime(_subTask.waitingTime);
	waitingTime.sleep();

	ROS_INFO_STREAM("SM(drive): Waiting time finished. Go to StateNext");
	_agent->transitionToPersistantState(STATE_NEXT);

}
