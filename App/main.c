/*
 * SWIDRO.c
 *
 * Created: 02/11/2022 09:23:34 PM
 * Author : TaqiEldeen
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/UART/UART_int.h"

#include "../HAL/HR_OXIMETER/HR_OXIMETER_int.h"
#include <avr/delay.h>
void TURONLED()
{

    DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_HIGH);
}
void testUART()
{
    UART_vSendData('E');
    UART_vSendData('+');
    UART_vSendData('-');
}
int main(void)
{
    DIO_vSetPinDir(PORTC_ID, PIN2_ID, DIR_OUTPUT);
    DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_LOW);

    UART_vInit();
    HR_OXIMETER_vInit();
    u32 counter = 1200;
    // You have to call this function with frequency at least 37Hz. But the closer you call it to 100Hz the better, the filter will work.

    while (counter > 0)
    {
        HR_OXIMETER_vCalculateHeartRateAndOxygen();
        counter--;
    }

    /* code */
    while (1)
    {
        // HR_OXIMETER_vHeartRate();
        // testUART();
        // _delay_ms(3000);
        // HR_OXIMETER_vCollectGroupOfSamples();
        //_delay_ms(1000);
    }
}
