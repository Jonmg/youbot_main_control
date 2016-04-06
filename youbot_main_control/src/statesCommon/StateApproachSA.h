/*
 * StateApproachSA.h
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#ifndef STATEAPPROACHSA_H_
#define STATEAPPROACHSA_H_

#include "../statesCommon/StateBaseYoubot.h"
#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/Twist.h"

class YoubotModel;

class StateApproachSA: public StateBaseYoubot
{
public:
	StateApproachSA(YoubotModel* const model);
	virtual ~StateApproachSA();

	virtual void onEntry();
	virtual void onActive();

private:
	void laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan);

	ros::Publisher _velPub;
	ros::Subscriber _laserSub;

	geometry_msgs::Twist _vel;

	bool _closeEnough;
};

#endif /* STATEAPPROACHSA_H_ */

