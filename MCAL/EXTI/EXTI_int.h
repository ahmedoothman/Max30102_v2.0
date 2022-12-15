/*
 * EXTI_int.h
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define INT0_ID 0
#define INT1_ID 1
#define INT2_ID 2

void EXTI_vInitINT0(void);
void EXTI_vInitINT1(void);
void EXTI_vInitINT2(void);

void EXTI_vReg_Func( ptr_func_t ptr, u8 A_u8IntId);

#endif /* MCAL_EXTI_EXTI_INT_H_ */
