
#include "wheels_config.h"


/**
 * Table of wheel configuration.
 * If the motor to encoder assignation is wrong, the problem is probably here.
 * Every tim need to be initialized in the main().
 */
Wheel_t g_wheels[] =
{
#ifdef BETA
/* wheel == sticker -> pin == cubeMX name + soudure*/
{"wheel 1", {0}, QuadEncoderB1, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, M_PI_4,          3.0},     /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, QuadEncoderA2, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, M_PI_2 + M_PI_4, 1.0},     /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, QuadEncoderA1, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, -M_PI_2 -M_PI_4, 1.0},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, QuadEncoderB2, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, -M_PI_4,         1.0}      /*wheel 4 -> pin_motor3*/
#elif defined (GAMMA)
{"wheel 1", {0}, EncoderTim3, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, AntiClockWise, M_PI_4,          1.0},     /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, EncoderTim1, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, AntiClockWise, M_PI_2 + M_PI_4, 1.0},     /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, EncoderTim2, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, AntiClockWise, -M_PI_2 -M_PI_4, 1.0},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, EncoderTim4, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, AntiClockWise, -M_PI_4,         1.0}      /*wheel 4 -> pin_motor3*/
#endif
};

const size_t wheelsLen = sizeof(g_wheels) / sizeof(Wheel_t);