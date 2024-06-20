/*
 * steering_pid.c
 *
 *  Created on: Mar 21, 2024
 *      Author: wegz
 */

#include"stm32f1xx_hal.h"
#include"steering_pid.h"


extern int lane_dist;
double error, proportional, derivative, controlSignal, integral, previousError;
int angle;
float kp=1.5,ki,kd=0.2;


void steering()
{
	error = TARGET_DISTANCE + lane_dist;
	proportional = kp * error;
	integral += ki * error;
	derivative = kd * (error - previousError);
	controlSignal = proportional + integral + derivative;
	previousError = error;
//	angle = map(controlSignal, -100, 100, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
	angle = (controlSignal - (-40)) * (180 - 20) / (40 - (-40)) + 20;
	HServo_writePosition(angle);
}


