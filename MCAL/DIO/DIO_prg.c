/*
 * DIO_prg.c
 *
 *  Created on: 19 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_reg.h"
#include "DIO_int.h"





void DIO_vSetPinDir (u8 A_u8PortId, u8 A_u8PinId, u8 A_u8Dir){
	switch(A_u8PortId){
		case PORTA_ID: WRT_BIT(DDRA, A_u8PinId, A_u8Dir); break;
		case PORTB_ID: WRT_BIT(DDRB, A_u8PinId, A_u8Dir); break;
		case PORTC_ID: WRT_BIT(DDRC, A_u8PinId, A_u8Dir); break;
		case PORTD_ID: WRT_BIT(DDRD, A_u8PinId, A_u8Dir); break;
	}
}

void DIO_vSetPortDir (u8 A_u8PortId, u8 A_u8Dir){
	switch(A_u8PortId){
		case PORTA_ID: (A_u8Dir == DIR_INPUT) ? (DDRA=0x00) : (DDRA=0xFF); break;
		case PORTB_ID: (A_u8Dir == DIR_INPUT) ? (DDRB=0x00) : (DDRB=0xFF); break;
		case PORTC_ID: (A_u8Dir == DIR_INPUT) ? (DDRC=0x00) : (DDRC=0xFF); break;
		case PORTD_ID: (A_u8Dir == DIR_INPUT) ? (DDRD=0x00) : (DDRD=0xFF); break;
	}
}

void DIO_vSetPinVal (u8 A_u8PortId, u8 A_u8PinId, u8 A_u8Val){
	switch(A_u8PortId){
		case PORTA_ID: WRT_BIT(PORTA, A_u8PinId, A_u8Val); break;
		case PORTB_ID: WRT_BIT(PORTB, A_u8PinId, A_u8Val); break;
		case PORTC_ID: WRT_BIT(PORTC, A_u8PinId, A_u8Val); break;
		case PORTD_ID: WRT_BIT(PORTD, A_u8PinId, A_u8Val); break;
	}
}

void DIO_vSetPortVal (u8 A_u8PortId, u8 A_u8Val){
	switch(A_u8PortId){
		case PORTA_ID: PORTA = A_u8Val; break;
		case PORTB_ID: PORTB = A_u8Val; break;
		case PORTC_ID: PORTC = A_u8Val; break;
		case PORTD_ID: PORTD = A_u8Val; break;
	}
}

u8 DIO_u8GetPinVal (u8 A_u8PortId, u8 A_u8PinId){
	u8 L_u8PinVal;
	switch(A_u8PortId){
		case PORTA_ID: L_u8PinVal = GET_BIT(PINA, A_u8PinId); break;
		case PORTB_ID: L_u8PinVal = GET_BIT(PINB, A_u8PinId); break;
		case PORTC_ID: L_u8PinVal = GET_BIT(PINC, A_u8PinId); break;
		case PORTD_ID: L_u8PinVal = GET_BIT(PIND, A_u8PinId); break;
	}
	return L_u8PinVal;
}
u8 DIO_u8GetPortVal (u8 A_u8PortId){
	u8 L_u8PortVal;
	switch(A_u8PortId){
		case PORTA_ID: L_u8PortVal = PINA; break;
		case PORTB_ID: L_u8PortVal = PINB; break;
		case PORTC_ID: L_u8PortVal = PINC; break;
		case PORTD_ID: L_u8PortVal = PIND; break;
	}
	return L_u8PortVal;
}

void DIO_vTogPin (u8 A_u8PortId, u8 A_u8PinId){
	switch(A_u8PortId){
		case PORTA_ID: TOG_BIT(PORTA, A_u8PinId); break;
		case PORTB_ID: TOG_BIT(PORTB, A_u8PinId); break;
		case PORTC_ID: TOG_BIT(PORTC, A_u8PinId); break;
		case PORTD_ID: TOG_BIT(PORTD, A_u8PinId); break;
	}
}
void DIO_vTogPort (u8 A_u8PortId, u8 A_u8PinId){
	switch(A_u8PortId){
		case PORTA_ID: PORTA ^= 0xFF; break;
		case PORTB_ID: PORTB ^= 0xFF; break;
		case PORTC_ID: PORTC ^= 0xFF; break;
		case PORTD_ID: PORTD ^= 0xFF; break;
	}
}
