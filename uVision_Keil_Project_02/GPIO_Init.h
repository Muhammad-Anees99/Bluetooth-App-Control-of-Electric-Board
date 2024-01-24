#ifndef GPIO_INIT_H
#define GPIO_INIT_H
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
unsigned volatile long j;
void GPIOF_Init(void);
void GPIOF_Init(void){

		SYSCTL->RCGCGPIO |= 0x20;   /* enable clock to GPIOF */
    GPIOF->DIR |= 0x0E;         //set PF1, PF2 and PF3 as digital output pin
    GPIOF->DEN |= 0x0E;         // CON PF1, PF2 and PF3 as digital GPIO pins
  	for(j=0; j< 3; j++);
}
#endif 
