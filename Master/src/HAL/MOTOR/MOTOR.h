/*
 * MOTOR.h
 *
 *  Created on: Sep 9, 2023
 *      Author: himah
 */

#ifndef HAL_MOTOR_MOTOR_H_
#define HAL_MOTOR_MOTOR_H_


#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"

#define MOTOR_OFF    0
#define MOTOR_ON     1

void motor_int(u8 port, u8 pin);
void motor_state(u8 port, u8 pin, u8 state);


#endif /* HAL_MOTOR_MOTOR_H_ */
