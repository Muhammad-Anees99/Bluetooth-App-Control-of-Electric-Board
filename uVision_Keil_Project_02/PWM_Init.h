#ifndef PWM_INIT_H
#define PWM_INIT_H
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
unsigned volatile long j;
void PB6_as_M0PWM0_Init(void);
void PWM_Module0_Channel0_Init(void);

void PB6_as_M0PWM0_Init(void){
	// Step 1: Clock enable on PortF
	SYSCTL->RCGCGPIO |= 0x02;		// 0b 0010 0000 
	for (j =0; j < 3 ; j++)			// at least 3 clock cyles
	
	// Step 2: APB is selected for PortF by selecting
	// 0x40025000 as Base Address in DATA section
	
	// Step 3: Enable alternate functionality on PortF
	GPIOB->AFSEL |= 0x40;				// 0b 0000 0100
	
	// Step 4: Enable digital pin functionaliy on PortF pin 2
	GPIOB->DEN |= 0x40; // Digital enable for PF2
	
	// Step 5: Set PortF pin 2 as an output pin
	GPIOB->DIR |= 0x40; // PF2 as Output pin
	
	// Step 6: Configure PortF pin 2 as M1PWM6 pin (Table 10-2 of Datasheet, page # 651)
	GPIOB->PCTL &= 0xF0FFFFFF;		// clear the bit fields
	GPIOB->PCTL |= 0x04000000;
}

void PWM_Module0_Channel0_Init(void){
	
	// Step 1: Clock Gating Control of PWM Module 1
	SYSCTL->RCGCPWM |= 0x01;		// b 0000 0010
	for (j =0; j < 3 ; j++)			// at least 3 clock cyles
	SYSCTL->RCC	&= (~(1<<20));		// disable clock signal divisor for PWM
	
	// Step 2: For PWM Channel configurations
	// we need check which PWM block our PWM Pin blongs to. For our case PF2
	// is M1PWM6 which is a part of PWM block 3 
	// Read any register description for identifying the block, e.g., CTL
	
	// Step 3: Disable Generator 3 before performing configurations
	// Step 4: Select Counter 3 Count-down mode
	PWM0->_0_CTL = 0x00;
	
	// Step 5: Set Load value for 10 kHz
	// (16 MHz / 10 kHz = 1600)
	PWM0->_0_LOAD = 320000;
	
	// Step 6: Set Compare Register Value to set 50% duty cycle
	// 50% of Load value = 1600 x 50% = 1600 x 0.5 = 800
	PWM0->_0_CMPA = 1590;
	
	// Step 7: Perform Generating Control Register configuration
	// PWM signal HIGH when counter relaoded and LOW when matches CMPA Value
	PWM0->_0_GENA |= 0x8C;
	
	// Step 8: Enable generator 3 counter
	PWM0->_0_CTL |= 0x01;
	
	// Step 9: Enalbe PWM Module 1 Channel 6 Output
	PWM0->ENABLE |= 0x01;
}


#endif 
