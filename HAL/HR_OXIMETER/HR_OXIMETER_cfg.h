/*
 * HR_OXIMETER_reg.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Ahmed Othman
 *  "THIS FOR MAX30102 Senseor (Heart Rate and Oximeter)"
 */

#ifndef HAL_HR_OXIMETER_HR_OXIMETER_CFG_H_
#define HAL_HR_OXIMETER_HR_OXIMETER_CFG_H_
#define TIME_CONSTANT 2
/* ************************************* */
/* FIFO Configuration */
/* ************************************* */
/*
    Sample Averaging OPTIONS:
    SAMPLEAVG_1
    SAMPLEAVG_2
    SAMPLEAVG_4
    SAMPLEAVG_8
    SAMPLEAVG_16
    SAMPLEAVG_32
 */
#define SAMPLEAVG_SELECTED SAMPLEAVG_8

/* ************************************* */
/* Mode Control Configuration */
/* ************************************* */
/*
    MODE Control OPTIONS:
    RED_ONLY
    RED_IR
    MULTI_RED_IR
 */

#define MODE_CONTROL_SELECTED RED_IR

/* ************************************* */
/* SpO2 Configuration */
/* ************************************* */
/*
    SPO2 ADC Range Options:
    ADCRANGE_2048
    ADCRANGE_4096
    ADCRANGE_8192
    ADCRANGE_16384
 */
#define ADCRANGE_SELECTED ADCRANGE_4096

/*
    SpO2 Sample Rate Control Options:
    SAMPLERATE_50
    SAMPLERATE_100
    SAMPLERATE_200
    SAMPLERATE_400
    SAMPLERATE_800
    SAMPLERATE_1000
    SAMPLERATE_1600
    SAMPLERATE_3200
 */
#define SAMPLERATE_SELECTED SAMPLERATE_400
/*
 * NOTE: You can't choose higher than that because it depends on PULSE Width too,
 * Check table of their relation in datasheet
 */

/*
    LED Pulse Width Control and ADC Resolution Options:
    PULSEWIDTH_69   (ADC RESOLUTION 15-BIT)
    PULSEWIDTH_118  (ADC RESOLUTION 16-BIT)
    PULSEWIDTH_215  (ADC RESOLUTION 17-BIT)
    PULSEWIDTH_411  (ADC RESOLUTION 18-BIT)
 */
#define PULSEWIDTH_SELECTED PULSEWIDTH_411

/* ************************************* */
/* LED Pulse Amplitude */
/* ************************************* */
/*
    LED Pulse Amplitude (Current) Options:
    LEDCURRENT_0_0
    LEDCURRENT_0_2
    LEDCURRENT_0_4
    LEDCURRENT_3_0
    LEDCURRENT_6_2
    LEDCURRENT_12_6
    LEDCURRENT_25_4
    LEDCURRENT_51_0
 */
#define LED1_IR_CURRENT_SELECTED LEDCURRENT_6_2
#define LED2_RED_CURRENT_SELECTED LEDCURRENT_6_2

/* *********************************************************** */
/* MULTI MODE Control register*/
/* *********************************************************** */
/*
    MULTI MODE Options:
    IR_LED
    RED_LED
 */
#define SLOT1_LED_SELECTED IR_LED
#define SLOT2_LED_SELECTED RED_LED

#endif /* HAL_HR_OXIMETER_HR_OXIMETER_CFG_H_ */
