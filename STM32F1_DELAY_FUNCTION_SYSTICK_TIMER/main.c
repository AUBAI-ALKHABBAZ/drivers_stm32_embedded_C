/* The topic of the video is setup an accurate delay function 
using the systick timer
*/

#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
void Delays(int time);
void DelayMs(unsigned long t);
void DelayMillis(void);
void systick_init(void);
int signal = 0;
int main(void)
{
	systick_init();
	init_GP(PA,0,IN,I_PP);
	init_GP(PC,13,OUT50, O_GP_PP);
	init_GP(PA,12,OUT50,O_GP_PP);
	
	__disable_irq();
	AFIO->EXTICR[0] = 0x00; /// Activating the interrupts for the Port A PIN 0
	EXTI->IMR |= 1; /// Enable the interrupt for EXTI0
	EXTI->RTSR |= 1; /// Generate a system interrupt at the rising edge
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable the global interrupt function
	__enable_irq();
	
	
	while(1)
	{
		W_GP(PA,12,signal);
		if(signal) /// Checking status of PIN ! portA 
		{
			DelayMs(1000);
			toggle_GP(PC,13); /// Toggle the PIN state
			DelayMs(1000);
		}
		else
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high
		}

	}
	
}

// Random generated delay
void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{}
	}
}

void EXTI0_IRQHandler() // Interrupt Handler function for Port A pin 0
{
	EXTI->PR |=1;
	if(signal)
	{signal = 0;}
	else
	{signal = 1;}
}

// initial systick timer  
//System Tick Timer Dialog The System Tick Timer Dialog displays and configures the system tick time features of this Cortex core peripheral.
void systick_init(void)
{
	SysTick->CTRL = 0; // we should put an initial systick value  CTRL = 0 
	SysTick->LOAD = 0x00FFFFFF; // max value
	SysTick->VAL = 0; // current value
	SysTick->CTRL |= 5;
}

void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0); // when  finshed the fla CRTL ==1 
}

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}
