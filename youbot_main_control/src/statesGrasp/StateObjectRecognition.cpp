/*
 * StateObjectRecognition.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#include "StateObjectRecognition.h"
#include "StateGrasp.h"
#include "../statesCommon/StateIdle.h"
#include "youbot_msgs/setPose.h"
#include "youbot_msgs/getObjectPosition.h"
#include "../YoubotModel.h"

StateObjectRecognition::StateObjectRecognition(YoubotModel* const model):
StateBaseYoubot(model)
{
	std::string setPoseTopic;
	std::string findObjectTopic;
	_prvNh->param<std::string>("set_pose_topic", setPoseTopic, "setPose");
	_prvNh->param<std::string>("find_objet_topic", findObjectTopic, "status");

	_SetPoseArmclient = _nh->serviceClient<youbot_msgs::setPose>("setPose");
	_SearchObjectclient = _nh->serviceClient<youbot_msgs::getObjectPosition>("getObject"); //change with "findObject"
}

StateObjectRecognition::~StateObjectRecognition()
{

}

void StateObjectRecognition::onEntry()
{

}

void StateObjectRecognition::onActive()
{
	ROS_INFO_THROTTLE(2, "SM(ObjectRecognition)");

	_agent->transitionToVolatileState(new StateGrasp(_model));
	return;

	youbot_msgs::setPose pose;
	pose.request.start.data = true;
	pose.request.ArmPose.data = "nearsearchpos";
	_SetPoseArmclient.call(pose);

	if (pose.response.finished.data == true)
	{
		std::cout << " searching for object..." << std::endl;
		youbot_msgs::getObjectPosition srvVision;
		srvVision.request.start.data = true;
		srvVision.request.object.data = _objectType;
		_SearchObjectclient.call(srvVision);

		if(srvVision.response.found.data)
		{
			ROS_INFO_STREAM("SM(ObjectRecognition): Object found. Go to StateGrasp");
			_agent->transitionToVolatileState(new StateGrasp(_model));
		}
	}
}
