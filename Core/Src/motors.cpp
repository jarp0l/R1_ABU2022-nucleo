/*
 * motors.cpp
 *
 *  Created on: Apr 28, 2022
 *      Author: fady
 */

#include <motors.h>

motors::motors() {}

static uint16_t time_period(uint16_t PWM_frequency) {
    if (PWM_frequency <
        2000) { // MIN PWM_FREQUENCY = 1281.738 for time period to be 16 bit
                //_Error_Handler(__FILE__, __LINE__);
    }
    return ((168000000 / 2) / PWM_frequency) -
           1; // In Center aligned mode period doubles hence we divide by 2
}

/* SET DUTYCYCLE primary function */
static void set_DutyCycle_Primary(TIM_HandleTypeDef *htim, uint32_t Channel,
                                  uint16_t dutyCycle) {
    uint16_t mapped_value;
    mapped_value = (time_period(8000) * dutyCycle) / 65535;
    // htim->Instance->CCR3=299;
    __HAL_TIM_SET_COMPARE(htim, Channel, mapped_value);
}

motors::motors(Motor_config *m_config) { this->m_motorconfig = m_config; }

void motors::motorinit(Motor_config *m_config) {
    this->m_motorconfig = m_config;
}

void motors::setSpeedPercentage(int percentage) {
    this->m_motorconfig->pwmSignal =
        this->m_motorconfig->pwmFullSignal * percentage / 100;
}

void motors::setDirection(Direction dir) {
    this->m_motorconfig->rotationDir = dir;
}

void motors::setSpeedDir(int percentage, Direction dir) {
    this->setSpeedPercentage(percentage);
    this->setDirection(dir);
}

void motors::stop() {
    __HAL_TIM_SET_COMPARE(this->m_motorconfig->pwmTim,
                          this->m_motorconfig->pwmTimChannel, 0);
}

void motors::run() {
    if (this->m_motorconfig->rotationDir == CLOCKWISE) {
        HAL_GPIO_WritePin(this->m_motorconfig->dirPort,
                          this->m_motorconfig->dirPin, GPIO_PIN_SET);
    } else if (this->m_motorconfig->rotationDir == ANTICLOCKWISE) {
        HAL_GPIO_WritePin(this->m_motorconfig->dirPort,
                          this->m_motorconfig->dirPin, GPIO_PIN_RESET);
    }
    set_DutyCycle_Primary(this->m_motorconfig->pwmTim,
                          this->m_motorconfig->pwmTimChannel,
                          this->m_motorconfig->pwmSignal);
    // __HAL_TIM_SET_COMPARE(this->m_motorconfig->pwmTim,
    // this->m_motorconfig->pwmTimChannel, this->m_motorconfig->pwmSignal);
}

motors::~motors() {
    // TODO Auto-generated destructor stub
}

void motors::initTim() {
    HAL_TIM_PWM_Start(this->m_motorconfig->pwmTim,
                      this->m_motorconfig->pwmTimChannel);
}
