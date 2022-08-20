/*
 * motorgeared.cpp
 *
 *  Created on: May 6, 2022
 *      Author: fady
 */

#include <motorgeared.h>
#include <pid.h>
#include <stdio.h>

#include <cmath>

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

motor_geared::motor_geared() {}

motor_geared::motor_geared(Motor_config *m_config, Encoder_config *e_config,
                           float gr)
    : motor_encoded(m_config, e_config) {
    this->gearRatio = gr;
}

int16_t motor_geared::getAngleGeared() {
    return ((int16_t)this->getEncoderPulses()) * 360 * 2 /
           (this->m_encoderconfig->ppr * this->gearRatio);
}

void motor_geared::setAngleGeared(float angle) {
    this->m_encoderconfig->angle = angle;
}

int motor_geared::getGearedPulseNeeded(float angle) {
    return this->m_encoderconfig->ppr * this->gearRatio * angle / (360 * 2);
}

void motor_geared::runGeared() {
    int pulsesNeeded = getGearedPulseNeeded(this->m_encoderconfig->angle);
    int pulsesFound = getEncoderPulses();
    int output;

    algo = FUZZY;

    if (algo == CONTINUOUS) {
        setContinousPIDConstrain(1, 0, 0, 0, 500);
        output = c_pid.Compute(pulsesNeeded, pulsesFound);
    } else if (algo == DISCRETE) {
        setDiscretePIDConstrain(1, 0, 0, 0, 500);
        output = d_pid.Compute(pulsesNeeded, pulsesFound);
    } else if (algo == FUZZY) {
        setFuzzyPIDConstrain(1, 0, 0, 0, 500);
        output = f_pid.compute_fuzzy_selfTuning_PID(pulsesNeeded, pulsesFound);
    }
    output = pulsesNeeded;
    setPulseFinal(output);

    // printf("Angle = %d, PulsesNeeded = %d, PulsesFound = %d\n",
    // (int)this->m_encoderconfig->angle, pulsesNeeded, (int)pulsesFound);
    this->run();
    angle = getAngle();
}

void motor_geared::setPulseFinal(int pulse) {
    int pulsesNeeded = pulse;
    int pulsesFound = getEncoderPulses();

    float highthresholdMax = 1.05;
    float highthresholdMin = 1.01;
    float lowthresholdMax = 0.95;
    float lowthersholdMin = 0.99;

    float velPercentage = 100;

    if (pulsesFound >= pulsesNeeded * highthresholdMax) {
        this->setSpeedDir(velPercentage, ANTICLOCKWISE);
    } else if (pulsesFound <= pulsesNeeded * lowthresholdMax) {
        this->setSpeedDir(velPercentage, CLOCKWISE);
    } else if (pulsesFound < pulsesNeeded * highthresholdMin &&
               pulsesFound > pulsesNeeded * lowthersholdMin) {
        this->setSpeedDir(0, ANTICLOCKWISE);
    } else {
        this->setSpeedDir(fabs(map(pulsesFound, pulsesNeeded * lowthresholdMax,
                                   pulsesNeeded * highthresholdMax,
                                   -velPercentage, velPercentage)),
                          (pulsesFound > pulsesNeeded) ? ANTICLOCKWISE
                                                       : CLOCKWISE);
    }
}

void motor_geared::motorGearedInit(Motor_config *m_config,
                                   Encoder_config *e_config, float gr) {
    this->motorEncodedInit(m_config, e_config);
    this->gearRatio = gr;
}

motor_geared::~motor_geared() {
    // TODO Auto-generated destructor stub
}