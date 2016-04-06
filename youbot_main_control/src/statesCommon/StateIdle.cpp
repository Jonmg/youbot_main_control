/*
 * StateIdle.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateIdle.h"
#include "StateNext.h"
#include "../YoubotModel.h"

StateIdle::StateIdle(YoubotModel* const model):
StateBaseYoubot(model),
_newGoal(false)
{
	//ToDo: add here the code for popTaskVector
}

StateIdle::~StateIdle()
{

}

void StateIdle::onActive()
{
  ROS_INFO_THROTTLE(2, "SM(Idle)");

    //_model->pushTaskVector(popTaskVector.response.taskVector);
    ROS_INFO_STREAM("SM(idle): New task received -> transition to StateNext..." << std::endl);
    _agent->registerPersistantState(STATE_NEXT, new StateNext(_model));
    _agent->transitionToPersistantState(STATE_NEXT);
    return;
}
