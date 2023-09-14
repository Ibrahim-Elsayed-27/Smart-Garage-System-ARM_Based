/*
 * MOTOR.c
 *
 *  Created on: Sep 9, 2023
 *      Author: himah
 */


#include "MOTOR.h"
#include "../../MCAL/MGPIO/MGPIO_interface.h"


void motor_int(u8 port, u8 pin){
	MGPIO_voidSetPinMode(port, pin, _MODE_OUTPUT);
}
void motor_state(u8 port, u8 pin, u8 state){
	MGPIO_voidWriteData(port, pin, state);
}
