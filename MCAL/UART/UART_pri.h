/*
 * UART_pri.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_PRI_H_
#define MCAL_UART_UART_PRI_H_

/* Parity Mode */
#define DISABLED 0
#define ENABLED_EVEN_PARITY 2
#define ENABLED_ODD_PARITY 3

#define PARITY_MASK 0b11001111

/* STOP BIT SELECT MODE */
#define ONE_BIT 0
#define TWO_BIT 1

#define STOP_BIT_MASK 0b11110111

/* Character Size Select */
#define CHAR_5_BIT_UCSRC 0
#define CHAR_6_BIT_UCSRC 1
#define CHAR_7_BIT_UCSRC 2
#define CHAR_8_BIT_UCSRC 3
#define CHAR_9_BIT_UCSRC 3

#define CHAR_5_BIT_UCSRB 0
#define CHAR_6_BIT_UCSRB 0
#define CHAR_7_BIT_UCSRB 0
#define CHAR_8_BIT_UCSRB 0
#define CHAR_9_BIT_UCSRB 1

#define FORMAT_MODE_MASK_UCSRC 0b11111001
#define FORMAT_MODE_MASK_UCSRB 0b11111011

/* Async Or Sync */
#define ASYNC 0
#define SYNC 1

#define ASYNC_SYNC_MASK 0b10111111

/* BAUD RATE MASK */
#define BAUD_RATE_MASK 0b11110000

/* ISR */
/* RX Complete Interrupt */
void __vector_13(void) __attribute__((signal));
/* UDRE Data Register Empty */
void __vector_14(void) __attribute__((signal));
/* TX Complete Interrupt */
void __vector_15(void) __attribute__((signal));
#endif /* MCAL_UART_UART_PRI_H_ */
