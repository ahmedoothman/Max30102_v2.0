/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: I2C			**************/
/***********		Version: 1.1		 	**************/
/***********		Date: 26 Sep 2022	 	**************/
/*********************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_int.h"
#include "TWI_pri.h"
#include "TWI_cfg.h"
#include "TWI_reg.h"
#include "TWI_int.h"

/**********************************************************************************************************
 * Description : Interface Function to Init in master mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vMasterInit(void)
{
	/*set the BitRate to 2 (400Kbs)*/
	TWBR = TWI_TWBR_VALUE;

	/*set the node address and the general call recognition status*/
	TWAR = (TWI_NODE_ADDRESS << TWI_SLAVE_ADDRESS_START_BIT) | (TWI_GCRE << 0);

	/*Enable the TWI*/
	TWCR = (1 << TWEN);
}

/**********************************************************************************************************
 * Description : Interface Function to send the start condition
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vSendStartCondition(void)
{
	/*Sending the start condition: clear the flag (by setting it), enable start bit & enable the TWI*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/*Waiting till the flag is set (status is presented)*/
	while (!GET_BIT(TWCR, TWINT))
		;
}

/**********************************************************************************************************
 * Description : Interface Function to send the stop condition
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vSendStopCondition(void)
{
	/*Sending the stop condition: clear the flag (by setting it), enable stop bit & enable the TWI*/
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/**********************************************************************************************************
 * Description : Interface Function to write data
 * Outputs     : void
 * Inputs      : the data
 ***********************************************************************************************************/
void TWI_vMasterWriteDataByte(u8 A_u8Data)
{
	/*Load the data*/
	TWDR = A_u8Data;
	/*clear the flag and start TWI*/
	TWCR = (1 << TWINT) | (1 << TWEN);
	/*Wait till flag is set*/
	while (!GET_BIT(TWCR, TWINT))
		;
}

/**********************************************************************************************************
 * Description : Interface Function to write the required slave address
 * Outputs     : void
 * Inputs      : the address of slave, the RW
 * NOTES	   : use the macros of reading/writing
 ***********************************************************************************************************/
void TWI_vMasterWriteSlaveAdd(u8 A_u8Address, u8 A_u8RW)
{
	/*Load the address of the slave and reading/writing state*/
	TWDR = (A_u8Address << 1) | (A_u8RW << 0);

	/*clear the flag and start TWI*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*Wait till flag is set*/
	while (!GET_BIT(TWCR, TWINT))
		;
}

/**********************************************************************************************************
 * Description : Interface Function to Read data with acknowledge
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
u8 TWI_u8MasterReadDataByteWith_ACK(void)
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

	/*Wait till data is received*/
	while (!GET_BIT(TWCR, TWINT))
		;

	return TWDR;
}

/**********************************************************************************************************
 * Description : Interface Function to read data without acknowledge
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
u8 TWI_u8MasterReadDataByteWith_NACK(void)
{
	TWCR = (1 << TWEN) | (1 << TWINT);

	/*Wait till data is received*/
	while (!GET_BIT(TWCR, TWINT))
		;

	/*Returning the byte read*/
	return TWDR;
}

u8 TWI_u8MasterReadNext(void)
{
	SET_BIT(TWCR, TWINT);
	while (GET_BIT(TWCR, TWINT) == 0)
		;
	return TWDR;
}

/**********************************************************************************************************
 * Description : Interface Function to get status of the bus
 * Outputs     : the status value
 * Inputs      : void
 * NOTES	   : use the macros for status to check for status
 ***********************************************************************************************************/
u8 TWI_u8MasterGetStatus(void)
{
	/*Returning the status only (Masking the prescaling bits and the reserved bit)*/
	return (TWSR & 0xF8);
}
