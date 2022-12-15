/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: I2C			**************/
/***********		Version: 1.1		 	**************/
/***********		Date: 26 Sep 2022	 	**************/
/*********************************************************/
#ifndef MCAL_TWI_TWI_REG_H_
#define MCAL_TWI_TWI_REG_H_


/******************		TWI Bit Rate Register	 ******************/
#define TWBR *((volatile u8*) 0x20)
/*Bits: 0-7 are TWBR selects the division factor for the bit rate generator*/


/******************		TWI Control Register	 ******************/
#define TWCR *((volatile u8*) 0x56)
/*Bits: bit 1 is reserved*/
#define	TWIE	0	/*TWI Interrupt Enable*/
#define TWEN	2	/*TWI Enable Bit*/
#define TWWC	3	/*TWI Write Collision Flag*/
#define TWSTO	4	/*TWI STOP Condition Bit*/
#define TWSTA	5	/*TWI START Condition Bit*/
#define TWEA	6	/*TWI Enable Acknowledge Bit*/
#define TWINT	7	/*TWI Interrupt Flag*/


/******************		TWI Status Register		 ******************/
#define TWSR *((volatile u8*) 0x21)
/*Bits: bit 2 is reserved, 3-7 are status bits*/
#define TWPS0	0	/*Prescale*/
#define TWPS1	1	/*Prescale*/


/******************		TWI Data Register		 ******************/
#define TWDR *((volatile u8*) 0x23)
/*Bits: 0-7 are for data*/


/******************		TWI (Slave) Address Register 	 ******************/
#define TWAR *((volatile u8*) 0x22)
/*Bits: 1-7 are address register*/
#define TWGCE	0	/*TWI General Call Recognition Enable Bit*/


#endif /* MCAL_TWI_TWI_REG_H_ */
