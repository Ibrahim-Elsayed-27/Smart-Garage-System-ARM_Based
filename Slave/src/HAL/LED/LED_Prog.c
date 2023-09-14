/*
 * LED_Prog.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Yomna Saleh
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/MGPIO/MGPIO_Interface.h"

void led_init(u8 copy_u8PortID, u8 copy_u8PinNum){

	MGPIO_voidSetPinMode(copy_u8PortID, copy_u8PinNum, _MODE_OUTPUT);
}


void led_state(u8 copy_u8PortID, u8 copy_u8PinNum, u8 copy_u8OnOff){

	MGPIO_voidWriteData(copy_u8PortID, copy_u8PinNum, copy_u8OnOff);
}


