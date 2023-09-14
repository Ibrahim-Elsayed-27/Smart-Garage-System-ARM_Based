/*
 * IR_Prog.c
 *
 *  Created on: Sep 9, 2023
 *      Author: himah
 */


#include "IR_Int.h"
#include "../../MCAL/MGPIO/MGPIO_interface.h"

void ir_init(u8 port, u8 pin){
	MGPIO_voidSetPinMode(port ,pin , _MODE_INPUT);

}

u8 ir_read(u8 port, u8 pin){
	return MGPIO_u8ReadData(port ,pin);
}
