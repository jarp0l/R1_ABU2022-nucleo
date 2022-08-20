/*
 * motorgeared.h
 *
 *  Created on: May 6, 2022
 *      Author: fady
 */

#ifndef INC_MOTORGEARED_H_
#define INC_MOTORGEARED_H_

#include "fuzzy.h"
#include "motorencoded.h"
#include "pid.h"

typedef enum { CONTINUOUS, DISCRETE, FUZZY } pid_algo;

class motor_geared : public motor_encoded {
  public:
    motor_geared();
    motor_geared(Motor_config *m_config, Encoder_config *e_config, float gr);
    void motorGearedInit(Motor_config *m_config, Encoder_config *e_config,
                         float gr);
    int16_t getAngleGeared();
    int getGearedPulseNeeded(float angle);
    void setAngleGeared(float angle);
    ~motor_geared();
    void runGeared();

    void setContinousPIDConstrain(float kp, float ki, float kd, float Min,
                                  float Max, int pon = P_ON_E,
                                  int Mode = AUTOMATIC,
                                  int Direction = DIRECT) {
        c_pid.SetOutputLimits(Min, Max);
        c_pid.SetMode(Mode);
        c_pid.SetControllerDirection(Direction);
        c_pid.SetTunings(kp, ki, kd, pon);
    }
    void setDiscretePIDConstrain(float kp, float ki, float kd, float Min,
                                 float Max) {
        d_pid.SetOutputLimits(Min, Max);
        d_pid.SetTunings(kp, ki, kd);
    }
    void setFuzzyPIDConstrain(float kpMax, float kiMax, float kdMax,
                              float e_max, float de_max) {
        f_pid.set_parameter(kpMax, kiMax, kdMax, e_max, de_max);
    }
    void setPulseFinal(int pulse);

  private:
    float gearRatio;
    continuous_PID c_pid;
    discrete_PID d_pid;
    fuzzy_pid f_pid;
    float angle;
    pid_algo algo;
};

#endif /* INC_MOTORGEARED_H_ */