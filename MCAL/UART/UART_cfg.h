/*
 * UART_cfg.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

/* BAUD RATE */
#define BAUD_RATE 9600
#define FCPU 8000000
#define BAUD_RATE_PRESCALE ((FCPU * 1.0 / (16 * BAUD_RATE)) - 1)

/*
    EQU:
    UBBR =  ((FCPU * 1.0 / (16 * BAUD_RATE)) - 1)
    ---------------------------------------------
    Baud RATE Options for 8MHZ
    --------------------------
    BAUD RATE |   UBBR
    2400      |   207
    4800      |   103
    9600      |   51
    14.4k     |   34
    19.2k     |   25
    28.8k     |   16
    38.4k     |   12
    57.6k     |   8
    76.8k     |   6
    115.2k    |   3
    230.4k    |   1
    0.5M      |   0
 */

#define UBBR_VALUE 51
/*
    Parity Options :

    DISABLED
    ENABLED_EVEN_PARITY
    ENABLED_ODD_PARITY
 */
#define PARITY_MODE DISABLED

/*
    Stop Bit Options:

    ONE_BIT
    TWO_BIT
 */
#define STOP_BIT_MODE ONE_BIT

/*
    Data Format Options :

    CHAR_5_BIT_UCSRC
    CHAR_6_BIT_UCSRC
    CHAR_7_BIT_UCSRC
    CHAR_8_BIT_UCSRC
    CHAR_9_BIT_UCSRC

    CHAR_5_BIT_UCSRB
    CHAR_6_BIT_UCSRB
    CHAR_7_BIT_UCSRB
    CHAR_8_BIT_UCSRB
    CHAR_9_BIT_UCSRB
 */
#define DATA_FORMAT_UCSRB CHAR_8_BIT_UCSRB
#define DATA_FORMAT_UCSRC CHAR_8_BIT_UCSRC

/* Async Sync MODE */
/*
    Optiosn:

    ASYNC
    SYNC
 */
#define ASYNC_SYNC_MODE ASYNC
#endif /* MCAL_UART_UART_CFG_H_ */
