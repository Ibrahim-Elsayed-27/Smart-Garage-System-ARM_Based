/*
 * MSYSTICK_Init.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Mostafa Ashraf
 */

#ifndef MCAL_MSYSTICK_MSTK_INT_H_
#define MCAL_MSYSTICK_MSTK_INT_H_

#define NULL 0

#define STK_AHB				1
#define STK_AHB_DIV_8		2

#define STK_ENABLE  0
#define CLKSOURCE	2
#define TICKINT		1
#define COUNTFLAG	16

#define ENABLE		1
#define DISABLE		0

void MSTK_vInit(void);

void MSTK_vSetBusyWait(u32 A_u32Ticks);

void MSTK_vSetInterval_single(u32 A_u32Ticks, void (*CallbackFunction)(void));
void MSTK_vSetInterval_periodic(u32 A_u32Ticks, void (*CallbackFunction)(void));

u32  MSTK_u32GetElapsedTime(void);
u32  MSTK_u32GetRemainingTime(void);

#endif /* MCAL_MSYSTICK_MSTK_INT_H_ */
