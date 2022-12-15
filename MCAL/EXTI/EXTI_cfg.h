/*
 * EXTI_cfg.h
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */

#ifndef MCAL_EXTI_EXTI_CFG_H_
#define MCAL_EXTI_EXTI_CFG_H_


/*
 * port and pin abstraction is used if we want to port the module on another MCU
 * */
/*sense control for INT0 &INT1 are: LOW_LEVEL, ANY_LOGICAL_CHANGE, FALLING_EDGE, RISING_EDGE*/


/*INT0 abstraction*/
#define INT0_PORT 			PORTD_ID
#define INT0_PIN  			PIN2_ID
#define INT0_SENSE_CONTROL  FALLING_EDGE

/*INT1 abstraction*/
#define INT1_PORT 			PORTD_ID
#define INT1_PIN  			PIN3_ID
#define INT1_SENSE_CONTROL  FALLING_EDGE

/*INT2 abstraction*/
#define INT2_PORT 			PORTB_ID
#define INT2_PIN  			PIN2_ID
#define INT2_SENSE_CONTROL  INT2_FALLING_EDGE

#endif /* MCAL_EXTI_EXTI_CFG_H_ */
