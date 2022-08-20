/*
 * robooperation.cpp
 *
 *  Created on: May 7, 2022
 *      Author: fady
 */

#include <robooperation.h>

void roboPlay(RobotState *robot_state, JoystickState *joystick_state) {
    initAllMotors(robot_state);
    initTim(robot_state);
    initJoyStick(joystick_state);

    while (1) {
        runRollers(robot_state, 87);
        joystick_state->joystick.parse_JoyData(robot_state);
        runAllMotors(robot_state);
    }
}

void runAllMotors(RobotState *robot_state) {
    robot_state->roller[0].run();
    robot_state->roller[1].run();
    robot_state->pitchMotor.runGeared();
    robot_state->yawMotor.runGeared();
    // robot_state->yawMotor.run();
}

void runRollers(RobotState *robot_state, int speed) {
    robot_state->roller[0].setSpeedDir(speed, ANTICLOCKWISE);
    robot_state->roller[1].setSpeedDir(speed, CLOCKWISE);
}

void initJoyStick(JoystickState *joystick_state) {
    joystick_state->gJoyStick.huart = &huart1;
    joystick_state->joystick.set_config(&(joystick_state->gJoyStick));
    joystick_state->joystick.init();
}
