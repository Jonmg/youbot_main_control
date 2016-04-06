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

class YoubotModel;

class StateDrive: public StateBaseYoubot
{
public:
	StateDrive(YoubotModel* const model);
	virtual ~StateDrive();

	virtual void onEntry();
	virtual void onActive();
private:
	void statusCallback(const actionlib_msgs::GoalStatusArray& status);

	ros::Publisher _goalPub;
	ros::Subscriber _statusSub;

	actionlib_msgs::GoalStatusArray _status;
	geometry_msgs::PoseStamped _goal; //it should come directly from
};

#endif /* STATEDRIVE_H_ */
