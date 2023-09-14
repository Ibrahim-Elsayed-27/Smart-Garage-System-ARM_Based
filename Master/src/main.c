/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"



#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/EXTERNAL_INTERRUPT/EXTERNAL_INTERRUPT_Int.h"
#include "MCAL/NVIC/NVIC_Int.h"
#include "MCAL/UART/UART_Int.h"


#include "HAL/IR/IR_Int.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/MOTOR/MOTOR.h"


void ir1_interrupt();
void ir2_interrupt();
void ir3_interrupt();
void available_slots();
void unavailable_slots();
volatile u8 ir1_state;
volatile u8 ir2_state;
volatile u8 ir3_state;
int main()
{

    /* Initialize (Clock , USART) */
	MRCC_voidInitSystemClk();


	/*Enable RCC For Peripherals*/
	MRCC_voidEnablePeripheralClock(AHB1, _PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(AHB1, _PERIPHERAL_EN_GPIOB);
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_SYSCFG);
	MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_USART1);

	/* Configure USART pin */
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_9, _MODE_ALTF);     //TX-->UART1
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_10, _MODE_ALTF);     //RX-->UART1
	MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_9, _ALTFN_7);      //TX-->UART1
	MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_10, _ALTFN_7);      //RX-->UART1
	uart_init(UART_NUMBER1);
	uart_enable(UART_NUMBER1);

	/*devices initialization*/
	led_init(_GPIOA_PORT,_PIN_0);
	led_init(_GPIOA_PORT,_PIN_1);
	//ESP8266_voidInit();
	ir_init(_GPIOB_PORT,_PIN_0);
	ir_init(_GPIOB_PORT,_PIN_1);
	ir_init(_GPIOB_PORT,_PIN_2);

	motor_int(_GPIOA_PORT,_PIN_2);
	motor_int(_GPIOA_PORT,_PIN_3);

	/*Set ir1 & ir2  Interrupt Properties*/
	nvic_v_interrupt_group_mode(Group16Sub0);
	nvic_v_interuupt_priority(6,0,0);
	nvic_v_interrupt_enable(6);

	external_v_interrupt_set_port(0,GPIO_PORTB);
	external_v_interrupt_set_type(0,any_change);
	external_v_interrupt_callback(0,ir1_interrupt);
	external_v_interrupt_enable(0);
	/*ir2*/
	nvic_v_interuupt_priority(7,0,0);
	nvic_v_interrupt_enable(7);


	external_v_interrupt_set_port(1,GPIO_PORTB);
	external_v_interrupt_set_type(1,any_change);
	external_v_interrupt_callback(1,ir2_interrupt);
	external_v_interrupt_enable(1);

	/*ir3*/
	nvic_v_interuupt_priority(8,0,0);
	nvic_v_interrupt_enable(8);


	external_v_interrupt_set_port(2,GPIO_PORTB);
	external_v_interrupt_set_type(2,any_change);
	external_v_interrupt_callback(2,ir3_interrupt);
	external_v_interrupt_enable(2);


	ir1_state = ir_read(_GPIOB_PORT,_PIN_0);
	ir2_state = ir_read(_GPIOB_PORT,_PIN_1);
	u8 irs_state=0;
  while (1)
    {
	  if(ir1_state == 1 && ir2_state == 1){
			unavailable_slots();
	  		}
	  else{
		  		available_slots();
	  		}


	irs_state = ir1_state | (ir2_state<<1);
	uart_send_data(UART_NUMBER1,&irs_state,1);
}
}

void ir1_interrupt(){

	ir1_state = ir_read(_GPIOB_PORT,_PIN_0);
	//esp send state
}


void ir2_interrupt(){

	ir2_state = ir_read(_GPIOB_PORT,_PIN_1);
}


void ir3_interrupt(){
	ir3_state = ir_read(_GPIOB_PORT,_PIN_2);
	if(ir1_state == 1 && ir2_state == 1){
		return ;
	}
	if (ir3_state == 0){
		motor_state(_GPIOA_PORT,_PIN_2,MOTOR_ON);
		motor_state(_GPIOA_PORT,_PIN_3,MOTOR_OFF);
		for(u32 i=0;i<1000000;i++);
		motor_state(_GPIOA_PORT,_PIN_2,MOTOR_OFF);
	}else{
		motor_state(_GPIOA_PORT,_PIN_2,MOTOR_OFF);
		motor_state(_GPIOA_PORT,_PIN_3,MOTOR_ON);
		for(u32 i=0;i<1000000;i++);
		motor_state(_GPIOA_PORT,_PIN_3,MOTOR_OFF);
	}

	//esp send state
}
void available_slots(){
	led_state(_GPIOA_PORT,_PIN_1,LED_OFF);
	led_state(_GPIOA_PORT,_PIN_0,LED_ON);
}
void unavailable_slots(){
	led_state(_GPIOA_PORT,_PIN_0,LED_OFF);
	led_state(_GPIOA_PORT,_PIN_1,LED_ON);
}

// ----------------------------------------------------------------------------
