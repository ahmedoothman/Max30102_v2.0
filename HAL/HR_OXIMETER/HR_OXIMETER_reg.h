/*
 * HR_OXIMETER_reg.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Ahmed Othman
 *  "THIS FOR MAX30102 Senseor (Heart Rate and Oximeter)"
 */

#ifndef HAL_HR_OXIMETER_HR_OXIMETER_REG_H_
#define HAL_HR_OXIMETER_HR_OXIMETER_REG_H_

/* ************************************ */
/* Interrupt Status 1 (0x00) */
/* ************************************ */
#define INT_STATUS1_Address 0x00
#define A_FULL 7  /* FIFO Almost Full Flag */
#define PPG_RDY 6 /* New FIFO Data Ready */
#define ALC_OVF 5 /* Ambient Light Cancellation Overflow */
#define PWR_RDY 0 /* Power Ready Flag */

/* ************************************ */
/* Interrupt Status 2 (0x01) */
/* ************************************ */
#define INT_STATUS2_Address 0x01
#define DIE_TEMP_RDY 1 /* Internal Temperature Ready Flag */

/* ************************************ */
/* Interrupt Enable 1 (0x02) */
/* ************************************ */
#define INT_ENABLE1_Address 0x02
#define A_FULL_EN 7  /* FIFO Almost Full Flag Enable */
#define PPG_RDY_EN 6 /* New FIFO Data Ready Enable */
#define ALC_OVF_EN 5 /* Ambient Light Cancellation Overflow Enable */

/* ************************************ */
/* Interrupt Enable 2 (0x03) */
/* ************************************ */
#define INT_ENABLE1_Address 0x03
#define DIE_TEMP_RDY_EN 1 /* Internal Temperature Ready Flag Enable */

/* ************************************ */
/* FIFO WR PTR (0x04)*/
/* ************************************ */
#define FIFO_WR_PTR_address 0x04

/* ************************************ */
/* OVF COUNTER (0x05)*/
/* ************************************ */
#define OVF_COUNTER_address 0x05

/* ************************************ */
/* FIFO RD PTR (0x06)*/
/* ************************************ */
#define FIFO_RD_PTR_address 0x06

/* ************************************ */
/* FIFO Data Register (0x07)*/
/* ************************************ */
#define FIFO_DATA_address 0x07

/* ************************************ */
/* FIFO Configuration (0x08)*/
/* ************************************ */
#define FIFO_Configuration_address 0x08
#define SMP_AVE_START_BIT 5     /* Sample Averaging (Bits 7:5) */
#define FIFO_ROLL_OVER_EN 4     /* FIFO Rolls on Full */
#define FIFO_A_FULL_START_BIT 0 /* FIFO Almost Full Value (Bits 3:0) */

/* ************************************ */
/* MODE Configuration (0x09)*/
/* ************************************ */
#define MODE_Configuration_address 0x09
#define SHDN 7           /* Shutdown Control */
#define RESET 6          /* Reset Control */
#define MODE_START_BIT 0 /* Mode Control (Bits 2:0) */

/* ************************************ */
/* SpO2 Configuration (0x0A)*/
/* ************************************ */
#define SpO2_Configuration_address 0x0A
#define SPO2_ADC_RGE_START_BIT 5 /* SpO2 ADC Range Control (Bits 6:5) */
#define SPO2_SR_START_BIT 2      /* SpO2 Sample Rate Control (Bits 4:2) */
#define LED_PW_START_BIT 0       /* LED Pulse Width Control and ADC Resolution (Bits 1:0) */

/* ************************************ */
/* LED Pulse Amplitude (0x0C - 0x0D)*/
/* ************************************ */
#define LED1_PA_address 0x0C
#define LED2_PA_address 0x0D

/* ************************************ */
/* LED Pulse Amplitude (0x0C - 0x0D)*/
/* ************************************ */
#define MULTI_LED_REG_S1_S2_address 0x11
#define SLOT_1_START_BIT 0
#define SLOT_2_START_BIT 4
#define MULTI_LED_REG_S3_S4_address 0x12
#define SLOT_3_START_BIT 0
#define SLOT_4_START_BIT 4

/* ************************************ */
/* Rev ID*/
/* ************************************ */
#define REVISION_ID_address 0xFE
/* ************************************ */
/* Part ID*/
/* ************************************ */
#define PART_ID_address 0xFF

/* ******
 *   NOTE: There is still 1 register :
 *   - Temperature Data
 ***** */

#endif /* HAL_HR_OXIMETER_HR_OXIMETER_REG_H_ */
