/*
 * GIE_reg.h
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */

#ifndef MCAL_GIE_GIE_REG_H_
#define MCAL_GIE_GIE_REG_H_

typedef enum{
	C, /*Carry flag*/
	Z, /*Zero flag*/
	N, /*Negative flag*/
	V, /*overFlow flag*/
	S, /*sign bit*/
	H, /*Half carry*/
	T, /*Bit copy*/
	I /*Global interrupt*/
};
/*here we made it volatile as we are changing the register our selves */
#define SREG *( (volatile u8*) 0x5F)


#endif /* MCAL_GIE_GIE_REG_H_ */
