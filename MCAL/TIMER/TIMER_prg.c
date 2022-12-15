/*
 * TIMER_prg.c
 *
 *  Created on: Sep 13, 2022
 *      Author: Dell
 */

#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "../GIE/GIE_int.h"
#include "../DIO/DIO_int.h"

#include "TIMER_reg.h"
#include "TIMER_int.h"
#include "TIMER_cfg.h"
#include "TIMER_pri.h"

#define GIE_vSetGlobalInterrupt GIE_vEnableGlobaLInt
FUNC_PTR_IV_OV GLB_PTRF_TIM1_OVF, GLB_PTRF_TIM0_OVF, GLB_PTRF_TIM2_OVF;
FUNC_PTR_IV_OV GLB_PTRF_TIM1_CTC, GLB_PTRF_TIM0_CTC, GLB_PTRF_TIM2_CTC;
FUNC_PTR_IV_OV GLB_PTRF_TIM1_ICU;
static u32 G_u32Timer0Counts, G_u32Timer1Counts, G_u32Timer2Counts;
static u32 G_u32Timer0PreLoad, G_u32Timer1PreLoad, G_u32Timer2PreLoad;
static u32 G_u16Timer1OVerflows = 0;

/*********************************************************/
/* INIT For all 3 timers, NOTE: Change your configuration*/
/*********************************************************/

void TIMER_vInit(u8 A_u8TIMERID)
{

    switch (A_u8TIMERID)
    {
    case TIMER0:
        /* Timer Mode */
        TCCR0 = (TCCR0 & WAVE_GENERATION_MODE_MASK) | TIMER0_WAVE_GENERATION_MODE;
        /* Set OC0 pin State */
        TCCR0 = (TCCR0 & OCR_PIN_MASK_T0_T2) | (TIMER0_OCR_PIN_MODE << 4);
        /* set prescale */
        TCCR0 = (TCCR0 & CLOCK_SOURCE_MASK) | TIMER0_PRESCALE_MODE;

        break;
    case TIMER2:
        /* Timer Mode */
        TCCR2 = (TCCR2 & WAVE_GENERATION_MODE_MASK) | TIMER2_WAVE_GENERATION_MODE;
        /* Set OC0 pin State */
        TCCR2 = (TCCR2 & OCR_PIN_MASK_T0_T2) | (TIMER2_OCR_PIN_MODE << 4);
        /* set prescale */
        TCCR2 = (TCCR2 & CLOCK_SOURCE_MASK) | TIMER2_PRESCALE_MODE;

        break;
    case TIMER1:
        /* SET COMPARE OUTPUT MODE FOR PIN OC1A OC2B */
        TCCR1A = (TCCR1A & OCR_PIN_MASK_T3_A) | (TIMER1_OCRA_PIN_MODE << 6);
        TCCR1A = (TCCR1A & OCR_PIN_MASK_T3_B) | (TIMER1_OCRB_PIN_MODE << 4);
        /* SET PRESCALE */
        TCCR1B = (TCCR1B & CLOCK_SOURCE_MASK) | TIMER1_PRESACLE_MODE;
        /* SET WAVE GENERATION MODE */
        TCCR1A = (TCCR1A & TCCR1A_WAVE_MODE_MASK) | TIMER1_WAVE_GENERATION_MODE_TCCR1A;
        TCCR1B = (TCCR1B & TCCR1B_WAVE_MODE_MASK) | TIMER1_WAVE_GENERATION_MODE_TCCR1B;
        break;

    default:
        break;
    }
}
/*********************************************************/
/* Set Preload For all 3 timers*/
/*********************************************************/
void TIMER_vSetPreLoad(u8 A_u8TIMERID, u16 A_u16PreloadValue)
{
    switch (A_u8TIMERID)
    {
    case TIMER0:
        TCNT0 = (u8)A_u16PreloadValue;
        break;
    case TIMER2:
        TCNT2 = (u8)A_u16PreloadValue;
        break;
    case TIMER1:
        TCNTW = A_u16PreloadValue;
        break;

    default:
        break;
    }
}
/*********************************************************/
/* Set OCR For all 3 timers , note don't use it with Timer1*/
/*********************************************************/
void TIMER_vSetOcrValue(u8 A_u8TIMERID, u16 A_u16OcrValue)
{
    switch (A_u8TIMERID)
    {
    case TIMER0:
        OCR0 = (u8)A_u16OcrValue;
        break;
    case TIMER2:
        OCR2 = (u8)A_u16OcrValue;
        break;
    case TIMER1:
        /* THERE IS A AND B*/
        OCR1AW = A_u16OcrValue;
        break;

    default:
        break;
    }
}
/*********************************************************/
/* Set OCR1A For Timer 1*/
/*********************************************************/
void TIMER_vSetOCR1AWValue(u16 A_u16OcrValue)
{
    OCR1AW = A_u16OcrValue;
}
/*********************************************************/
/* Set OCR1B For Timer 1*/
/*********************************************************/
void TIMER_vSetOCR1BWValue(u16 A_u16OcrValue)
{
    OCR1BW = A_u16OcrValue;
}
/*********************************************************/
/* Set ICR1W For Timer 1*/
/*********************************************************/
void TIMER_vSetICR1WValue(u16 A_u16OcrValue)
{
    ICR1W = A_u16OcrValue;
}
/********************************************************/
/* Generate Delays, ALL TIMERS */
/********************************************************/

void TIMER_vDelayMS(u8 A_u8TIMERID, f32 A_f32Delay, FUNC_PTR_IV_OV A_FPtr)
{
    GIE_vSetGlobalInterrupt();
    f32 L_f32OverFlowTime, L_f32DelayReq;
    f32 L_f32NumberOfOverflows, L_f32PreLoadFrac;
    u32 L_u32Counts, L_u32PreLoad, L_u32Ocr, L_u32TickTime;
    L_f32DelayReq = (A_f32Delay * 1.0) / 1000;
    switch (A_u8TIMERID)
    {
    /************************************************/
    /********************* TIMER0 *******************/
    /************************************************/
    case TIMER0:

#if TIMER0_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_NORMAL

        L_f32OverFlowTime = (TIMER0_PRESCALE_VALUE * 1.0 / FCPU) * TIMER0_RESOLUTION;
        L_f32NumberOfOverflows = (L_f32DelayReq * 1.0) / L_f32OverFlowTime;
        L_u32Counts = (u32)L_f32NumberOfOverflows;
        L_f32PreLoadFrac = L_f32NumberOfOverflows - L_u32Counts;
        L_u32PreLoad = (u32)((1 - L_f32PreLoadFrac) * TIMER0_RESOLUTION);
        G_u32Timer0PreLoad = L_u32PreLoad;
        G_u32Timer0Counts = L_u32Counts + 1;
        TIMER_vSetPreLoad(TIMER0, L_u32PreLoad);
        /* Assign callback function */
        GLB_PTRF_TIM0_OVF = A_FPtr;
        /* Enable Timer Overflow Interrupt */
        SET_BIT(TIMSK, TOIE0);
#elif TIMER0_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_CTC
        L_u32TickTime = TIMER0_PRESCALE_VALUE / FCPU;
        L_u32Counts = L_f32DelayReq / L_u32TickTime;
        if (L_u32Counts <= TIMER0_RESOLUTION)
        { /* NUMBER OF COUNTS CAN FIT INSIDE THE OCR */
            TIMER_vSetOcrValue(TIMER0, L_u32Counts);
            G_u32Timer0Counts = 1;
        }
        else
        {
            L_u32Ocr = 250;
            L_u32Counts = ((L_f32DelayReq * FCPU) / TIMER0_PRESCALE_VALUE) / L_u32Ocr;
            /* NUMBER OF COUNTS CANNOT FIT INSIDE THE OCR */
            /* SO We Set OCR With Init Value and counts the compare mactches*/
            TIMER_vSetOcrValue(TIMER0, L_u32Ocr);
            G_u32Timer0Counts = L_u32Counts;
        }
        /* Assign callback function */
        GLB_PTRF_TIM0_CTC = A_FPtr;
        /* Enable Timer Overflow Interrupt */
        SET_BIT(TIMSK, OCIE0);
#else
#warning "This mode is not used in delay"
#endif
        break;
    /************************************************/
    /********************* TIMER2 *******************/
    /************************************************/
    case TIMER2:
#if TIMER2_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_NORMAL

        L_f32OverFlowTime = (TIMER2_PRESCALE_VALUE * 1.0 / FCPU) * TIMER2_RESOLUTION;
        L_f32NumberOfOverflows = (L_f32DelayReq * 1.0) / L_f32OverFlowTime;
        L_u32Counts = (u32)L_f32NumberOfOverflows;
        L_f32PreLoadFrac = L_f32NumberOfOverflows - L_u32Counts;
        L_u32PreLoad = (u32)((1 - L_f32PreLoadFrac) * TIMER2_RESOLUTION);
        G_u32Timer2PreLoad = L_u32PreLoad;
        G_u32Timer2Counts = L_u32Counts + 1;
        TIMER_vSetPreLoad(TIMER2, L_u32PreLoad);
        /* Assign callback function */
        GLB_PTRF_TIM2_OVF = A_FPtr;
        /* Enable Timer Overflow Interrupt */
        SET_BIT(TIMSK, TOIE2);

//
#elif TIMER2_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_CTC
        L_u32TickTime = TIMER2_PRESCALE_VALUE / FCPU;
        L_u32Counts = L_f32DelayReq / L_u32TickTime;
        if (L_u32Counts <= TIMER2_RESOLUTION)
        { /* NUMBER OF COUNTS CAN FIT INSIDE THE OCR */
            TIMER_vSetOcrValue(TIMER2, L_u32Counts);
            G_u32Timer2Counts = 1;
        }
        else
        {
            L_u32Ocr = 250;
            L_u32Counts = ((L_f32DelayReq * FCPU) / TIMER2_PRESCALE_VALUE) / L_u32Ocr;
            /* NUMBER OF COUNTS CANNOT FIT INSIDE THE OCR */
            /* SO We Set OCR With Init Value and counts the compare mactches*/
            TIMER_vSetOcrValue(TIMER2, L_u32Ocr);
            G_u32Timer2Counts = L_u32Counts;
        }
        /* Assign callback function */
        GLB_PTRF_TIM2_CTC = A_FPtr;
        /* Enable Timer Overflow Interrupt */
        SET_BIT(TIMSK, OCIE2);
#else
#warning "This mode is not used in delay"
#endif
        break;
    /************************************************/
    /********************* TIMER1 *******************/
    /************************************************/
    case TIMER1:
        /*You will need it*/
        /* Assign callback function */
        GLB_PTRF_TIM1_OVF = A_FPtr;
        /* Enable Timer Overflow Interrupt */
        GLB_PTRF_TIM1_CTC = A_FPtr;
        break;

    default:
        break;
    }
}

/********************************************************/
/* Generate PWM SIGNALS, ALL TIMERS */
/********************************************************/

void TIMER_vPWMSignal(u8 A_u8TIMERID, f32 A_f32DutyCycle)
{
    u16 L_u16OcrValue;
    switch (A_u8TIMERID)
    {
    /************************************************/
    /********************* TIMER0 *******************/
    /************************************************/
    case TIMER0:
        /* *********************************** */
        /* SET OC0 as Output */
        /* *********************************** */

        DIO_vSetPinDir(PORTB_ID, PIN3_ID, DIR_OUTPUT);
        /* *********************************** */
        /* Check Modes */
        /* *********************************** */

#if TIMER0_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_PWM_FAST
#if TIMER0_OCR_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER0_RESOLUTION;
        TIMER_vSetOcrValue(TIMER0, L_u16OcrValue);
#elif TIMER0_OCR_PIN_MODE == SET_COMPARE_MODE_INVERTING
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER0_RESOLUTION;
        TIMER_vSetOcrValue(TIMER0, L_u16OcrValue);
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#elif TIMER0_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_PWM_PC
#if TIMER0_OCR_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER0_RESOLUTION;
        TIMER_vSetOcrValue(TIMER0, L_u16OcrValue);
#elif TIMER0_OCR_PIN_MODE == SET_COMPARE_MODE_INVERTING
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER0_RESOLUTION;
        TIMER_vSetOcrValue(TIMER0, L_u16OcrValue);
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#else
#warning "This mode is not used in pwm signal"
#endif
        break;
    /************************************************/
    /********************* TIMER2 *******************/
    /************************************************/
    case TIMER2:
        /* *********************************** */
        /* SET OC2 as Output */
        /* *********************************** */
        DIO_vSetPinDir(PORTD_ID, PIN7_ID, DIR_OUTPUT);
        /* *********************************** */
        /* Check Modes */
        /* *********************************** */
#if TIMER2_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_PWM_FAST
#if TIMER2_OCR_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER2_RESOLUTION;
        TIMER_vSetOcrValue(TIMER2, L_u16OcrValue);
#elif TIMER2_OCR_PIN_MODE == SET_COMPARE_MODE_INVERTING
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER2_RESOLUTION;
        TIMER_vSetOcrValue(TIMER2, L_u16OcrValue);
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#elif TIMER2_WAVE_GENERATION_MODE == WAVE_GENERATION_MODE_PWM_PC
#if TIMER2_OCR_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER2_RESOLUTION;
        TIMER_vSetOcrValue(TIMER2, L_u16OcrValue);
#elif TIMER2_OCR_PIN_MODE == SET_COMPARE_MODE_INVERTING
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER2_RESOLUTION;
        TIMER_vSetOcrValue(TIMER2, L_u16OcrValue);
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#else
#warning "This mode is not used in pwm signal"
#endif
        break;
    /************************************************/
    /********************* TIMER1 *******************/
    /************************************************/
    case TIMER1:
#if TIMER1_WAVE_GENERATION_MODE_TCCR1A == FAST_PWM_ICR1_TCCR1A && TIMER1_WAVE_GENERATION_MODE_TCCR1B == FAST_PWM_ICR1_TCCR1B
/* SET TMIER MODE TO FAST PWM ICR1 FROM CONFIGURATION */
#if TIMER1_OCRA_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        ICR1W = TIMER1_TOP;
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER1_TOP;
        TIMER_vSetOcrValue(TIMER1, L_u16OcrValue);
#elif TIMER1_OCRA_PIN_MODE == SET_COMPARE_MODE_INVERTING
        ICR1W = TIMER1_TOP;
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER1_TOP;
        TIMER_vSetOcrValue(TIMER1, L_u16OcrValue);
        break;
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#if TIMER1_OCRB_PIN_MODE == CLEAR_COMPARE_MODE_NON_INVERTING
        L_u16OcrValue = (A_f32DutyCycle * 1.0 / 100) * TIMER1_TOP;
        TIMER_vSetOcrValue(TIMER1, L_u16OcrValue);
#elif TIMER1_OCRB_PIN_MODE == SET_COMPARE_MODE_INVERTING
        L_u16OcrValue = (1 - (A_f32DutyCycle * 1.0 / 100)) * TIMER1_TOP;
        TIMER_vSetOcrValue(TIMER1, L_u16OcrValue);
#else
#warning "This PIN Mode is not used in PWM Signal"
#endif
#else
#warning "This Mode is not used in pwm signal"
#endif
        break;

    default:
        break;
    }
}
/********************************************************/
/* Get ICU Value */
/********************************************************/
u16 TIMER_u16GetICU()
{
    return ICR1W;
}
/********************************************************/
/* SET CallBack Function for overflow interrupt timer1 */
/********************************************************/
void TIMER_vsetCallBackFunctionOvfTIMER1(FUNC_PTR_IV_OV A_FPtr)
{
    /* SET CALL BACK FUNCTION */
    GLB_PTRF_TIM1_OVF = A_FPtr;
}
/********************************************************/
/* SET CallBack Function for ICU interrupt timer1 */
/********************************************************/
void TIMER_vsetCallBackFunctionIcuTIMER1(FUNC_PTR_IV_OV A_FPtr)
{
    GLB_PTRF_TIM1_ICU = A_FPtr;
}
/********************************************************************/
/* Configure ICU To be used , NOTE it is seperate from function init */
/*********************************************************************/
void TIMER_vCongfigureICU()
{
    /* SELECT NORMAL MODE FROM CONFIGURATIONs */
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
    /* SET TRTIGGER TO RISING EDGE */
    SET_BIT(TCCR1B, ICES1);
    /* ENABLE INTERRUPT for ICU */
    SET_BIT(TIMSK, TICIE1);
    /* Enable Overflow interrupt */
    SET_BIT(TIMSK, TOIE1);
    /* SET ICP AS INPUT PD6 */
    DIO_vSetPinDir(PORTD_ID, PIN6_ID, DIR_INPUT);
    /* SET PRESCALE FROM CONFIGURATIONS to 8*/
    CLR_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
}
/********************************************************************/
/* Disable ICU Interrupt */
/*********************************************************************/
void TIMER_vDisableIntICU()
{
    /* Disable INTERRUPT for ICU */
    CLR_BIT(TIMSK, TICIE1);
}
/********************************************************************/
/* Set Triggering , Rising Or Falling for ICES1 for ICU*/
/*********************************************************************/
void TIMER_vSetTriggeringICU(u8 A_u8Triggering)
{
    switch (A_u8Triggering)
    {
    case RISING:
        /* SET TRIGGERING TO RISING EDGE */
        SET_BIT(TCCR1B, ICES1);
        break;
    case FALLING:
        /* SET TRIGGERING TO FALLING EDGE */
        CLR_BIT(TCCR1B, ICES1);
        break;
    default:
        break;
    }
}
/*********************************************************************/
/******************** ISR / TIMER0**************************/
/*********************************************************************/
/* TIMER0 COMP */
void __vector_10(void)
{
    static u32 L_u32Counter = 0;
    L_u32Counter++;
    if (L_u32Counter == G_u32Timer0Counts)
    {
        L_u32Counter = 0;
        GLB_PTRF_TIM0_CTC();
    }
}
/* TIMER0 OVF */
void __vector_11(void)
{
    static u32 L_u32Counter = 0;
    L_u32Counter++;
    if (L_u32Counter == G_u32Timer0Counts)
    {
        L_u32Counter = 0;
        TIMER_vSetPreLoad(TIMER0, G_u32Timer0PreLoad);
        GLB_PTRF_TIM0_OVF();
    }
}
/*********************************************************************/
/******************** ISR / TIMER2 **************************/
/*********************************************************************/
/* TIMER COMP */
void __vector_4(void)
{
    static u32 L_u32Counter = 0;
    L_u32Counter++;
    if (L_u32Counter == G_u32Timer2Counts)
    {
        L_u32Counter = 0;
        GLB_PTRF_TIM2_CTC();
    }
}
/* TIMER2 OVF */
void __vector_5(void)
{
    static u32 L_u32Counter = 0;
    L_u32Counter++;
    if (L_u32Counter == G_u32Timer2Counts)
    {
        L_u32Counter = 0;
        TIMER_vSetPreLoad(TIMER2, G_u32Timer2PreLoad);
        GLB_PTRF_TIM2_OVF();
    }
}
/*********************************************************************/
/******************** ISR / TIMER1 **************************/
/*********************************************************************/
/* ICU */
void __vector_6(void)
{
    GLB_PTRF_TIM1_ICU();
}
/* OVF */
void __vector_9(void)
{
    GLB_PTRF_TIM1_OVF();
}
