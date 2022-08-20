#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include "crc_hash.h"
#include "initentities.h"
#include "queue_custom.h"
#include "usart.h"

#define START_BYTE (0xA5)

// Button's bit position in the byte
#define B_X (7)
#define B_Y (6)
#define B_A (5)
#define B_B (4)
#define B_UP (3)
#define B_DOWN (2)
#define B_LB (1)
#define B_RB (0)

#define B_START (7)
#define B_BACK (6)
#define B_XBOX (5)
#define B_LEFT (4)
#define B_RIGHT (3)

#define _BV(x) (1 << x)

struct JoyStick_Data {
    uint8_t button1;
    uint8_t button2;
    uint8_t lt;
    uint8_t rt;
    uint8_t l_hatx;
    uint8_t l_haty;
    uint8_t r_hatx;
    uint8_t r_haty;
};

struct JoyStick_Handle {
    UART_HandleTypeDef *huart;
    Queue<JoyStick_Data, 2> data;
};

class JoyStick {
  public:
    JoyStick() : hjoy_(0) {}
    JoyStick(JoyStick_Handle *hjoy) { hjoy_ = hjoy; }
    JoyStick(JoyStick &&) = default;
    JoyStick(const JoyStick &) = default;
    JoyStick &operator=(JoyStick &&) = default;
    JoyStick &operator=(const JoyStick &) = default;
    ~JoyStick() {}
    void set_config(JoyStick_Handle *hjoy) { hjoy_ = hjoy; }
    void init();
    void parse_JoyData(RobotState *robot_state);

  private:
    JoyStick_Handle *hjoy_;
    RobotState *robot_state;
    // bool isButtonPressed(uint8_t buttonPressed, uint8_t buttonToCheck);
};
#endif // !_JOYSTICK_H_
