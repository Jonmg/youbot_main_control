/*
 * StateReturnSA.h
 *
 *  Created on: Apr 6, 2016
 *      Author: jon
 */

#ifndef STATERETURNSA_H_
#define STATERETURNSA_H_

#include "../statesCommon/StateBaseYoubot.h"
#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/Twist.h"

class YoubotModel;

class StateReturnSA: public StateBaseYoubot
{
public:
	StateReturnSA(YoubotModel* const model);
	virtual ~StateReturnSA();

	virtual void onEntry();
	virtual void onActive();

private:
	void laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan);

	ros::Publisher _velPub;
	ros::Subscriber _laserSub;

	geometry_msgs::Twist _vel;

	bool _farEnough;
};

#endif /* STATERETURNSA_H_ */
