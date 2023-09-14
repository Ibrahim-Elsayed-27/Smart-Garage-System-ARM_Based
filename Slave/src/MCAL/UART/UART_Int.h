/*
 * UART_Int.h
 *
 *  Created on: Aug 23, 2023
 *      Author: himah
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_
#include "../../LIB/STD_Types.h"

#define UART_NUMBER1 1
#define UART_NUMBER2 2
#define UART_NUMBER3 3
#define UART_NUMBER4 4
#define UART_NUMBER5 5
#define UART_NUMBER6 6

void uart_init(u8 uart_number);

void uart_enable(u8 uart_number);
void uart_disable(u8 uart_number);
void uart_send_data(u8 uart_number,u8* data,u8 len);
void uart_send_string(u8 uart_number,u8* string);
u8 uart_read_data(u8 uart_number);

#endif /* MCAL_UART_UART_INT_H_ */
