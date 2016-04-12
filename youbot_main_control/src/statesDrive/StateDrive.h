/*
 * StateDrive.h
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#ifndef STATEDRIVE_H_
#define STATEDRIVE_H_

#include "../statesCommon/StateBaseYoubot.h"
#include "geometry_msgs/PoseStamped.h"
#include "actionlib_msgs/GoalStatusArray.h"
#include "youbot_msgs/Task.h"
#include "ats_msgs/path_ctrl_status.h"

class YoubotModel;

class StateDrive: public StateBaseYoubot
{
public:
	StateDrive(YoubotModel* const model);
	virtual ~StateDrive();

	virtual void onEntry();
	virtual void onActive();
private:
	void statusNavStackCallback(const actionlib_msgs::GoalStatusArray& status);
	void statusPathControlCallback(const ats_msgs::path_ctrl_status& status);
	void interpretatePosition ();
	void readFromTXTfile();
	double stringToDouble(std::string s);

	ros::Publisher _goalPub;
	ros::Subscriber _statusSub;
	ros::ServiceClient _serviceClientCreatePath;
	ros::ServiceClient _sendPathClient;
	ros::Subscriber _subStatusPathCtrl;

	actionlib_msgs::GoalStatusArray _statusNavStack;
	ats_msgs::path_ctrl_status _statusPathControl;
	geometry_msgs::PoseStamped _goal; //it should come directly from
	youbot_msgs::Task _task;
	std::string _filepath;
};

#endif /* STATEDRIVE_H_ */
