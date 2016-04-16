/*
 * StateGrasp.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateGrasp.h"
#include "../statesCommon/StateReturnSA.h"
#include "youbot_msgs/grabObject.h"
#include "../YoubotModel.h"

StateGrasp::StateGrasp(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string graspObjectTopic;
	_prvNh->param<std::string>("grasp_object_topic", graspObjectTopic, "grabObject");

	_graspObjectclient = _nh->serviceClient<youbot_msgs::grabObject>(graspObjectTopic);
}

StateGrasp::~StateGrasp()
{

}

void StateGrasp::onEntry()
{
	_model->getActualSubTask(_subTask);
}

void StateGrasp::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(Grasp)");

	sleep(3);
	_agent->transitionToVolatileState(new StateReturnSA(_model));
	return;

	youbot_msgs::grabObject	srvArm;

	srvArm.request.start.data = true;
	srvArm.request.object.data = _subTask.objectType.data();
	_graspObjectclient.call(srvArm);
	if (srvArm.response.finished.data)
	{
		ROS_INFO_STREAM("SM(Grasp): Object grasped. Go to StateReturnSA");
		_agent->transitionToVolatileState(new StateReturnSA(_model));
	}
}
