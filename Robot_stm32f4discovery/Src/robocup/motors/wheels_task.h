#ifndef WHEEL_TASK_H_
#define WHEEL_TASK_H_

#include <stdio.h>
#include <math.h>

#include "../util.h"
#include "wheels.h"

typedef enum {
	OPEN_LOOP,
	CLOSE_LOOP
} CtrlLoop_t;

typedef struct {
	float vx, vy, vtheta;
} SpeedCommand_t;


extern volatile CtrlLoop_t g_ctrlLoopState;
extern volatile SpeedCommand_t g_speedCommand;

// These variables are public for the unit test
extern Wheel_t wheels[];
extern const size_t wheelsLen;

void wheelTask(void);
void initPwmAndQuad(void);
void readQuadsSpeed(int16_t *wheelSpeed);

#endif /* WHEEL_TASK_H_ */
