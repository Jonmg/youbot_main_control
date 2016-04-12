/*
 * StateInit.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateInit.h"
#include "StateIdle.h"
#include "../YoubotModel.h"

StateInit::StateInit(YoubotModel* const model, const unsigned int robotId):
StateBaseYoubot(model), //is it required?
_robotId(robotId)
{
	// TODO The initializations should be done: Map, Pose (done)... everything should be available here
}

StateInit::~StateInit() {

}

void StateInit::onActive()
{
  ROS_INFO_THROTTLE(2, "SM(Init)");

  //	_agent->transitionToVolatileState(new StateIdle(_model));
  //	return;

  geometry_msgs::PoseStamped pose;
  if(_model->getCurrentPose(&pose, 5.0))
  {
    if(isnan(pose.pose.position.x))
    {
      ROS_INFO_STREAM("SM(init): No valid pose yet..." << std::endl);
      return;
    }
    else
    {
      ROS_INFO_STREAM("SM(init): Received pose -> transition to state idle..." << std::endl);
      _agent->transitionToVolatileState(new StateIdle(_model));
    }
  }
}
