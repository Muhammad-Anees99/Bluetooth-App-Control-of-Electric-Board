#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
#include "PWM_Init.h"
#include "UART_Init.h"
#include "PLL_Init.h"
#include "GPIO_Init.h"
#include "set_timer.h"
#define Forward  16800;
#define Backward 51200;  
char ch[3];

int n;
int main(void)
{		
    PLL_Init();
    PB6_as_M0PWM0_Init();
    PWM_Module0_Channel0_Init();
		UART_init();
		GPIOF_Init();
		
    while(1)
    {	
        char check = UART_Read();          /* get a character from UART5 */
				if( check=='A'){
					GPIOF->DATA |=(1<<3);
					GPIOF->DATA &=~(1<<1);
					UART_Write_String("Button Turned OFF");
					
					//PWM0->_0_CMPA = 278000 + ((314000 - 278000) * 180) / 180;
				 // PWM0->_0_CMPA =  28000;//278000 + (314000 - 278000) * 90 / 180;orig
					//(desired_pulse_width_in_μs / 20) * PWM_resolution
					PWM0->_0_CMPA=Forward;//0 to 90
				}
				else if( check=='B'){
					//For 10second delay=t=17550
					//Delay_MicroSecond(1755); //almost 10 seconds delay
					GPIOF->DATA &=~(1<<3);
					GPIOF->DATA |=(1<<1);
					UART_Write_String("Button Turned ON\n");
					// Set PWM to return to 0 degrees
					//PWM0->_0_CMPA = 19000;original less than 45 degree
					PWM0->_0_CMPA= Backward ;//90 to 0
				}	
				else if( check=='C'){
					
					ch [0]=  UART_Read(); 
					ch [1]= '\0';
					PWM0->_0_CMPA= Backward ;
					
					int n = atoi(&ch);
					//extractInteger(ch);
					//calculate_time(ch);
					//For 10second delay=t=17550
					Delay_MicroSecond(n*10*1755); //almost 10 seconds delay
					GPIOF->DATA &=~(1<<3);
					GPIOF->DATA |=(1<<1);
					UART_Write_String("Button Turned OFF\n");
					// Set PWM to return to 0 degrees
					//PWM0->_0_CMPA = 19000;original less than 45 degree
					//90 to 0
					PWM0->_0_CMPA=Forward;
				}
    }
}
