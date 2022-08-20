#ifndef C46DB521_2CFF_456E_AB55_7E46B92BD902
#define C46DB521_2CFF_456E_AB55_7E46B92BD902

#include "motorgeared.h"
#include "motors.h"

typedef struct {
    motors roller[2];
    motor_geared pitchMotor;
    motor_geared yawMotor;

    Motor_config rollerConfig[2];
    Motor_config pitchConfig;
    Motor_config yawConfig;

    Encoder_config pitchEncoderConfig;
    Encoder_config yawEncoderConfig;
} RobotState;

#endif /* C46DB521_2CFF_456E_AB55_7E46B92BD902 */
