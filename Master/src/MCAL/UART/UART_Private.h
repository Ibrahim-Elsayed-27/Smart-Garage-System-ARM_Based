/*
 * UART_Private.h
 *
 *  Created on: Aug 23, 2023
 *      Author: himah
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#include "../../LIB/STD_Types.h"

#define UART1_BASE_ADDR   0x40011000




typedef struct{

	u32 SBK :1;
	u32 RWU :1;
	u32 RE :1;
	u32 TE :1;
	u32 IDLEIE :1;
	u32 RXNEIE :1;
	u32 TCIE :1;
	u32 TXEIE :1;
	u32 PEIE :1;
	u32 PS :1;
	u32 PCE :1;
	u32 WAKE :1;
	u32 M :1;
	u32 UE :1;
	u32 Reserved1 :1;
	u32 OVER8 :1;
	u32 Reserved2 :16;

}UART_CR1;


typedef struct{

	u32 SR;
	u32 DR;
	u32 BRR;
	UART_CR1 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;

}UART_MemMap_t;


#define UART1 ((volatile UART_MemMap_t*)(UART1_BASE_ADDR))
#endif /* MCAL_UART_UART_PRIVATE_H_ */
