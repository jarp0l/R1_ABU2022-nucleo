/*
 * motors.h
 *
 *  Created on: Apr 28, 2022
 *      Author: fady
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "tim.h"

enum Direction { CLOCKWISE, ANTICLOCKWISE };

typedef struct {
    GPIO_TypeDef *dirPort;
    uint16_t dirPin;
    TIM_HandleTypeDef *pwmTim;
    int pwmTimChannel;
    int pwmFullSignal;
    int pwmSignal;
    Direction rotationDir;
} Motor_config;

class motors {
  public:
    motors();
    motors(Motor_config *m_config);
    void motorinit(Motor_config *m_config);
    void setSpeedPercentage(int percentage);
    void setDirection(Direction dir);
    void setSpeedDir(int percentage, Direction dir);
    void stop();
    void run();
    void initTim();
    ~motors();

  protected:
    Motor_config *m_motorconfig;
};

#endif /* INC_MOTORS_H_ */
