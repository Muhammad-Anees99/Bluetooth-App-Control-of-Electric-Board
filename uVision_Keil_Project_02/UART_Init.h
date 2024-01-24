#ifndef UART_INIT_H
#define UART_INIT_H
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
void UART_init(void); // Initialize UART5 module for HC-05
char UART_Read(void); //Read data from Rx5 pin of TM4C123
void UART_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin 
void UART_Write_String(char *str); // Transmit a string to HC-05 over Tx5 pin 
unsigned volatile long j;
void UART_init(void)
{
	SYSCTL->RCGCUART |= 0x20;  /* enable clock to UART5 */
    SYSCTL->RCGCGPIO |= 0x10;  /* enable clock to PORTE for PE4/Rx and RE5/Tx */
    for(j=0; j< 3; j++);
    /* UART0 initialization */
    UART5->CTL = 0;         /* UART5 module disbable */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          //select system clock/
    UART5->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x30;      /* set PE4 and PE5 as digital */
    GPIOE->AFSEL = 0x30;    /* Use PE4,PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analg function*/
    GPIOE->PCTL = 0x00110000;     /* configure PE4 and PE5 for UART */
}
char UART_Read(void)
{
    char data;
    while ((UART5->FR & (1 << 4)) != 0); // wait until Rx buffer is not full
    data = (char)(UART5->DR & 0xFF);    // mask out unnecessary bits
    return data;
}

void UART_Write(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

void UART_Write_String(char *str)
{
  while(*str)
	{
		UART_Write(*(str++));
	}
}


#endif 
