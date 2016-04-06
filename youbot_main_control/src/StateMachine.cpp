/*
 * StateMachine.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateMachine.h"
#include "YoubotModel.h"
//#include "states/StateInit.h"
#include "geometry_msgs/PoseStamped.h"
#include <tf/tf.h>

StateMachine::StateMachine() :
_nh(new ros::NodeHandle),
_prvNh(new ros::NodeHandle("~")),
_robotId(0)
{
	geometry_msgs::PoseStamped initPose;
	double initYaw = 0.0;
	double rateVar = 0.0;
	int iVar = 0;

	_prvNh->param<std::string>("tf_base_frame", _tfBaseFrame, "map");
	_prvNh->param<std::string>("tf_robot_frame", _tfRobotFrame, "base_footprint");
	_prvNh->param<double>("init_pose_x", initPose.pose.position.x, 0.0);
	_prvNh->param<double>("init_pose_y", initPose.pose.position.y, 0.0);
	_prvNh->param<double>("init_pose_yaw", initYaw, 0.0);
	_prvNh->param<double>("loop_rate_main", rateVar, 20.0);
	_prvNh->param<int>("robot_id", iVar, 0);

	_robotId = static_cast<unsigned int>(iVar);

	tf::Quaternion quat;
	quat.setRPY(0.0, 0.0, initYaw);

	initPose.pose.orientation.w = quat.w();
	initPose.pose.orientation.x = quat.x();
	initPose.pose.orientation.y = quat.y();
	initPose.pose.orientation.z = quat.z();

	_model = new YoubotModel(initPose, _nh, _prvNh);
	_loopMain = new ros::Rate(rateVar);
}

StateMachine::~StateMachine()
{
	delete _nh;
	delete _prvNh;
	delete _model;
	delete _loopMain;
}

void StateMachine::start()
{
	//_agent.transitionToVolatileState(new StateInit(_model, _robotId));
	this->run();
}

void StateMachine::run()
{
	while(ros::ok())
	{
		ros::spinOnce();
		this->updatePose();
		_agent.awake();
		_loopMain->sleep();
	}
}

bool StateMachine::updatePose()
{
	tf::StampedTransform tf;
	geometry_msgs::PoseStamped pose;
	try
	{
		_listener.lookupTransform(_tfBaseFrame, _tfRobotFrame, ros::Time(0), tf);
		pose.pose.position.x = tf.getOrigin().x();
		pose.pose.position.y = tf.getOrigin().y();
		pose.pose.orientation.w = tf.getRotation().getW();
		pose.pose.orientation.x = tf.getRotation().getX();
		pose.pose.orientation.y = tf.getRotation().getY();
		pose.pose.orientation.z = tf.getRotation().getZ();
		_model->setPose(pose);
		return true;
	}
	catch(tf::TransformException& e)
	{
		ROS_ERROR_STREAM("SM(pose_callback): Error calling tf " << e.what() << std::endl);
		return false;
	}
	return true; //just to avoid a error in eclipse
}
