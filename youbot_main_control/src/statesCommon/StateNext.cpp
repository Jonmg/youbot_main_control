/*
 * StateNext.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateNext.h"
#include "StateIdle.h"
//#include "statesDrive/StatePlan.h"
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
	ROS_INFO_STREAM_ONCE("SM(next): OnEntry");

	//ToDo: copy taskVector form Model
}

void StateNext::onActive(void)
{

}
