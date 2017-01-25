#include "wheel.h"

#include <math.h>

// TODO No rotation
#define RADIUS 0

// Calculate speed for that motor base on velocity command
float wheel_setCommand(Wheel_t* wheel, const float vx, const float vy, const float vt) {

	const float magnitude = sqrtf(vx*vx + vy*vy);
	const float angle = atan2f(vy, vx);
	// The wheel's angle is the position of the wheel axe
	// The force angle is the angle of the force vector create by the rotation of the wheel
	const float forceAngle = wheel->angle + (float)M_PI_2;
	const float result = magnitude * cosf(forceAngle - angle) + vt;
	return result;
}

void wheel_break(const Wheel_t *wheel) {
	wheel_setPWM(wheel, MOTOR_BREAK);
}

void wheel_setPWM(const Wheel_t *wheel, float speed) {
	// Range is 20000 to 28000, the output is in the range -1.0 to 1.0
	// TODO put in own function

#if defined (BETA)
	int command = ((int) fabs(speed * 24000.0)) + 18000;
#elif defined (GAMMA)
	int command = (int) fabs(speed * 30000) + 6000;
#elif defined (GAMMA2)
	float _speed = 1.0f - (float)fabs(speed);
	int command = ((int) ((float)fabs(_speed) * 65535.0f));
#endif
	// Less then 4% of power we break
	if((float)fabs(speed) < 0.09){
		command = 0;
#if defined (GAMMA2)
		command = 65535;
#endif
	}

	uint32_t timerValue = (uint32_t)command;
  	__HAL_TIM_SetCompare(wheel->pTimer, wheel->timerChannel, timerValue);

  	//static char buffer[128];
	//snprintf(buffer, 128, "fbk: %d err: %d out: %d ", (int)wheel->pid.fbk, (int)wheel->pid.e, (int)(wheel->pid.output *100.0));
	//Debug_Print(buffer);

	// A clockwise/anticlockwise refer to rotation of the wheel when looking from the front.
	// A clockwise turn clockwise when the direction pin is set to high
	// Please note this is the WHEEL rotation not the MOTOR rotation
	GPIO_PinState dirPinState = GPIO_PIN_RESET;
	switch (wheel->direction) {
		case ClockWise:
			dirPinState = speed >= 0.0 ? GPIO_PIN_SET : GPIO_PIN_RESET; // use wheel->pid->r ?
			break;
		case AntiClockWise:
		default:
			dirPinState = speed < 0.0 ? GPIO_PIN_SET : GPIO_PIN_RESET;
	}

	// Change the GPIO state
	HAL_GPIO_WritePin(wheel->dirGpioPort, wheel->dirGpioPin, dirPinState);
}


