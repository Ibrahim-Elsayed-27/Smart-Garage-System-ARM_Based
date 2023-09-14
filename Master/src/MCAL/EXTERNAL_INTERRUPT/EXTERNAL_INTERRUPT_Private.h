/*
 * EXTERNAL_INTERRUPT_Private.h
 *
 *  Created on: Aug 14, 2023
 *      Author: himah
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_PRIVATE_H_
#define MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_PRIVATE_H_



/*  RCC Base address  */
#define EXTI_BASE_ADRESS 0x40013C00


typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;


}EXTI_MemMap_t;




#define EXTI ((volatile EXTI_MemMap_t*) EXTI_BASE_ADRESS)
#define SYSCFG_EXTICR1 *((volatile u32*) (0x40013800+0x08))
#define SYSCFG_EXTICR2 *((volatile u32*) (0x40013800+0x0C))
#define SYSCFG_EXTICR3 *((volatile u32*) (0x40013800+0x10))
#define SYSCFG_EXTICR4 *((volatile u32*) (0x40013800+0x14))


#endif /* MCAL_EXTERNAL_INTERRUPT_EXTERNAL_INTERRUPT_PRIVATE_H_ */
