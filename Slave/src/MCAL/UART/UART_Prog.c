/*
 * UART_Prog.c
 *
 *  Created on: Aug 23, 2023
 *      Author: himah
 */


#include "UART_Int.h"
#include "UART_Private.h"
#include "UART_config.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"


static void (*uart1_callback) (void) = 0;


void uart_init(u8 uart_number){


	switch(uart_number){
	case UART_NUMBER1:

		/*SET BAUD RATE (115200 for 25 MHZ)*/
		UART1 -> BRR = 0x000000D9;

		/*SET  Oversampling mode to oversampling by 16*/
		UART1 -> CR1.OVER8 = 0;

		/*SET WORD LENGTH TO 8 DATA BITs*/
		UART1 -> CR1.M = 0;

		/*DISABLE PARITY CONTROL*/
		UART1 -> CR1.PCE = 0;

		/*SET STOP BITS TO TWO*/
		CLR_BIT(UART1 -> CR2, 12);
		CLR_BIT(UART1 -> CR2, 13);

		/*ENABLE TRANSMITTER*/
		UART1 -> CR1.TE = 1;

		/*ENABLE RECIEVER*/
		UART1 -> CR1.RE = 1;

		/*ENABLE DATA FRAME (TRANSMITTED OR RECIEVED) INTERRUPT*/
		UART1 -> CR1.RXNEIE = 0;
		break;
	}



}


void uart_enable(u8 uart_number){
	switch(uart_number){
	case UART_NUMBER1:
		UART1 -> CR1.UE = 1;
		break;
	}
}
void uart_disable(u8 uart_number){
	switch(uart_number){
	case UART_NUMBER1:
		UART1 -> CR1.UE = 0;
		break;
	}
}


void uart_send_data(u8 uart_number,u8* data,u8 len){
	switch(uart_number){
	case UART_NUMBER1:
		for (int i=0;i<len;i++){
			UART1 ->DR = *(data+i);
			while(! GET_BIT(UART1 -> SR,6));
		}
	}
}

void uart_send_string(u8 uart_number,u8* string){
	switch(uart_number){
	case UART_NUMBER1:
		while(* string !='\0'){
		UART1 ->DR = * string;
		while(! GET_BIT(UART1 -> SR,6));
		string++;
		}
		UART1 ->DR = '\0';
		while(! GET_BIT(UART1 -> SR,6));
	}
}


u8 uart_read_data(u8 uart_number){
	u8 data=0;
	u16 timeout=0;
	switch(uart_number){
		case UART_NUMBER1:
			while(! GET_BIT(UART1 ->SR, 5 )){
				timeout++;
				if(timeout > 10000){
					data=255;
					break;
				}
			}
			data= (u8) UART1 ->DR;
			break;

	}

	return data;
}


void uart_callback(u8 uart_number,void (*callback)( void)){
	switch(uart_number){
		case UART_NUMBER1:
			uart1_callback=callback;
			break;
	}
}

/*
void USART1_IRQHandler(void)
{
	uart1_callback() ;

	UART1 -> SR = 0;

}
*/
