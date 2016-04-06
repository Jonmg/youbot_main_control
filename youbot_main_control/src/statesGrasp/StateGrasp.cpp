/*
 * StateGrasp.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateGrasp.h"
//#include "StateReturnSA.h"
#include "youbot_msgs/grabObject.h"
#include "../YoubotModel.h"

StateGrasp::StateGrasp(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string graspObjectTopic;
	_prvNh->param<std::string>("set_pose_topic", graspObjectTopic, "grabObject");

	_graspObjectclient = _nh->serviceClient<youbot_msgs::grabObject>(graspObjectTopic);
}

StateGrasp::~StateGrasp()
{

}

void StateGrasp::onEntry()
{

}

void StateGrasp::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(Grasp)");

	youbot_msgs::grabObject	srvArm;

	srvArm.request.start.data = true;
	srvArm.request.object.data = _objectType;
	_graspObjectclient.call(srvArm);
	if (srvArm.response.finished.data)
	{
		ROS_INFO_STREAM("SM(Grasp): Object grasped. Go to StateReturnSA");
		//_agent->transitionToVolatileState(new StateReturnSA(_model));
	}

}
