/*
 * EXTI_reg.h
 *
 *  Created on: 29 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_EXTI_EXTI_REG_H_
#define MCAL_EXTI_EXTI_REG_H_

/*GICR*/
#define MCUCSR  *( (u8*) 0x54)
/*pins*/
#define ISC2 6
/*PIN 7,4,3,2,1,0 are not used in this peripheral. pin 5 is reserved*/

/*GICR*/
#define GICR *( (u8*) 0x5B)
/*pins*/
#define INT1 7
#define INT0 6
#define INT2 5
/*pins 4,3,2 are reserved, pins 1,0 are for another peripheral*/

/*GIFR*/
#define GIFR *( (volatile u8*) 0x5A)
/*pins*/
#define INTF1 7
#define INTF0 6
#define INTF2 5
/*pins 4,3,2,1,0 are not used in this peripheral*/

/*MCUCR*/
#define MCUCR *( (u8*) 0x55)
/*pins*/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
/*pins 4,5,6,7 are not used in this peripheral*/

#endif /* MCAL_EXTI_EXTI_REG_H_ */
