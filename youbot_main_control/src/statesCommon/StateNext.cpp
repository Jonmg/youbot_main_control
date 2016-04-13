/*
 * StateNext.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateNext.h"
#include "StateIdle.h"
#include "../statesDrive/StateDrive.h"
#include "StateApproachSA.h"
#include "../YoubotModel.h"

StateNext::StateNext(YoubotModel* const model):
StateBaseYoubot(model),
_subTaskActualNumber(0),
_subTaskMaxlNumber(0),
_firstTime(true)
{
	//ToDo: the state is almost empty, everything is to be done here
}

StateNext::~StateNext() {

}

void StateNext::onEntry()
{

}

void StateNext::onActive(void)
{
	ROS_INFO_THROTTLE(2, "SM(next)");

	/*trial:
	if(_firstTime)
	{
		_firstTime = false;
		if(!_model->getNextTask(_task))
		{

			ROS_INFO_DELAYED_THROTTLE(1, "SM(next): No more tasks to be done. Go to State Idle");
			_agent->transitionToVolatileState(new StateIdle(_model));
			return;
		}
		else
		{
			_subTaskMaxlNumber = _task.sequences.size() + _task.initialsituation.size() + _task.goalsituation.size();
			_subTaskActualNumber = 0;
		}
	}

	nextTask();


		if (_task.testtype == "D")
		{
			ROS_INFO_STREAM("SM(next): task type = 'D'. Go to State Drive");
			_agent->transitionToVolatileState(new StateDrive(_model));
		}
		else if (_task.testtype == "G")
		{
			ROS_INFO_STREAM("SM(next): Received pose -> transition to state idle..." << std::endl);
			_agent->transitionToVolatileState(new StateApproachSA(_model));
		}*/


	if(!_model->getNextTask(_task))
	{
		ROS_INFO_DELAYED_THROTTLE(1, "SM(next): No more tasks to be done. Go to State Idle");
		_agent->transitionToVolatileState(new StateIdle(_model));
		return;
	}

	if (_task.testtype == "BNT")
	{
		ROS_INFO_STREAM("SM(next): task type = 'D'. Go to State Drive");
		_agent->transitionToVolatileState(new StateDrive(_model));
	}
	else if (_task.testtype == "BMT")
	{
		ROS_INFO_STREAM("SM(next): Received pose -> transition to state idle..." << std::endl);
		_agent->transitionToVolatileState(new StateApproachSA(_model));
	}
}

bool StateNext::nextTask()
{
	if (_subTaskActualNumber == _subTaskMaxlNumber)
		return false;


	return true;
}
