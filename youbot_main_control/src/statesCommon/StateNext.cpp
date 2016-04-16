/*
 * StateNext.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateNext.h"
#include "StateIdle.h"
#include "../statesDrive/StateDrive.h"
#include "../statesDrive/StateWait.h"
#include "StateApproachSA.h"
#include "../YoubotModel.h"

StateNext::StateNext(YoubotModel* const model):
StateBaseYoubot(model),
_subTaskActualNumber(0)
{
	//ToDo: the state is almost empty, everything is to be done here
}

StateNext::~StateNext() {

}

void StateNext::onEntry()
{
	if (!_subTaskVector.subtasks.size())
	{
		if(!_model->getSubTasks(_subTaskVector))
		{
			ROS_INFO_DELAYED_THROTTLE(1, "SM(next): No more tasks to be done. Go to State Idle");
			_agent->transitionToVolatileState(new StateIdle(_model));
		}
	}
}

void StateNext::onActive(void)
{
	ROS_INFO_THROTTLE(2, "SM(next)");

	/*trial:*/
	if (!nextTask())
	{
		ROS_INFO_STREAM("SM(next): No more tasks to be done. Go to State Idle");
		_agent->transitionToVolatileState(new StateIdle(_model));
		return;
	}


	ROS_INFO_STREAM("SM(next): actualTask " << _subTaskActualNumber <<  "  :" << _actualSubTask);

	if (_actualSubTask.subTasktType == "M")
	{
		ROS_INFO_STREAM("SM(next): task type = " << _actualSubTask.subTasktType << ". Go to State Drive");
		_agent->transitionToVolatileState(new StateDrive(_model));
	}
	else if (_actualSubTask.subTasktType == "W")
	{
		ROS_INFO_STREAM("SM(next): task type = " << _actualSubTask.subTasktType << ". Go to State Wait");
		_agent->transitionToVolatileState(new StateWait(_model));
	}
	else if (_actualSubTask.subTasktType == "G")
	{
		ROS_INFO_STREAM("SM(next): task type = " << _actualSubTask.subTasktType << ". Go to State Grasp");
		_agent->transitionToVolatileState(new StateApproachSA(_model));
	}
	else if (_actualSubTask.subTasktType == "D")
	{
		ROS_INFO_STREAM("SM(next): task type = " << _actualSubTask.subTasktType << ". Go to State Deliver");
		_agent->transitionToVolatileState(new StateApproachSA(_model));
	}


	/*if(!_model->getNextTask(_task))
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
	}*/
}

bool StateNext::nextTask()
{
	if (_subTaskActualNumber == _subTaskVector.subtasks.size())
		return false;
	else
	{
		_actualSubTask = _subTaskVector.subtasks.at(_subTaskActualNumber);
		_model->setActualSubTask(_actualSubTask);
		_subTaskActualNumber++;
		return true;
	}
}
