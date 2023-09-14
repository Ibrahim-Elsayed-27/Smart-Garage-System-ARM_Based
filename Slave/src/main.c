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
#include "MCAL/UART/UART_Int.h"



#include "HAL/LED/LED_Interface.h"


// ----- main() ---------------------------------------------------------------

int main()
{
	/* Initialize (Clock , USART) */
	MRCC_voidInitSystemClk();
	/*Enable RCC For Peripherals*/
	MRCC_voidEnablePeripheralClock(AHB1, _PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_USART1);
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_SYSCFG);

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

	u8 irs_state=0;

  // Infinite loop
  while (1)
    {
	  	  irs_state = uart_read_data(UART_NUMBER1);
	  	  led_state(_GPIOA_PORT,_PIN_0,GET_BIT(irs_state,0));
	  	  led_state(_GPIOA_PORT,_PIN_1,GET_BIT(irs_state,1));


    }
}


// ----------------------------------------------------------------------------
