/*
 * roboinitall.h
 *
 *  Created on: May 6, 2022
 *      Author: fady
 */

#ifndef INC_ROBOINITALL_H_
#define INC_ROBOINITALL_H_

#include "initentities.h"

void initRollers(RobotState *robot_state);
void initPitchYaw(RobotState *robot_state);
void initAllMotors(RobotState *robot_state);
void initTim(RobotState *robot_state);

#endif /* INC_ROBOINITALL_H_ */
