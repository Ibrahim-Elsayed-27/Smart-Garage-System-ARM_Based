/*
 * NVIC_Private.h
 *
 *  Created on: Aug 13, 2023
 *      Author: himah
 */

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_


#define NVIC_BASE_ADDR  0xE000E100

typedef struct{

	u32 ISER[8];
	u32 Reserved1[24];
	u32 ICER[8];
	u32 Reserved2[24];
	u32 ISPR[8];
	u32 Reserved3[24];
	u32 ICPR[8];
	u32 Reserved4[24];
	u32 IABR[8];
	u32 Reserved5[56];
	u8  IPR[240];
	u32 Reserved6[580];
	u32 STIR;

}NVIC_MemMap_t;

#define NVIC ((volatile NVIC_MemMap_t*)(NVIC_BASE_ADDR))
#define SCB_AIRCR *((volatile u32*)(0xE000ED0C))
#define NVIC_VECTKEY   0x05FA0000



#endif /* MCAL_NVIC_NVIC_PRIVATE_H_ */
