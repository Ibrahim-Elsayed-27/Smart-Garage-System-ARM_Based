/*
 * MSYSTICK_Private.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Mostafa Ashraf
 */

#ifndef MCAL_MSYSTICK_MSTK_PRIVATE_H_
#define MCAL_MSYSTICK_MSTK_PRIVATE_H_


#define STK_BASE_ADDR			0xE000E010

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}MSTK_MemMap_t;

#define STK			((volatile MSTK_MemMap_t*)(STK_BASE_ADDR))


#endif /* MCAL_MSYSTICK_MSTK_PRIVATE_H_ */
