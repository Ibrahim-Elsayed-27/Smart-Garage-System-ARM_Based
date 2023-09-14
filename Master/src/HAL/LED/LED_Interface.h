/*
 * LED_Interface.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Yomna Saleh
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_


#define LED_OFF    0
#define LED_ON     1

void led_init(u8 copy_u8PortID, u8 copy_u8PinNum);
void led_state(u8 copy_u8PortID, u8 copy_u8PinNum, u8 copy_u8OnOff);

#endif /* HAL_LED_LED_INTERFACE_H_ */
