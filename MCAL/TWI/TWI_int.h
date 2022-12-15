
/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: I2C			**************/
/***********		Version: 1.1		 	**************/
/***********		Date: 26 Sep 2022	 	**************/
/*********************************************************/

#ifndef MCAL_TWI_TWI_INT_H_
#define MCAL_TWI_TWI_INT_H_

/*****************		the status codes		*****************/
#define TWI_STATUS_START 0x08        // start has been sent
#define TWI_STATUS_REP_START 0x10    // repeated start
#define TWI_STATUS_MT_SLA_W_ACK 0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TWI_STATUS_MT_SLA_R_ACK 0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TWI_STATUS_MT_DATA_ACK 0x28  // Master transmit data and ACK has been received from Slave.
#define TWI_STATUS_MR_DATA_ACK 0x50  // Master received data and send ACK to slave
#define TWI_STATUS_MR_DATA_NACK 0x58 // Master received data but doesn't send ACK to slave

/*****************		the states of addressing a slave (reading/writing)		*****************/
#define TWI_SLAVE_RD 1
#define TWI_SLAVE_WR 0

/**********************************************************************************************************
 * Description : Interface Function to Init in master mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vMasterInit(void);

/**********************************************************************************************************
 * Description : Interface Function to send the start condition
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vSendStartCondition(void);

/**********************************************************************************************************
 * Description : Interface Function to send the stop condition
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TWI_vSendStopCondition(void);

/**********************************************************************************************************
 * Description : Interface Function to write data
 * Outputs     : void
 * Inputs      : the data
 ***********************************************************************************************************/
void TWI_vMasterWriteDataByte(u8 A_u8Data);

/**********************************************************************************************************
 * Description : Interface Function to write the required slave address
 * Outputs     : void
 * Inputs      : the data
 * NOTES	   : use the macros of reading/writing
 ***********************************************************************************************************/
void TWI_vMasterWriteSlaveAdd(u8 A_u8Data, u8 A_u8RW);

/**********************************************************************************************************
 * Description : Interface Function to Read data with acknowledge
 * Outputs     : the data read
 * Inputs      : void
 ***********************************************************************************************************/
u8 TWI_u8MasterReadDataByteWith_ACK(void);

/**********************************************************************************************************
 * Description : Interface Function to read data without acknowledge
 * Outputs     : the data read
 * Inputs      : void
 ***********************************************************************************************************/
u8 TWI_u8MasterReadDataByteWith_NACK(void);

/**********************************************************************************************************
 * Description : Interface Function to get status of the bus
 * Outputs     : the status code
 * Inputs      : void
 * NOTE		   : you can check for status codes with status macros
 ***********************************************************************************************************/
u8 TWI_u8MasterGetStatus(void);

/**********************************************************************************************************
 * Description : Interface Function to get status of the bus
 * Outputs     : the next data byte
 * Inputs      : void
 * NOTE		   : YOU MUST FIRST USE ANY READ FUNCTION BEFORE CALLING THIS
 ***********************************************************************************************************/
u8 TWI_u8MasterReadNext(void);

#endif /* MCAL_TWI_TWI_INT_H_ */
