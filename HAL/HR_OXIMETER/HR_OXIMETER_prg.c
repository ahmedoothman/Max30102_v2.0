/*
 * HR_OXIMETER_reg.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Ahmed Othman
 *  "THIS FOR MAX30102 Senseor (Heart Rate and Oximeter)"
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TWI/TWI_int.h"
#include "../../MCAL/TIMER/TIMER_int.h"

#include "HR_OXIMETER_reg.h"
#include "HR_OXIMETER_pri.h"
#include "HR_OXIMETER_cfg.h"
#include "HR_OXIMETER_int.h"

#include <avr/delay.h>
#include <math.h>
/* Global variables */
volatile u32 G_u32Millis = 0;
/* Filters Variable */
volatile DC_Filter dcFilterIR;
volatile DC_Filter dcFilterRed;
volatile MEANDiff_Filter meanDiffIR;
volatile Butterworth_Filter lpbFilterIR;

volatile u8 G_u8CurrentPulseDetectorState;
volatile f32 G_f32CurrentBPM;
volatile f32 G_f32ValuesBPM[PULSE_BPM_SAMPLE_SIZE];
volatile f32 G_f32ValuesBPMSum;
volatile u8 G_u8ValuesBPMCount;
volatile u8 G_u8BPMIndex;
volatile u32 G_u32LastBeatThreshold;

volatile f32 G_f32IrAcValueSqSum = 0;
volatile f32 G_f32RedAcValueSqSum = 0;
volatile f32 G_f32CurrentSaO2Value = 0;
volatile u16 G_u16SamplesRecorded = 0;
volatile u16 G_u16PulseDetected = 0;

/* ********************************************************************* */
/* ******************************** init ******************************* */
/* ********************************************************************* */
void HR_OXIMETER_vInit()
{
    u8 L_u8RegContent;
    /* Init I2C Comm */
    TWI_vMasterInit();
    /* ******************************************** */
    /*
    -------Send Configuration of FIFO Register-------
    -> SMP AVG
    -> FIFO_ROLLOVER_EN
    -> FIFO_A_FULL
     */
    /* Enable ROLL OVER*/
    /* ******************************************** */

    L_u8RegContent = (SAMPLEAVG_SELECTED << SMP_AVE_START_BIT) | (1 << FIFO_ROLL_OVER_EN);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, FIFO_Configuration_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of MODE Register-------
    -> SHDN
    -> RESET
    -> MODE
     */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (MODE_CONTROL_SELECTED << MODE_START_BIT);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, MODE_Configuration_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of SPO2 Register-------
    -> SPO2 ADC Range
    -> SPO2 Sample Rate
    -> LED Pulse Width Control
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (ADCRANGE_SELECTED << SPO2_ADC_RGE_START_BIT) | (SAMPLERATE_SELECTED << SPO2_SR_START_BIT) | (PULSEWIDTH_SELECTED << LED_PW_START_BIT);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, SpO2_Configuration_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of MULTI Control Register-------
    ->SLOT1 IR
    ->SLOT2 LED
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (SLOT1_LED_SELECTED << SLOT_1_START_BIT) | (SLOT2_LED_SELECTED << SLOT_2_START_BIT);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, MULTI_LED_REG_S1_S2_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of LPA Register-------
    ->LED1 IR
    ->LED2 RED
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | LED1_IR_CURRENT_SELECTED;
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, LED1_PA_address, L_u8RegContent);
    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | LED2_RED_CURRENT_SELECTED;
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, LED2_PA_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Reset FIFO-------
    ->Write Ptr
    ->OverFlow Couter
    ->Read Ptr
    */
    /* ******************************************** */
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, FIFO_WR_PTR_address, 0x00);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, OVF_COUNTER_address, 0x00);
    HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, FIFO_RD_PTR_address, 0x00);

    /* ******************************************** */
    /*
    -------Start Timer Counts Every 2 milli sec -------
    */
    /* ******************************************** */
    TIMER_vInit(TIMER0);
    TIMER_vDelayMS(TIMER0, TIME_CONSTANT, HR_OXIMETER_vCountsMillis);
    /* ******************************************** */
    /*
    -------Init Variables -------
    */
    /* ******************************************** */
    dcFilterIR.w = 0;
    dcFilterIR.result = 0;
    dcFilterRed.w = 0;
    dcFilterRed.result = 0;

    meanDiffIR.count = 0;
    meanDiffIR.index = 0;
    meanDiffIR.sum = 0;

    lpbFilterIR.result = 0;
    lpbFilterIR.values[0] = 0;
    lpbFilterIR.values[1] = 0;

    G_u8CurrentPulseDetectorState = PULSE_IDLE;
    G_f32ValuesBPM[0] = 0;
    G_f32ValuesBPMSum = 0;
    G_u8ValuesBPMCount = 0;
    G_u8BPMIndex = 0;
    G_u32LastBeatThreshold = 0;
}
/* ********************************************************************* */
/* ********************* Read Data From Fifo ************************ */
/* ********************************************************************* */
FIFO_SAMPLE HR_OXIMETER_ReadFIFO()
{
    FIFO_SAMPLE L_sample;
    u32 L_u32RedLedSample = 0;
    u32 L_u32IRLedSample = 0;
    u8 L_u8TempBuff[6];
    HR_OXIMETER_voidGetRegContentMultiple(SLAVE_ADDRESS, FIFO_DATA_address, 6, L_u8TempBuff);
    /* IR LED */
    L_u32IRLedSample = ((u32)(L_u8TempBuff[0])) << 16;
    L_u32IRLedSample |= ((u32)L_u8TempBuff[1]) << 8;
    L_u32IRLedSample |= ((u32)L_u8TempBuff[2]) << 0;
    L_u32IRLedSample &= MSB_MASK; // MASK From Bit 18-31
    /* RED LED*/
    L_u32RedLedSample = ((u32)(L_u8TempBuff[3])) << 16;
    L_u32RedLedSample |= ((u32)L_u8TempBuff[4]) << 8;
    L_u32RedLedSample |= ((u32)L_u8TempBuff[5]) << 0;
    L_u32RedLedSample &= MSB_MASK; // MASK From Bit 18-31

    L_sample.rawIR = L_u32IRLedSample;
    L_sample.rawRED = L_u32RedLedSample;
    /* Set RD PTR to 0x00 */
    // HR_OXIMETER_vWrtRegContent(SLAVE_ADDRESS, FIFO_RD_PTR_address, 0x00);
    return L_sample;
}
/* ********************************************************************* */
/* ********************* Collect Group Sample *********************** */
/* ********************************************************************* */
void HR_OXIMETER_vCollectGroupOfSamples()
{
    FIFO_SAMPLE L_sample = HR_OXIMETER_ReadFIFO();
    display_data_Collected(L_sample.rawIR, L_sample.rawRED);
}
/* ********************************************************************* */
/* ************************** Calculate Heart Rate ********************* */
/* ********************************************************************* */
void HR_OXIMETER_vCalculateHeartRateAndOxygen()
{
    u8 L_u8PulseDetected = FALSE;
    FIFO_SAMPLE L_sample = HR_OXIMETER_ReadFIFO();
    // display_data_Collected((u32)L_sample.rawIR, (u32)L_sample.rawRED);
    dcFilterIR = HR_OXIMETER_DCRemoval((f32)L_sample.rawIR, dcFilterIR.w, ALPHA);
    dcFilterRed = HR_OXIMETER_DCRemoval((f32)L_sample.rawRED, dcFilterRed.w, ALPHA);
    // display_data_Collected((u32)dcFilterIR.result, (u32)dcFilterRed.result);
    f32 L_f32meanDiffResIr = HR_OXIMETER_f32MeanDiff(dcFilterIR.result, &meanDiffIR);
    // display_data_Collected((u32)L_f32meanDiffResIr, 0);
    HR_OXIMETER_vLowPassButterworthFilter(L_f32meanDiffResIr, &lpbFilterIR);
    display_data_Collected((u32)lpbFilterIR.result, 0);
    G_f32IrAcValueSqSum += dcFilterIR.result * dcFilterIR.result;
    G_f32RedAcValueSqSum += dcFilterRed.result * dcFilterRed.result;
    G_u16SamplesRecorded++;
    // display_data_Collected((u32)G_f32IrAcValueSqSum, (u32)G_f32RedAcValueSqSum);

    if (HR_OXIMETER_u8CheckBeat(lpbFilterIR.result) == TRUE && G_u16SamplesRecorded > 0)
    {
        /* code */
        L_u8PulseDetected = TRUE;

        G_u16PulseDetected++;
        // f32 L_f32RedRatio = sqrt(G_f32RedAcValueSqSum / G_u16SamplesRecorded);
        // f32 L_f32IRRatio = sqrt(G_f32IrAcValueSqSum / G_u16SamplesRecorded);
        // f32 L_f32IRComponent = log(L_f32IRRatio);
        // f32 L_f32EDComponent = log(L_f32RedRatio);
        // f32 L_f32RatioRMS = L_f32EDComponent / L_f32IRComponent;

        // G_f32CurrentSaO2Value = 110.0 - 18.0 * L_f32RatioRMS;
    }

    if (L_u8PulseDetected == TRUE)
    {
        /* code */
        display_HeartRate_Oxygen((u32)G_f32CurrentBPM, G_f32CurrentSaO2Value);
    }
}
/* ********************************************************************* */
/* ************************** Check Beat ********************* */
/* ********************************************************************* */
u8 HR_OXIMETER_u8CheckBeat(f32 A_f32SensorValue)
{
    static f32 L_f32PrevSensorValue = 0;
    static u8 L_u8ValuesWentDown = 0;
    static u32 L_u32CurrentBeat = 0;
    static u32 L_u32LastBeat = 0;
    if (A_f32SensorValue > PULSE_MAX_THRESHOLD)
    {
        G_u8CurrentPulseDetectorState = PULSE_IDLE;
        L_f32PrevSensorValue = 0;
        L_u32LastBeat = 0;
        L_u32CurrentBeat = 0;
        L_u8ValuesWentDown = 0;
        G_u32LastBeatThreshold = 0;
        return FALSE;
    }

    switch (G_u8CurrentPulseDetectorState)
    {
    case PULSE_IDLE:
        if (A_f32SensorValue >= PULSE_MIN_THRESHOLD)
        {
            G_u8CurrentPulseDetectorState = PULSE_TRACE_UP;
            L_u8ValuesWentDown = 0;
        }
        break;
    case PULSE_TRACE_UP:
        if (A_f32SensorValue > L_f32PrevSensorValue)
        {
            L_u32CurrentBeat = G_u32Millis * TIME_CONSTANT; // This Variable has the counts of the time passed since the micro is on
            G_u32LastBeatThreshold = A_f32SensorValue;
        }
        else
        {
            u32 L_u32BeatDuration = L_u32CurrentBeat - L_u32LastBeat;
            L_u32LastBeat = L_u32CurrentBeat;
            f32 L_f32RawBPM = 0;
            if (L_u32BeatDuration > 0)
            {
                L_f32RawBPM = 60000.0 / (f32)L_u32BeatDuration;
            }

            G_f32ValuesBPM[G_u8BPMIndex] = L_f32RawBPM;
            G_f32ValuesBPMSum = 0;

            for (u32 i = 0; i < PULSE_BPM_SAMPLE_SIZE; i++)
            {
                G_f32ValuesBPMSum += G_f32ValuesBPM[i];
            }

            G_u8BPMIndex++;
            G_u8BPMIndex = G_u8BPMIndex % PULSE_BPM_SAMPLE_SIZE;

            if (G_u8ValuesBPMCount < PULSE_BPM_SAMPLE_SIZE)
                G_u8ValuesBPMCount++;

            G_f32CurrentBPM = G_f32ValuesBPMSum / G_u8ValuesBPMCount;
            G_u8CurrentPulseDetectorState = PULSE_TRACE_DOWN;
            return TRUE;
        }
        break;
    case PULSE_TRACE_DOWN:
        if (A_f32SensorValue < L_f32PrevSensorValue)
        {
            L_u8ValuesWentDown++;
        }
        if (A_f32SensorValue < PULSE_MIN_THRESHOLD)
        {
            G_u8CurrentPulseDetectorState = PULSE_IDLE;
        }
        break;
    }
    L_f32PrevSensorValue = A_f32SensorValue;
    return FALSE;
}
/* ********************************************************************* */
/* ************************** DC Removal Filter ************************ */
/* ********************************************************************* */
DC_Filter HR_OXIMETER_DCRemoval(f32 A_FuncX, f32 A_PrevW, f32 alpha)
{
    // IIR Filter
    DC_Filter filtered;
    filtered.w = A_FuncX + (alpha * A_PrevW);
    filtered.result = filtered.w - A_PrevW;
    return filtered;
}
/* ********************************************************************* */
/* ************************** Mean Median Filter  ************************ */
/* ********************************************************************* */
f32 HR_OXIMETER_f32MeanDiff(f32 A_f32Input, MEANDiff_Filter *A_FilterValues)
{
    f32 avg = 0;

    A_FilterValues->sum -= A_FilterValues->values[A_FilterValues->index];
    A_FilterValues->values[A_FilterValues->index] = A_f32Input;
    A_FilterValues->sum += A_FilterValues->values[A_FilterValues->index];

    A_FilterValues->index++;
    A_FilterValues->index = A_FilterValues->index % MEAN_FILTER_SIZE;

    if (A_FilterValues->count < MEAN_FILTER_SIZE)
        A_FilterValues->count++;

    avg = A_FilterValues->sum / A_FilterValues->count;
    return avg - A_f32Input;
}
/* ********************************************************************* */
/* ************************** Butterworth filter  ************************ */
/* ********************************************************************* */
void HR_OXIMETER_vLowPassButterworthFilter(f32 A_f32Input, Butterworth_Filter *A_filterResult)
{
    A_filterResult->values[0] = A_filterResult->values[1];

    // Fs = 100Hz and Fc = 10Hz
    A_filterResult->values[1] = (2.452372752527856026e-1 * A_f32Input) + (0.50952544949442879485 * A_filterResult->values[0]);

    // Fs = 100Hz and Fc = 4Hz
    // A_filterResult->values[1] = (1.367287359973195227e-1 * A_f32Input) + (0.72654252800536101020 * A_filterResult->values[0]); //valuesery precise butterworth filter

    A_filterResult->result = A_filterResult->values[0] + A_filterResult->values[1];
}
/* ********************************************************************* */
/* *********************** Read Multiple Bytes ************************* */
/* ********************************************************************* */
static void HR_OXIMETER_voidGetRegContentMultiple(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8NofBytes, u8 *A_uBuffptr)
{
    u8 L_u8Stauts;
    TWI_vSendStartCondition(); // send start condition
    DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_LOW);
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* Check the ack from sensor*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    };

    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    };

    TWI_vSendStartCondition();                        // Sned Repeated Start
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 1); // send slave address with Read
    /*while (L_u8Stauts != TWI_STATUS_MT_SLA_R_ACK)
    {
    };*/
    for (u32 k = 0; k < (A_u8NofBytes - 1); k++)
    {
        A_uBuffptr[k] = TWI_u8MasterReadDataByteWith_ACK();
    }
    A_uBuffptr[A_u8NofBytes - 1] = TWI_u8MasterReadDataByteWith_NACK();
    TWI_vSendStopCondition();
}
/* ********************************************************************* */
/* ************************** Read One Byte **************************** */
/* ********************************************************************* */
static u8 HR_OXIMETER_u8GetRegContentOnce(u8 A_u8SlaveAdd, u8 A_u8Reg)
{
    u8 L_u8Stauts;
    u8 L_u8RegContent;
    TWI_vSendStartCondition();                        // send start condition
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* Check the ack from sensor*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    };
    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    };

    TWI_vSendStartCondition();                        // Sned Repeated Start
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 1); // send slave address with Read
    /*while (L_u8Stauts != TWI_STATUS_MT_SLA_R_ACK)
    {
    };*/

    L_u8RegContent = TWI_u8MasterReadDataByteWith_NACK();
    TWI_vSendStopCondition();
    return L_u8RegContent;
}
/* ********************************************************************* */
/* ************************** Write On Register ************************ */
/* ********************************************************************* */
static void HR_OXIMETER_vWrtRegContent(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8RegContent)
{
    u8 L_u8Stauts;
    TWI_vSendStartCondition();                        // send start condition
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* Check the ack from sensor*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    };

    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    }
    /* put data in the reg */
    TWI_vMasterWriteDataByte(A_u8RegContent);
    L_u8Stauts = TWI_u8MasterGetStatus();
    while (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    }
    TWI_vSendStopCondition();
}
void HR_OXIMETER_vGetPartINFO(u8 *A_u8RevID, u8 *A_u8PartID)
{
    *A_u8RevID = HR_OXIMETER_u8GetRegContentOnce(SLAVE_ADDRESS, REVISION_ID_address);
    *A_u8PartID = HR_OXIMETER_u8GetRegContentOnce(SLAVE_ADDRESS, PART_ID_address);
}
/* ********************************************************************* */
/* *************** Counts Millis Since The Micro is On ***************** */
/* ********************************************************************* */
void HR_OXIMETER_vCountsMillis()
{
    G_u32Millis++;
}

/* ----------------------------------------------- */
/* Delete all the comming after */
/* ----------------------------------------------- */
void display_data_Collected(u32 A_u32IRReading, u32 A_u32RedReading)
{
    sendCharTOSw('S');
    sendCharTOSw('N');
    send32BitDatatoDebugger(A_u32IRReading);
    send32BitDatatoDebugger(A_u32RedReading);
    send32BitDatatoDebugger(G_u32Millis);
    // sendCharTOSw('E');
}
void display_HeartRate_Oxygen(u32 A_u32HeartRate, u32 A_u32Oxygen)
{
    sendCharTOSw('R');
    sendCharTOSw('N');
    send32BitDatatoDebugger(A_u32HeartRate);
    send32BitDatatoDebugger(A_u32Oxygen);
    send32BitDatatoDebugger(G_u32Millis);
}
void toggle_led()
{
    DIO_vSetPinDir(PORTC_ID, PIN2_ID, DIR_OUTPUT);
    _delay_ms(200);
    DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_HIGH);
    _delay_ms(200);
    DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_LOW);
}
void sendStringToDebugSw(u8 *string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        UART_vSendData(string[i]);
    }
    UART_vSendData('+');
    UART_vSendData('-');
}
void send32BitDatatoDebugger(u32 data)
{
    /* Sends Low Byte First */
    sendToDebugSw((u8)(data & 0x000000FF));
    sendToDebugSw((u8)((data & 0x0000FF00) >> 8));
    sendToDebugSw((u8)((data & 0x00FF0000) >> 16));
    sendToDebugSw((u8)((data & 0xFF000000) >> 24));
}
void sendToDebugSw(u8 data)
{
    u8 L_u08FirstChar = data & 0x0F;
    u8 L_u08SecondChar = (data & 0xF0) >> 4;
    switch (L_u08FirstChar)
    {
    case 10:
        L_u08FirstChar = 'A';
        break;
    case 11:
        L_u08FirstChar = 'B';
        break;
    case 12:
        L_u08FirstChar = 'C';
        break;
    case 13:
        L_u08FirstChar = 'D';
        break;
    case 14:
        L_u08FirstChar = 'E';
        break;
    case 15:
        L_u08FirstChar = 'F';
        break;
    default:
        L_u08FirstChar += '0';
        break;
    }
    switch (L_u08SecondChar)
    {
    case 10:
        L_u08SecondChar = 'A';
        break;
    case 11:
        L_u08SecondChar = 'B';
        break;
    case 12:
        L_u08SecondChar = 'C';
        break;
    case 13:
        L_u08SecondChar = 'D';
        break;
    case 14:
        L_u08SecondChar = 'E';
        break;
    case 15:
        L_u08SecondChar = 'F';
        break;
    default:
        L_u08SecondChar += '0';
        break;
    }
    UART_vSendData(L_u08SecondChar);
    UART_vSendData(L_u08FirstChar);
    UART_vSendData('+');
    UART_vSendData('-');
}
void sendCharTOSw(u8 data)
{
    UART_vSendData(data);
    UART_vSendData('+');
    UART_vSendData('-');
}
