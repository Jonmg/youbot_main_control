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
StateBaseYoubot(model)
{

}

StateNext::~StateNext() {
	// TODO Auto-generated destructor stub
}

void StateNext::onEntry()
{
	_model->getTask(_task);
}

void StateNext::onActive(void)
{
	ROS_INFO_THROTTLE(2, "SM(next)");

	if (_task.testtype == "D")
	{
		ROS_INFO_STREAM("SM(next): task type = 'D'. Go to State Drive");
		_agent->transitionToVolatileState(new StateDrive(_model));
	}
	else if (_task.testtype == "G")
	{
		ROS_INFO_STREAM("SM(next): Received pose -> transition to state idle..." << std::endl);
		_agent->transitionToVolatileState(new StateApproachSA(_model));
	}
}
