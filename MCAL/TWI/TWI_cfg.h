/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: I2C			**************/
/***********		Version: 1.1		 	**************/
/***********		Date: 26 Sep 2022	 	**************/
/*********************************************************/
#ifndef MCAL_TWI_TWI_CFG_H_
#define MCAL_TWI_TWI_CFG_H_

/* SCL frequency based on 8MHZ F_CPU
 *
 * Options:
 * 1- TWI_400KHZ
 * 2- TWI_100KHZ
 * */
#define TWI_TWBR_VALUE TWI_400KHZ

/*Define the required node address*/
#define TWI_NODE_ADDRESS 0b0000001

/* General Call Recognition Enable
 *
 * Options:
 * 1- TWI_GCRE_ENABLE
 * 2- TWI_GCRE_DISABLE
 * */
#define TWI_GCRE TWI_GCRE_DISABLE

#define TWI_RECEVIED_DATA_NACK 0x58
#define TWI_RECEVIED_DATA_ACK 0x50

#endif /* MCAL_TWI_TWI_CFG_H_ */
