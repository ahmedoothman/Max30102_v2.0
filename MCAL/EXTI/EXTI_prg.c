/*
 * EXTI_prg.c
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EXTI_reg.h"
#include "EXTI_pri.h"
#include "EXTI_cfg.h"
#include "EXTI_int.h"
#include "../DIO/DIO_int.h"

void EXTI_vInitINT0(void){
	DIO_vSetPinDir(INT0_PORT, INT0_PIN, DIR_INPUT);/*enable input*/
	DIO_vSetPinVal(INT0_PORT, INT0_PIN, VAL_HIGH);/*enable pull-up*/
	SET_BIT(GICR,INT0);

	/*Bit masking for the mode*/
	MCUCR = ( MCUCR&(0xFC) ) | (INT0_SENSE_CONTROL << ISC00);
}
void EXTI_vInitINT1(void){
	DIO_vSetPinDir(INT1_PORT, INT1_PIN, DIR_INPUT);/*enable input*/
	DIO_vSetPinVal(INT1_PORT, INT1_PIN, VAL_HIGH);/*enable pull-up*/
	SET_BIT(GICR,INT1);

	/*Bit masking for the mode*/
	MCUCR = ( MCUCR&(0xF3) ) | (INT1_SENSE_CONTROL << ISC10);
}

void EXTI_vInitINT2(void){
	DIO_vSetPinDir(INT2_PORT, INT2_PIN, DIR_INPUT);/*enable input*/
	DIO_vSetPinVal(INT2_PORT, INT2_PIN, VAL_HIGH);/*enable pull-up*/
	SET_BIT(GICR,INT2);

	/*Bit masking for the mode*/
	MCUCSR = ( MCUCSR&(0xBF) ) | (INT2_SENSE_CONTROL << ISC2);
}

void EXTI_vReg_Func( ptr_func_t ptr, u8 A_u8IntId){
	switch(A_u8IntId){
		case INT0_ID: G_ISR_INT0_ptr = ptr; break;
		case INT1_ID: G_ISR_INT1_ptr = ptr; break;
		case INT2_ID: G_ISR_INT2_ptr = ptr; break;
	}
}

void __vector_1(void){
	G_ISR_INT0_ptr();
}

void __vector_2(void){
	G_ISR_INT1_ptr();
}

void __vector_3(void){
	G_ISR_INT2_ptr();
}
