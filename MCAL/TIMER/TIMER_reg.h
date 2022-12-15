/*
 * TIMER_reg.h
 *
 *  Created on: Sep 13, 2022
 *      Author: Dell
 */
#define MCUCSR *((volatile u8 *)0x54)

#ifndef MCAL_TIMER_TIMER_REG_H_
#define MCAL_TIMER_TIMER_REG_H_
/************************************************************/
/****************** Timer / Counter 0 ***********************/
/************************************************************/
/* Timer/Counter Control Register – TCCR0 */
#define TCCR0 *((u8 *)0x53)

#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

/* Timer/Counter0 (8 Bits) */
#define TCNT0 *((volatile u8 *)0x52)

/* Timer/Counter0 Output Compare Register */
#define OCR0 *((volatile u8 *)0x5C)

/************************************************************/
/****************** Timer / Counter 2 ***********************/
/************************************************************/
/* Timer/Counter Control Register – TCCR2 */
#define TCCR2 *((u8 *)0x45)

#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2 7

/* Timer/Counter2 (8 Bits) */
#define TCNT2 *((volatile u8 *)0x44)

/* Timer/Counter2 Output Compare Register */
#define OCR2 *((volatile u8 *)0x43)

/************************************************************/
/****************** Timer / Counter 1 ***********************/
/************************************************************/

/*Timer/Counter1 Control Register A –  */
#define TCCR1A *((volatile u8 *)0x4F)

#define WGM10 0
#define WGM11 1
#define FOC1B 2
#define FOC1A 3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

/*Timer/Counter1 Control Register B */
#define TCCR1B *((volatile u8 *)0x4E)

#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

/*Timer/Counter1 – TCNT1H*/
#define TCNT1H *((volatile u8 *)0x4D)
/*Timer/Counter1 – TCNT1L*/
#define TCNT1L *((volatile u8 *)0x4C)

/*Timer/Counter1 – TCNT1H + TCNT1L*/
#define TCNTW *((volatile u16 *)0x4C)

/*Output Compare Register 1 A OCR1AH */
#define OCR1AH *((volatile u8 *)0x4B)
/*Output Compare Register 1 A OCR1AL */
#define OCR1AL *((volatile u8 *)0x4A)
/*Output Compare Register 1 A OCR1AH + OCR1AL */
#define OCR1AW *((volatile u16 *)0x4A)

/*Output Compare Register 1 B OCR1BH */
#define OCR1BH *((volatile u8 *)0x49)
/*Output Compare Register 1 B OCR1BL */
#define OCR1BL *((volatile u8 *)0x48)

/*Output Compare Register 1 B OCR1BH + OCR1BL */
#define OCR1BW *((volatile u16 *)0x48)

/*Input Capture Register 1 ICR1H*/
#define ICR1H *((volatile u8 *)0x47)
/*Input Capture Register 1 ICR1L*/
#define ICR1L *((volatile u8 *)0x46)
/*Input Capture Register 1 ICR1H + ICR1L*/
#define ICR1W *((volatile u16 *)0x46)

/************************************************************/
/****************** Shared **********************************/
/************************************************************/

/* Timer/Counter Interrupt Mask Register – TIMSK */
#define TIMSK *((volatile u8 *)0x59)

#define TOIE0 0
#define OCIE0 1
#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2 6
#define OCIE2 7

/*Timer/Counter Interrupt Flag Register – TIFR*/
#define TIFR *((volatile u8 *)0x58)

#define TOV0 0
#define OCF0 1
#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1 5
#define TOV2 6
#define OCF2 7

#endif /* MCAL_TIMER_TIMER_REG_H_ */
