/*
 * IR_Int.h
 *
 *  Created on: Sep 9, 2023
 *      Author: himah
 */

#ifndef HAL_IR_IR_INT_H_
#define HAL_IR_IR_INT_H_


#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"

void ir_init(u8 port, u8 pin);
u8 ir_read(u8 port, u8 pin);


#endif /* HAL_IR_IR_INT_H_ */
