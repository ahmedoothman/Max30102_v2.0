/*
 * UART_prg.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Dell
 */

#include "../../lib/std_types.h"
#include "../../lib/bit_math.h"

#include "../DIO/DIO_int.h"
#include "../GIE/GIE_int.h"

#include "UART_reg.h"
#include "UART_pri.h"
#include "UART_cfg.h"
#include "UART_int.h"

#include <avr/delay.h>

FUNC_PTR_Iu8_OV G_PTR_FUNC_RX;
static u8 G_u8DataSend;
void UART_vInit()
{
    /* Select The Baud Rate */
    UBRRL = UBBR_VALUE;
    UBRRH = UBBR_VALUE >> 8;

    /* Enable Writing to UCSRC By Setting URSEL IN Each write in the Register*/
    /* Disable Parity */
    UCSRC = (UCSRC & PARITY_MASK) | PARITY_MODE << 4 | (1 << URSEL);
    /* Select 1 Stop Bit */
    UCSRC = (UCSRC & STOP_BIT_MASK) | STOP_BIT_MODE << 3 | (1 << URSEL);
    /* Set Data Format 8 bit */
    UCSRC = (UCSRC & FORMAT_MODE_MASK_UCSRC) | DATA_FORMAT_UCSRC << 1 | (1 << URSEL);
    UCSRB = (UCSRB & FORMAT_MODE_MASK_UCSRB) | DATA_FORMAT_UCSRB << 2;
    /* Set Async Sync Mode */
    // UCSRC = (UCSRC & ASYNC_SYNC_MASK) | ASYNC_SYNC_MODE << 6 | (1 << URSEL);
    /* Set RX Pin as input PORTD PIN0*/
    DIO_vSetPinDir(PORTD_ID, PIN0_ID, DIR_INPUT);
    /* Set TX Pin as Output PORTD PIN1*/
    DIO_vSetPinDir(PORTD_ID, PIN1_ID, DIR_OUTPUT);

    /* Enable Transmitter & Receiver*/
    SET_BIT(UCSRB, RXEN);
    SET_BIT(UCSRB, TXEN);

    /* at the same clk cycle */
    // UCSRB |= (1 << RXEN) | (1 << TXEN);
    // UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}
void UART_vSendData(u8 A_u8Data)
{
    /* Wait For Empty Transmit Buffer */
    while (!(UCSRA & (1 << UDRE)))
    {
        // wait
    }
    UDR = A_u8Data;
}
void UART_vSendDataAsync(u8 A_u8Data)
{
    /* GLobal Interrupt Enable */
    GIE_vEnableGlobaLInt();
    /* Enable UDR Empty interrupt */
    SET_BIT(UCSRB, UDRIE);
    /* Enable TX Transmit interrupt */
    // SET_BIT(UCSRB, TXCIE);
    /* Set The Data to global variables */
    G_u8DataSend = A_u8Data;
}
void UART_vSendString(u8 *A_u8DataStr)
{
    /* Send each char of string till the NULL */
    for (u32 i = 0; A_u8DataStr[i] != 0; i++)
    {
        UART_vSendData(A_u8DataStr[i]);
    }
}

u8 UART_u8GetData(void)
{
    /* Wait untill receive flag is finished */
    while ((UCSRA & (1 << RXC)) == 0)
    {
        // wait
    }
    return UDR;
}
void UART_vGetString(u8 *A_u8Data)
{
    u8 L_u8CharCount = 0;
    A_u8Data[L_u8CharCount] = UART_u8GetData();
    while (A_u8Data[L_u8CharCount] != ADR_NULL)
    {
        L_u8CharCount++;
        A_u8Data[L_u8CharCount] = UART_u8GetData();
    }
    A_u8Data[L_u8CharCount] = '\0';
}
void UART_u8GetDataAsync(FUNC_PTR_Iu8_OV A_Fptr)
{
    /* GLobal Interrupt Enable */
    GIE_vEnableGlobaLInt();
    /* Enable RX interrupt */
    SET_BIT(UCSRB, RXCIE);
    /* Register CallBack Function */
    G_PTR_FUNC_RX = A_Fptr;
}
/* RX Complete Interrupt */
void __vector_13(void)
{
    G_PTR_FUNC_RX(UDR);
}
/* UDRE Data Register Empty */
void __vector_14(void)
{
    UDR = G_u8DataSend;
    // CLR_BIT(UCSRB, UDRIE);
}
/* TX Complete Interrupt */
void __vector_15(void)
{
}
