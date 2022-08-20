/*
 * motorencoded.h
 *
 *  Created on: May 1, 2022
 *      Author: fady
 */

#ifndef INC_MOTORENCODED_H_
#define INC_MOTORENCODED_H_

#include "motors.h"

typedef struct {
    TIM_HandleTypeDef *encTimer;
    GPIO_TypeDef *ch1Port;
    uint16_t ch1Pin;
    GPIO_TypeDef *ch2Port;
    uint16_t ch2Pin;
    uint16_t ppr;
    float angle;
} Encoder_config;

class motor_encoded : public motors {
  public:
    motor_encoded(Motor_config *m_config, Encoder_config *e_config);
    motor_encoded();
    void motorEncodedInit(Motor_config *m_config, Encoder_config *e_config);
    ~motor_encoded();
    int getEncoderPulses();
    float getAngle();
    int getPulseNeeded(float angle);
    void setAngle(float angle);
    void initEncoderTim();
    void runAngle();

  protected:
    Encoder_config *m_encoderconfig;
};

#endif /* INC_MOTORENCODED_H_ */
