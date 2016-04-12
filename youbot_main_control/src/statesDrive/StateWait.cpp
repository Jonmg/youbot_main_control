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
	//watingTime = model->getWaitingTime();
	ros::Duration waitingTime(3); //just for now. It has to be tested also
	_finalTime = ros::Time::now() + waitingTime;
}

void StateWait::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(StateWait)");
	ros::Duration timeLeft = _finalTime - ros::Time::now();

	if(timeLeft  <=  ros::Duration(0)) //Succeed
	{
		ROS_INFO_STREAM("SM(drive): Waiting time finished. Go to StateNext");
		_model->deleteNextTask();
		_agent->transitionToPersistantState(STATE_NEXT);
	}
	else
		ROS_INFO_THROTTLE(1, "Waiting " );
}
