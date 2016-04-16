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
_firstTime(true)
{
	std::string taskTopic;
	_prvNh->param<std::string>("sub_task_topic", taskTopic, "subTask");

	_taskSub = _nh->subscribe(taskTopic, 1, &StateIdle::taskCallback, this);
}

StateIdle::~StateIdle()
{

}

void StateIdle::taskCallback(const youbot_msgs::SubTaskVector::ConstPtr& task)
{
	if (_firstTime)
	{
		_firstTime =false;
		_model->addSubTasks(*task);
		ROS_INFO_STREAM("SM(idle): subTasks: " << *task);
	}
}

void StateIdle::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(Idle)");

	if (!_firstTime)
	{
	ROS_INFO_STREAM("SM(idle): New task received -> transition to StateNext...");
	_agent->registerPersistantState(STATE_NEXT, new StateNext(_model)); //just one time, no??
	_agent->transitionToPersistantState(STATE_NEXT);
	_firstTime = true;//is it necessary as it is not a persistent state?
	}
}
