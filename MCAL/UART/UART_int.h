/*
 * UART_int.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Othman
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

void UART_vInit();
void UART_vSendData(u8 A_u8Data);
void UART_vSendDataAsync(u8 A_u8Data);
void UART_vSendString(u8 *A_u8DataStr);
u8 UART_u8GetData(void);
void UART_vGetString(u8 *A_u8Data);
void UART_u8GetDataAsync(FUNC_PTR_Iu8_OV A_Fptr);

#endif /* MCAL_UART_UART_INT_H_ */
