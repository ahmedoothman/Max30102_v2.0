/*
 * TIMER_int.h
 *
 *  Created on: Sep 13, 2022
 *      Author: Dell
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2
#define RISING 0
#define FALLING 1
void TIMER_vInit(u8 A_u8TIMERID);
void TIMER_vSetPreLoad(u8 A_u8TIMERID, u16 A_u16PreloadValue);
void TIMER_vSetOcrValue(u8 A_u8TIMERID, u16 A_u16OcrValue);
void TIMER_vSetOCR1AWValue(u16 A_u16OcrValue);
void TIMER_vSetOCR1BWValue(u16 A_u16OcrValue);
void TIMER_vSetICR1WValue(u16 A_u16OcrValue);

void TIMER_vPWMSignal(u8 A_u8TIMERID, f32 A_f32DutyCycle);
void TIMER_vDelayMS(u8 A_u8TIMERID, f32 A_f32Delay, FUNC_PTR_IV_OV A_FPtr);

u16 TIMER_u16GetICU();
void TIMER_vCongfigureICU();
void TIMER_vsetCallBackFunctionOvfTIMER1(FUNC_PTR_IV_OV A_FPtr);
void TIMER_vsetCallBackFunctionIcuTIMER1(FUNC_PTR_IV_OV A_FPtr);
void TIMER_vSetTriggeringICU(u8 A_u8Triggering);
void TIMER_vDisableIntICU();
u16 TIMER_u16GetOverFlow();

#endif /* MCAL_TIMER_TIMER_INT_H_ */
