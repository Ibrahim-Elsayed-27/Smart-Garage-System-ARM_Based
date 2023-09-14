/*
 * NVIC_Int.h
 *
 *  Created on: Aug 13, 2023
 *      Author: himah
 */

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"

#define reg_div 32


typedef enum{
	Group16Sub0=3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}NVIC_GROUP_t;

void nvic_v_interrupt_enable(u8 interrupt_number);
void nvic_v_interrupt_disable(u8 interrupt_number);
void nvic_v_interrupt_enable_pending(u8 interrupt_number);
void nvic_v_interrupt_disable_pending(u8 interrupt_number);
u8 nvic_u8_get_interrupt_status(u8 interrupt_number);
void nvic_v_interrupt_group_mode(NVIC_GROUP_t nvic_group);
void nvic_v_interuupt_priority(u8 interrupt_number, u8 interrupt_group, u8 interrupt_sub_group);
#endif /* MCAL_NVIC_NVIC_INT_H_ */
