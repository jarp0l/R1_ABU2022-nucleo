/*
 * motorencoded.cpp
 *
 *  Created on: May 1, 2022
 *      Author: fady
 */

#include <motorencoded.h>
#include <stdio.h>

motor_encoded::motor_encoded(Motor_config *m_config, Encoder_config *e_config)
    : motors(m_config) {
    this->m_encoderconfig = e_config;
}

motor_encoded::motor_encoded() {}

void motor_encoded::motorEncodedInit(Motor_config *m_config,
                                     Encoder_config *e_config) {
    this->m_motorconfig = m_config;
    this->m_encoderconfig = e_config;
}

int motor_encoded::getEncoderPulses() {
    return this->m_encoderconfig->encTimer->Instance->CNT;
}

float motor_encoded::getAngle() {
    return this->getEncoderPulses() * 360.0 * 2 / this->m_encoderconfig->ppr;
}

int motor_encoded::getPulseNeeded(float angle) {
    return this->m_encoderconfig->ppr * angle / (360 * 2);
}

void motor_encoded::setAngle(float angle) {
    this->m_encoderconfig->angle = angle;
}

void motor_encoded::runAngle() {
    int pulsesNeeded = getPulseNeeded(this->m_encoderconfig->angle);
    int pulsesFound = getEncoderPulses();

    // printf("Angle = %d, PulsesNeeded = %d, PulsesFound = %d\n",
    // this->m_encoderconfig->angle, pulsesNeeded, pulsesFound);

    if (pulsesFound == pulsesNeeded || (pulsesFound >= pulsesNeeded * 0.99 &&
                                        pulsesFound <= pulsesNeeded * 1.01)) {
        this->setSpeedPercentage(0);
    } else if (pulsesFound >= pulsesNeeded * 1.1) {
        this->setSpeedDir(30, CLOCKWISE);
    } else if (pulsesFound >= pulsesNeeded * 1.05) {
        this->setSpeedDir(20, CLOCKWISE);
    } else if (pulsesFound >= pulsesNeeded * 1.03) {
        this->setSpeedDir(10, CLOCKWISE);
    } else if (pulsesFound >= pulsesNeeded * 1.01) {
        this->setSpeedDir(5, CLOCKWISE);
    } else if (pulsesFound <= pulsesNeeded * 0.9) {
        this->setSpeedDir(30, ANTICLOCKWISE);
    } else if (pulsesFound <= pulsesNeeded * 0.93) {
        this->setSpeedDir(20, ANTICLOCKWISE);
    } else if (pulsesFound <= pulsesNeeded * 0.95) {
        this->setSpeedDir(10, ANTICLOCKWISE);
    } else if (pulsesFound <= pulsesNeeded * 0.99) {
        this->setSpeedDir(5, ANTICLOCKWISE);
    } else {
        this->setSpeedPercentage(0);
    }
    this->run();
}

motor_encoded::~motor_encoded() {
    // TODO Auto-generated destructor stub
}

void motor_encoded::initEncoderTim() {
    HAL_TIM_Encoder_Start_IT(this->m_encoderconfig->encTimer, TIM_CHANNEL_ALL);
    this->m_encoderconfig->encTimer->Instance->CNT = 0;
}
