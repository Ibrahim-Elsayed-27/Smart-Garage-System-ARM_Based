/*
 * MSYSTICK_Prog.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Mostafa Ashraf
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "MSTK_Int.h"
#include "MSTK_Private.h"
#include "MSTK_Config.h"


static void (*GS_STK_Callback)(void) ;
static u8   G_u8SingleFlag ;



void MSTK_vInit(void)
{
	/* 1- clock source */
#if STK_CLK_SOURCE == STK_AHB
	SET_BIT(STK->CTRL, CLKSOURCE) ;
#endif
	/* 2- Interrupt enable or disable*/
#if STK_INTERRPUT_EN==ENABLE
	SET_BIT(STK->CTRL, TICKINT) ;
#endif
}


void MSTK_vSetBusyWait(u32 A_u32Ticks)
{
	/* 1- reset timer value */
	STK->VAL = 0 ;
	/* 2- Load timer with Value */
	STK->LOAD = A_u32Ticks ;
	/* 3- Start the timer   */
	SET_BIT(STK->CTRL, STK_ENABLE);
	/* 4-  wait for timer flag to be raised  */
	while(GET_BIT(STK->CTRL, COUNTFLAG) != 1  ){}
	/* 5-  Stop the timer   */
	CLR_BIT(STK->CTRL, STK_ENABLE);
}

void MSTK_vSetInterval_single(u32 A_u32Ticks, void (*CallbackFunction)(void))
{
	/* 0- set Callback function */
	GS_STK_Callback = CallbackFunction ;
	G_u8SingleFlag = 1 ;
	/* 1- reset timer value */
	STK->VAL = 0 ;
	/* 2- Load timer with Value */
	STK->LOAD = A_u32Ticks ;
	/* 3- Start the timer   */
	SET_BIT(STK->CTRL, STK_ENABLE);
}

void MSTK_vSetInterval_periodic(u32 A_u32Ticks, void (*CallbackFunction)(void))
{
	/* 0- set Callback function */
	GS_STK_Callback = CallbackFunction ;
	G_u8SingleFlag = 0 ;
	/* 1- reset timer value */
	STK->VAL = 0 ;
	/* 2- Load timer with Value */
	STK->LOAD = A_u32Ticks ;
	/* 3- Start the timer   */
	SET_BIT(STK->CTRL, STK_ENABLE);
}


u32  MSTK_u32GetElapsedTime(void)
{
	return (STK->LOAD-STK->VAL) ;
}

u32  MSTK_u32GetRemainingTime(void)
{
	return STK->VAL ;
}


void Systick_Handler(void)
{
	if(GS_STK_Callback != NULL)
	{
		GS_STK_Callback();
	}
	if(G_u8SingleFlag)
	{
		G_u8SingleFlag = 0 ;
		/* 5-  Stop the timer   */
		CLR_BIT(STK->CTRL, STK_ENABLE);
	}
}

