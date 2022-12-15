/*
 * DIO_reg.h
 *
 *  Created on: 19 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_DIO_DIO_REG_H_
#define MCAL_DIO_DIO_REG_H_

/*PORTA*/
#define PORTA *( (u8 *) 0x3B)
#define DDRA  *( (u8 *) 0x3A)
#define PINA  *( (volatile u8 *) 0x39)

/*PORTB*/
#define PORTB *( (u8 *) 0x38)
#define DDRB  *( (u8 *) 0x37)
#define PINB  *( (volatile u8 *) 0x36)

/*PORTC*/
#define PORTC *( (u8 *) 0x35)
#define DDRC  *( (u8 *) 0x34)
#define PINC  *( (volatile u8 *) 0x33)

/*PORTD*/
#define PORTD *( (u8 *) 0x32)
#define DDRD  *( (u8 *) 0x31)
#define PIND  *( (volatile u8 *) 0x30)

#endif /* MCAL_DIO_DIO_REG_H_ */
