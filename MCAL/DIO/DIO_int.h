/*
 * DIO_int.h
 *
 *  Created on: 19 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

/*ATmega 32 has 4 DIO ports*/
typedef enum {
	PORTA_ID,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID
};

/*Each port has 8 pins*/
typedef enum {
	PIN0_ID,
    PIN1_ID,
    PIN2_ID,
    PIN3_ID,
    PIN4_ID,
    PIN5_ID,
    PIN6_ID,
    PIN7_ID
};

/*Values possible either logic high or logic low*/
#define VAL_HIGH 1
#define VAL_LOW  0

/*Direction of the pin/port*/
#define DIR_OUTPUT 1
#define DIR_INPUT  0

void DIO_vSetPinDir  (u8 A_u8PortId, u8 A_u8PinId, u8 A_u8Dir);
void DIO_vSetPortDir (u8 A_u8PortId, u8 A_u8Dir);

void DIO_vSetPinVal  (u8 A_u8PortId, u8 A_u8PinId, u8 A_u8Val);
void DIO_vSetPortVal (u8 A_u8PortId, u8 A_u8Val);

u8 DIO_u8GetPinVal   (u8 A_u8PortId, u8 A_u8PinId);
u8 DIO_u8GetPortVal  (u8 A_u8PortId);

void DIO_vTogPin     (u8 A_u8PortId, u8 A_u8PinId);
void DIO_vTogPort    (u8 A_u8PortId, u8 A_u8PinId);


#endif /* MCAL_DIO_DIO_INT_H_ */
