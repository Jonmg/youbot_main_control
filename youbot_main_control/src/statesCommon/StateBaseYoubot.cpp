/*
 * StateBaseYoubot.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: jon
 */

#include "StateBaseYoubot.h"
#include "../YoubotModel.h"

StateBaseYoubot::StateBaseYoubot(YoubotModel* const model) :
_model(model),
_nh(model->nodeHandle()),
_prvNh(model->paramNodeHandle())
{

}

StateBaseYoubot::~StateBaseYoubot() {
	// TODO Auto-generated destructor stub
}

