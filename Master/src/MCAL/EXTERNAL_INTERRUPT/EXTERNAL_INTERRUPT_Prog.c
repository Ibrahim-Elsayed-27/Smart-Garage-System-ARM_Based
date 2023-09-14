/*
 * EXTERNAL_INTERRUPT_Prog.c
 *
 *  Created on: Aug 14, 2023
 *      Author: himah
 */


#include "EXTERNAL_INTERRUPT_Config.h"
#include "EXTERNAL_INTERRUPT_Int.h"
#include "EXTERNAL_INTERRUPT_Private.h"


/*initialize the isr functions for each interrupt to null */
static void (*external_interrupt_0_callback) (void) = 0;
static void (*external_interrupt_1_callback) (void) = 0;
static void (*external_interrupt_2_callback) (void) = 0;


void external_v_interrupt_enable(external_interrupt_number external_number){
	SET_BIT(EXTI -> IMR, external_number);
}
void external_v_interrupt_disable(external_interrupt_number external_number){
	CLR_BIT(EXTI -> IMR, external_number);
}
void external_v_interrupt_software_enable(external_interrupt_number external_number){
	SET_BIT(EXTI -> SWIER, external_number);
}


void external_v_interrupt_set_type(external_interrupt_number external_number,external_interrupt_type external_type){
	switch(external_type){
	case rising_edge:
		CLR_BIT(EXTI -> FTSR,external_number);
		SET_BIT(EXTI -> RTSR,external_number);
		break;
	case falling_edge:
		SET_BIT(EXTI -> FTSR,external_number);
		CLR_BIT(EXTI -> RTSR,external_number);
		break;
	case any_change:
		SET_BIT(EXTI -> FTSR,external_number);
		SET_BIT(EXTI -> RTSR,external_number);
		break;
	}

}


void external_v_interrupt_callback(external_interrupt_number external_number, void (*callback) (void) ){
	switch(external_number){
		case external_interrupt_0:
			external_interrupt_0_callback=callback;
			break;
		case external_interrupt_1:
			external_interrupt_1_callback=callback;
			break;
		case external_interrupt_2:
			external_interrupt_2_callback=callback;
			break;
	}

}


void external_v_interrupt_set_port(external_interrupt_number external_number,u8 port){
	if (external_number<4){
		switch(port){
		case GPIO_PORTA:
			SYSCFG_EXTICR1 &= ~(0b11 << (external_number*4));
			SYSCFG_EXTICR1 |= (0b0000 <<(external_number*4));
			break;
		case GPIO_PORTB:
			SYSCFG_EXTICR1 &= ~(0b11 << (external_number*4));
			SYSCFG_EXTICR1 |= (0b0001 <<(external_number*4));
			break;
		}
	}else if(external_number<8){
		;
	}
	else if(external_number<12){
			;
		}
	else if(external_number<16){
			;
		}
}


void EXTI0_IRQHandler(void){
	external_interrupt_0_callback();
	SET_BIT(EXTI -> PR,0);
}

void EXTI1_IRQHandler(void){
	external_interrupt_1_callback();
	SET_BIT(EXTI -> PR,0);
}

void EXTI2_IRQHandler(void){
	external_interrupt_2_callback();
	SET_BIT(EXTI -> PR,0);
}
