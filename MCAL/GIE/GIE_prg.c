/*
 * GIE_prg.c
 *
 *  Created on: 29 Aug 2022
 *      Author: TaqiEldeen
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "GIE_reg.h"
#include "GIE_int.h"

/*Enable global interrupt*/
void GIE_vEnableGlobaLInt(){
	SET_BIT(SREG, I);
}

/*Disable global interrupt*/
void GIE_vDisableGlobalInt(){
	CLR_BIT(SREG, I);
}
