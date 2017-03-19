#include "ctrl_task.h"

#include "wheels_UT.h"
#include "wheels_config.h"


#ifdef USE_QUAD
static quad_Handle quadA;
static quad_Handle quadB;
#else
typedef struct EncoderTimerAssociation_t{
	QuadEncoder_t identifier;
	TIM_HandleTypeDef* timer;
	EncoderHandle_t encoder;
} EncoderTimerAssociation_t;

static EncoderTimerAssociation_t s_encoders[] = {
	{EncoderTim1, &htim1, {0}},
	{EncoderTim2, &htim2, {0}},
	{EncoderTim3, &htim3, {0}},
	{EncoderTim4, &htim4, {0}}
};
const size_t encodersLen = sizeof(s_encoders) / sizeof(EncoderTimerAssociation_t);
#endif

volatile CtrlLoop_t g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
volatile SpeedCommand_t g_speedCommand = {
		.vx = 0.0,
		.vy = 0.0,
		.vtheta = 0,
		.tickSinceLastUpdate = 0
};
volatile SpeedCommandOpen_t g_speedCommandOpen = {
		.w1 = 0.0,
		.w2 = 0.0,
		.w3 = 0.0,
		.w4 = 0.0,
		.tickSinceLastUpdate = 0
};




// This tasks deals with the movements of the robot
void ctrl_taskEntryPoint(void) {
	//test_startUp();
	if (robot_isDebug()) {
		while(!test_startUp());
	}
  	LOG_INFO("Starting!!!\r\n");
	initPwmAndQuad();

	int32_t wheelSpeed[4];
  	TickType_t lastWakeTime = xTaskGetTickCount();
  	bool speedCommandTimeout = true;
  	bool speedCommandOpenTimeout = true;
	for(;;) {
		// Delay the loop to a fix frequency
		vTaskDelayUntil(&lastWakeTime, CONTROL_LOOP_PERIOD_MS / portTICK_PERIOD_MS);

		static int c = 0;
		if(++c >= 100){
			c = 0;
			//if(g_ctrlLoopState == CLOSE_LOOP_WITHOUT_LOGGING)
				//LOG_INFO("ctrl\r\n");
		}

		readQuadsSpeed(&wheelSpeed);

		float vx, vy, vt;
		float output[4];

		switch(g_ctrlLoopState) {
			case OPEN_LOOP:
				output[0] = g_speedCommandOpen.w1;
				output[1] = g_speedCommandOpen.w2;
				output[2] = g_speedCommandOpen.w3;
				output[3] = g_speedCommandOpen.w4;

				const bool lastSpeedCommandOpenTimeout = speedCommandOpenTimeout;
				speedCommandOpenTimeout = hasSpeedCommandOpenTimeout();
				if (speedCommandOpenTimeout) {
					if (c == 0 || speedCommandOpenTimeout != lastSpeedCommandOpenTimeout)
						LOG_ERROR("Timeout on open loop command\r\n");
					ctrl_emergencyBreak();
					continue;
				}

				for (int i = 0; i < wheelsLen; ++i) {
					Wheel_t* pWheel = &g_wheels[i];
					float feedback = (float)wheelSpeed[pWheel->quad];
					motorDataLog_addWheelData(output[i], feedback);
					wheel_setPWM(pWheel, output[i]);
				}
				break;
			case CLOSE_LOOP_WITHOUT_LOGGING:
			case CLOSE_LOOP_WITH_LOGGING:
				vx = g_speedCommand.vx;
				vy = g_speedCommand.vy;
				vt = g_speedCommand.vtheta;

				const bool lastSpeedCommandTimeout = speedCommandTimeout;
				speedCommandTimeout = hasSpeedCommandTimeout();
				if (speedCommandTimeout) {
					if (c == 0 || speedCommandTimeout != lastSpeedCommandTimeout)
						LOG_ERROR("Timeout on command\r\n");
					ctrl_emergencyBreak();
					continue;
				}

				if(g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
					motorDataLog_addReceivedSpeed(vx, vy, vt);
				}

				for (int i = 0; i < wheelsLen; ++i) {
					Wheel_t* pWheel = &g_wheels[i];
					float output = 0.0;
					float reference = wheel_setCommand(pWheel, vx, vy, vt);
					float feedback = (float)wheelSpeed[pWheel->quad];

					// The speed reference and feedback must be absolute, since the pid ignore the wheel direction.
					// This is done since the passage from one direction to another one cause an instability
					pWheel->pid.r = (float)fabs(reference);
					pWheel->pid.fbk = (float)fabs(feedback);
					pid_update(&pWheel->pid);

					output = pWheel->pid.output;

					// Pid uses absolute speed and does not know about wheel direction
					// If the speed command is negative we change the pid output to be negative
					// and thus the motor will spin in the correct direction
					output *= (reference >= 0.0 ? 1.0f : -1.0f);

					wheel_setPWM(pWheel, output);
				}
				break;
			default:
				LOG_ERROR("Unimplemented control loop state.\r\n");
		}
		// Handle logging output for close/open loop test
		if (g_ctrlLoopState == OPEN_LOOP || g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
			for (int i = 0; i < wheelsLen; ++i) {
				if (g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
					motorDataLog_addCloseLoopData(&g_wheels[i].pid);
				}
			}
			motorDataLog_flushDataLine();
		}

	  }
}

void ctrl_emergencyBreak(void) {
	for(size_t i = 0; i < wheelsLen; ++i) {
		wheel_break(&g_wheels[i]);
	}
}

void initPwmAndQuad(void) {
	static bool executeOnce = true;
	if(executeOnce) {
		executeOnce = false;

		for(size_t i = 0; i < wheelsLen; ++i) {
		  	HAL_TIM_PWM_Start(g_wheels[i].pTimer, g_wheels[i].timerChannel);
			g_wheels[i].pid = pid_init(PID_P, PID_I, PID_D, 1.0, 0.0);
		}

#ifdef USE_QUAD
	  	quadA = quad_Init(CS_1);
	  	quadB = quad_Init(CS_2);
#else
		for(int i = 0; i < encodersLen; ++i) {
			s_encoders[i].encoder = encoder_init(s_encoders[i].timer);
		}
#endif
	}
}

void readQuadsSpeed(int32_t *wheelSpeed) {

#ifdef USE_QUAD
	quad_ReadCounters(&quadA);
	quad_ReadCounters(&quadB);
	wheelSpeed[QuadEncoderA1] = quadA.delta_count0;
	wheelSpeed[QuadEncoderA2] = quadA.delta_count1;
	wheelSpeed[QuadEncoderB1] = quadB.delta_count0;
	wheelSpeed[QuadEncoderB2] = quadB.delta_count1;
#else
	for(int i = 0; i < encodersLen; ++i) {
		EncoderTimerAssociation_t* encoderTimerAsso = &s_encoders[i];
		encoder_readCounters(&(encoderTimerAsso->encoder));
		wheelSpeed[encoderTimerAsso->identifier] = encoderTimerAsso->encoder.deltaCount;
	}
#endif
}


bool hasSpeedCommandTimeout(void) {
	const TickType_t SPEED_COMMAND_TIMEOUT_TICK = 500;
	return xTaskGetTickCount() - g_speedCommand.tickSinceLastUpdate > SPEED_COMMAND_TIMEOUT_TICK / portTICK_PERIOD_MS;
}

bool hasSpeedCommandOpenTimeout(void) {
	const TickType_t SPEED_COMMAND_TIMEOUT_TICK = 500;
	return xTaskGetTickCount() - g_speedCommandOpen.tickSinceLastUpdate > SPEED_COMMAND_TIMEOUT_TICK / portTICK_PERIOD_MS;
}
