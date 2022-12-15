/*
 * TIMER_pri.h
 *
 *  Created on: Sep 13, 2022
 *      Author: Dell
 */

#ifndef MCAL_TIMER_TIMER_PRI_H_
#define MCAL_TIMER_TIMER_PRI_H_

/*************** GLOBAL ********************/

/***********************************************************/
/*********************** TIMER0 ****************************/
/***********************************************************/

/* CLOCK SOURCE OPTIONS */
#define TIMER0_CLOCK_SOURCE_NO_CLK 0
#define TIMER0_CLOCK_SOURCE_NO_PRESSCALE 1
#define TIMER0_CLOCK_SOURCE_PRESSCALE_8 2
#define TIMER0_CLOCK_SOURCE_PRESSCALE_64 3
#define TIMER0_CLOCK_SOURCE_PRESSCALE_256 4
#define TIMER0_CLOCK_SOURCE_PRESSCALE_1024 5
#define TIMER0_CLOCK_SOURCE_EXTERNAL_FALL 6
#define TIMER0_CLOCK_SOURCE_EXTERNAL_RISE 7

/***********************************************************/
/*********************** TIMER2 ****************************/
/***********************************************************/
#define TIMER2_CLOCK_SOURCE_NO_CLK 0
#define TIMER2_CLOCK_SOURCE_NO_PRESSCALE 1
#define TIMER2_CLOCK_SOURCE_PRESSCALE_8 2
#define TIMER2_CLOCK_SOURCE_PRESSCALE_32 3
#define TIMER2_CLOCK_SOURCE_PRESSCALE_64 4
#define TIMER2_CLOCK_SOURCE_PRESSCALE_128 5
#define TIMER2_CLOCK_SOURCE_PRESSCALE_256 6
#define TIMER2_CLOCK_SOURCE_PRESSCALE_1024 7

#define CLOCK_SOURCE_MASK 0xF8

/* WAVE GENERATION MODE */
#define WAVE_GENERATION_MODE_NORMAL 0b00000000 /* OVERFLOW MODE */
#define WAVE_GENERATION_MODE_PWM_PC 0b01000000
#define WAVE_GENERATION_MODE_CTC 0b00001000
#define WAVE_GENERATION_MODE_PWM_FAST 0b01001000

#define WAVE_GENERATION_MODE_MASK 0b10110111

/* Compare Match Output Mode */
#define NORMAL_COMPARE_MODE 0 /* OCR DISCONNECTED */
#define TOOGLE_COMPARE_MODE 1
#define CLEAR_COMPARE_MODE_NON_INVERTING 2
#define SET_COMPARE_MODE_INVERTING 3

#define OCR_PIN_MASK_T0_T2 0b11001111
/***********************************************************/
/*********************** TIMER1 ****************************/
/***********************************************************/
/***********************************************************/

/* CLOCK SOURCE OPTIONS */
#define TIMER1_CLOCK_SOURCE_NO_CLK 0
#define TIMER1_CLOCK_SOURCE_NO_PRESSCALE 1
#define TIMER1_CLOCK_SOURCE_PRESSCALE_8 2
#define TIMER1_CLOCK_SOURCE_PRESSCALE_64 3
#define TIMER1_CLOCK_SOURCE_PRESSCALE_256 4
#define TIMER1_CLOCK_SOURCE_PRESSCALE_1024 5
#define TIMER1_CLOCK_SOURCE_EXTERNAL_FALL 6
#define TIMER1_CLOCK_SOURCE_EXTERNAL_RISE 7

/* WAVE GENERATION MODE  */
#define NORMAL_TCCR1A 0b00000000
#define NORMAL_TCCR1B 0b00000000
#define PWM_PC_8BIT_TCCR1A 0b00000001
#define PWM_PC_8BIT_TCCR1B 0b00000000
#define PWM_PC_9BIT_TCCR1A 0b00000010
#define PWM_PC_9BIT_TCCR1B 0b00000000
#define PWM_PC_10BIT_TCCR1A 0b00000011
#define PWM_PC_10BIT_TCCR1B 0b00000000
#define CTC_OCR1A_TCCR1A 0b00000000
#define CTC_OCR1A_TCCR1B 0b00001000
#define FAST_PWM_8BIT_TCCR1A 0b00000001
#define FAST_PWM_8BIT_TCCR1B 0b00001000
#define FAST_PWM_9BIT_TCCR1A 0b00000010
#define FAST_PWM_9BIT_TCCR1B 0b00001000
#define FAST_PWM_10BIT_TCCR1A 0b00000011
#define FAST_PWM_10BIT_TCCR1B 0b00001000
#define PWM_PC_FREQ_ICR1_TCCR1A 0b00000000
#define PWM_PC_FREQ_ICR1_TCCR1B 0b00010000
#define PWM_PC_FREQ_OCR1A_TCCR1A 0b00000001
#define PWM_PC_FREQ_OCR1A_TCCR1B 0b00010000
#define PWM_PC_ICR1_TCCR1A 0b00000010
#define PWM_PC_ICR1_TCCR1B 0b00010000
#define PWM_PC_OCR1A_TCCR1A 0b00000011
#define PWM_PC_OCR1A_TCCR1B 0b00010000
#define CTC_ICR1_TCCR1A 0b00000000
#define CTC_ICR1_TCCR1B 0b00011000
#define FAST_PWM_ICR1_TCCR1A 0b00000010
#define FAST_PWM_ICR1_TCCR1B 0b00011000
#define FAST_PWM_OCR1A_TCCR1A 0b00000010
#define FAST_PWM_OCR1A_TCCR1B 0b00011000

#define TCCR1A_WAVE_MODE_MASK 0b11111100
#define TCCR1B_WAVE_MODE_MASK 0b11100111
/* Compare Match Output Mode */
#define NORMAL_COMPARE_MODE 0 /* OCR DISCONNECTED */
#define TOOGLE_COMPARE_MODE 1
#define CLEAR_COMPARE_MODE_NON_INVERTING 2
#define SET_COMPARE_MODE_INVERTING 3

#define OCR_PIN_MASK_T3_B 0b11001111
#define OCR_PIN_MASK_T3_A 0b00111111

/******************** ISR / TIMER0**************************/
/* TIMER0 COMP */
void __vector_10(void) __attribute__((signal));
/* TIMER0 OVF */
void __vector_11(void) __attribute__((signal));

/******************** ISR / TIMER2**************************/
/* TIMER COMP */
void __vector_4(void) __attribute__((signal));
/* TIMER2 OVF */
void __vector_5(void) __attribute__((signal));

/******************** ISR / TIMER1**************************/
/* TIMER1 CAPT */
void __vector_6(void) __attribute__((signal));
/* TIMER1 COMPA */
void __vector_7(void) __attribute__((signal));
/* TIMER1 COMPB */
void __vector_8(void) __attribute__((signal));
/* TIMER1 OVF */
void __vector_9(void) __attribute__((signal));

#endif /* MCAL_TIMER_TIMER_PRI_H_ */
