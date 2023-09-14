/*
 * NVIC_Prog.c
 *
 *  Created on: Aug 13, 2023
 *      Author: himah
 */

#include "NVIC_Config.h"
#include "NVIC_Int.h"
#include "NVIC_Private.h"

NVIC_GROUP_t global_grouping;


void nvic_v_interrupt_enable(u8 interrupt_number){
	SET_BIT(NVIC -> ISER[interrupt_number/ reg_div] , interrupt_number % reg_div);
}
void nvic_v_interrupt_disable(u8 interrupt_number){
	SET_BIT(NVIC -> ICER[interrupt_number/ reg_div] , interrupt_number % reg_div);
}

void nvic_v_interrupt_enable_pending(u8 interrupt_number){
	SET_BIT(NVIC -> ISPR[interrupt_number/ reg_div] , interrupt_number % reg_div);
}
void nvic_v_interrupt_disable_pending(u8 interrupt_number){
	SET_BIT(NVIC -> ICPR[interrupt_number/ reg_div] , interrupt_number % reg_div);
}
u8 nvic_u8_get_interrupt_status(u8 interrupt_number){
	u8 status = GET_BIT(NVIC -> IABR[interrupt_number/ reg_div] , interrupt_number % reg_div);
	return status;
}

void nvic_v_interrupt_group_mode(NVIC_GROUP_t nvic_group){
	global_grouping = nvic_group;
	SCB_AIRCR = NVIC_VECTKEY;
	u32 copy= NVIC_VECTKEY | (nvic_group<<8);
	SCB_AIRCR = copy;
}

void nvic_v_interuupt_priority(u8 interrupt_number, u8 interrupt_group, u8 interrupt_sub_group){
	switch(global_grouping){
	case(Group16Sub0):
			NVIC -> IPR[interrupt_number] = interrupt_group<<4;
			break;
	case(Group8Sub2):
			NVIC -> IPR[interrupt_number] = interrupt_group<<5 | interrupt_sub_group<<4 ;
			break;
	case(Group4Sub4):
		NVIC -> IPR[interrupt_number] = interrupt_group<<6 | interrupt_sub_group<<4 ;
		break;
	case(Group2Sub8):
		NVIC -> IPR[interrupt_number] = interrupt_group<<7 | interrupt_sub_group<<4 ;
		break;
	case(Group0Sub16):
		NVIC -> IPR[interrupt_number] = interrupt_group<<8 | interrupt_sub_group<<4 ;
		break;
	default:
		break;

	}
}
