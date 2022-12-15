/*
 * EXTI_pri.h
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */

#ifndef MCAL_EXTI_EXTI_PRI_H_
#define MCAL_EXTI_EXTI_PRI_H_

/*Available sense control in ATmega32 for INT1 & INT0*/
#define LOW_LEVEL			0
#define ANY_LOGICAL_CHANGE  1
#define FALLING_EDGE 		2
#define RISING_EDGE 		3


/*Available sense control for INT2*/
#define INT2_FALLING_EDGE 0
#define INT2_RISING_EDGE  1

/**/
#define ISR(N) __vector_N(void)

#define INT0_vect 0

/*ISR for INT0. the vector number is 2*/
/*signal attribute means nesting is enabled. */
void __vector_1 (void) __attribute__((signal));

/*ISR for INT1. the vector number is 3*/
void __vector_2 (void) __attribute__((signal));

/*ISR for INT2. the vector number is 4*/
void __vector_3 (void) __attribute__((signal));

/*global variable to be used in the ISR*/
/*
static void (* G_ISR_INT0_ptr) (void);
static void (* G_ISR_INT1_ptr) (void);
static void (* G_ISR_INT2_ptr) (void);*/

ptr_func_t G_ISR_INT0_ptr;
ptr_func_t G_ISR_INT1_ptr;
ptr_func_t G_ISR_INT2_ptr;

#endif /* MCAL_EXTI_EXTI_PRI_H_ */
