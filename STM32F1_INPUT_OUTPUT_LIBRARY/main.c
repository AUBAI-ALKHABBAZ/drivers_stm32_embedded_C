#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
void Delays(int time);

int main(void)
{ 
	/*
	RCC_APB2ENR  |= 4; //// Enabling PORT A
	RCC_APB2ENR  |= 0x10; /// Enabling PORT C
	GPIOA->CRL &= 0xFFFFFFF0; /// Reset the Port A PIN 0
	GPIOA->CRL |= 0x8; /// Set port A pin 0 as in Input push pull
	
	GPIOC->CRH &= 0xFF0FFFFF; /// Reset the pin 13
	GPIOC->CRH |= 0x00300000; /// Set PIN 13 as output
	*/
	init_GP(PA,0,IN,I_PP); // set port A pin 0 as input 
	init_GP(PA,1,IN,I_PP); // set port A pin 1 as input 
	init_GP(PC,13,OUT50,O_GP_PP); // set port C pin 13 as output
	while(1)
	{
		if(R_GP(PA,0)==1 & R_GP(PA,1)==1) /// Checking status of PIN ! portA pin 0 and pin 1 
		{
			Delays(10); 
			toggle_GP(PC,13); /// Toggle the PIN state port c pin 13
			Delays(10);
		}
		else
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high   Pin13 is Led inside stm32
		}
	}
	
}


void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{}
	}
}
