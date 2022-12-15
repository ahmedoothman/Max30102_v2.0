/*
 * UART_reg.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_REG_H_
#define MCAL_UART_UART_REG_H_

/* USART I/O Data Register – UDR */
#define UDR *((volatile u8 *)0x2C)

/* USART Control and Status Register A – UCSRA */
#define UCSRA *((volatile u8 *)0x2B)
#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7
/* USART Control and Status Register B – UCSRB */
#define UCSRB *((volatile u8 *)0x2A)
#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7
/* USART Control and Status Register C – UCSRB */
#define UCSRC *((volatile u8 *)0x40)
#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS 3
#define UPM0 4
#define UPM1 5
#define UMSEL 6
#define URSEL 7
/*USART Baud Rate Registers – UBRRL and UBRRH */
#define UBRRH *((volatile u8 *)0x40)
#define URSEL 7
#define UBRRL *((volatile u8 *)0x29)

#endif /* MCAL_UART_UART_REG_H_ */
