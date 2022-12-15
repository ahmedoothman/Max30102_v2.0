/*
 * HR_OXIMETER_int.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Dell
 */

#ifndef HAL_HR_OXIMETER_HR_OXIMETER_INT_H_
#define HAL_HR_OXIMETER_HR_OXIMETER_INT_H_
/* ************************************* */
/* NEEDED PARMETER*/
/* ************************************* */
#define ALPHA 0.95
#define NUMBER_OF_SAMPLES 32
#define MEAN_FILTER_SIZE 15

/* Pulse Detection Parameters */
#define PULSE_MIN_THRESHOLD 200 // 300 is good for finger , but wrist you need like 20, and there is too much noise
#define PULSE_MAX_THRESHOLD 2000
#define PULSE_GO_DOWN_THRESHOLD 1
#define PULSE_BPM_SAMPLE_SIZE 10
/* *********************************************************** */
/* Needed DataTypes*/
/* *********************************************************** */
typedef struct
{
    u32 rawIR;
    u32 rawRED;
} FIFO_SAMPLE;

typedef struct
{
    f32 w;
    f32 result;
} DC_Filter;
typedef struct
{
    f32 values[MEAN_FILTER_SIZE];
    u8 index;
    f32 sum;
    u8 count
} MEANDiff_Filter;
typedef struct
{
    f32 values[2];
    f32 result;
} Butterworth_Filter;

typedef enum PulseStateMachine
{
    PULSE_IDLE,
    PULSE_TRACE_UP,
    PULSE_TRACE_DOWN
} PulseStateMachine;
/* *********************************************************** */
/* Init*/
/* *********************************************************** */
void HR_OXIMETER_vInit();
/* *********************************************************** */
/* Read FiFo (only get one sample) */
/* *********************************************************** */
FIFO_SAMPLE HR_OXIMETER_ReadFIFO();

/* *********************************************************** */
/* Functions to collect group of samples */
/* *********************************************************** */
void HR_OXIMETER_vCollectGroupOfSamples();

/* *********************************************************** */
/* Get HeartRate and Oxygen */
/* *********************************************************** */
void HR_OXIMETER_vCalculateHeartRateAndOxygen();
/* *********************************************************** */
/* Check Beat */
/* *********************************************************** */
u8 HR_OXIMETER_u8CheckBeat(f32 A_f32SensorValue);
/* *********************************************************** */
/* I2C Functions */
/* *********************************************************** */
static u8 HR_OXIMETER_u8GetRegContentOnce(u8 A_u8SlaveAdd, u8 A_u8Reg);
static void HR_OXIMETER_voidGetRegContentMultiple(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8NofBytes, u8 *A_uBuffptr);
static void HR_OXIMETER_vWrtRegContent(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8RegContent);

/* *********************************************************** */
/* Filters */
/* *********************************************************** */
DC_Filter HR_OXIMETER_DCRemoval(f32 A_FuncX, f32 A_PrevW, f32 alpha);
f32 HR_OXIMETER_f32MeanDiff(f32 A_f32Input, MEANDiff_Filter *A_FilterValues);
void HR_OXIMETER_vLowPassButterworthFilter(f32 A_f32Input, Butterworth_Filter *A_filterResult);
/* *********************************************************** */
/* Counts Millis Since The Micro is On */
/* *********************************************************** */
void HR_OXIMETER_vCountsMillis();

/* *********************************************************** */
/* Get Sensor info */
/* *********************************************************** */
void HR_OXIMETER_vGetPartINFO(u8 *A_u8RevID, u8 *A_u8PartID);

/* Functions i will remove later */
void display_red_ir(u32 ir, u32 red, u8 samples);
void toggle_led();
void display_data_Collected(u32 A_u32IRReading, u32 A_u32RedReading);
void display_HeartRate_Oxygen(u32 A_u32HeartRate, u32 A_u32Oxygen);
void sendToDebugSw(u8 data);
void sendStringToDebugSw(u8 *string);
void send32BitDatatoDebugger(u32 data);
void sendCharTOSw(u8 data);
#endif /* HAL_HR_OXIMETER_HR_OXIMETER_INT_H_ */
