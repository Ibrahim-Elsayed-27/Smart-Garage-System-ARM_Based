/*
 * EXTERNAL_INTERRUPT_Int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: himah
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_INT_H_
#define MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_INT_H_

#include "../..//LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"


typedef enum {
	external_interrupt_0,
	external_interrupt_1,
	external_interrupt_2,

}external_interrupt_number;


typedef enum{
	rising_edge,
	falling_edge,
	any_change
}external_interrupt_type;

#define GPIO_PORTA 0
#define GPIO_PORTB 1


void external_v_interrupt_enable(external_interrupt_number external_number);
void external_v_interrupt_disable(external_interrupt_number external_number);
void external_v_interrupt_software_enable(external_interrupt_number external_number);
void external_v_interrupt_set_type(external_interrupt_number external_number,external_interrupt_type external_type);
void external_v_interrupt_callback(external_interrupt_number external_number, void (*callback) (void) );
void external_v_interrupt_set_port(external_interrupt_number external_number,u8 port);


#endif /* MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_INT_H_ */
