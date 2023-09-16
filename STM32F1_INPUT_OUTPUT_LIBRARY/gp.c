// import head file gp_drive.h  for gp_drvie.c
#include "gp_drive.h"

//  Create a function to initial General ports
void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt){
	  volatile unsigned long * CR;
		unsigned short tPIN = pin;
		unsigned short offset = 0x00;
		// to select (port configuration register low or High) we use  the number of pins from 0 to 7 or from 8 to 15  as if condition 
		if(pin > 7)
		{
			tPIN -= 8;
			offset = 0x01;
		}
		if(port == 1)
		{
			RCC_APB2ENR |= 4; //// Enabling - PORT A APB2 peripheral clock enable register (RCC_APB2ENR)
			CR = (volatile unsigned long *) (&GPIO_A + offset);
		}
		else if(port == 2)
		{
			RCC_APB2ENR |= 8; //// Enabling PORT B  - APB2 peripheral clock enable register (RCC_APB2ENR)
			CR = (volatile unsigned long *) (&GPIO_B + offset);
		}
		else if(port == 3)
		{
			RCC_APB2ENR |= 0x10; //// Enabling PORT C - APB2 peripheral clock enable register (RCC_APB2ENR)
			CR = (volatile unsigned long *) (&GPIO_C + offset);
		}
		*CR &= ~(0xf<<(tPIN)*4); ///Reset the taget pin for Port configuration register -  Reset value: 0x4444 4444  its equal to   0xffff ffff == 0xf<<(tPIN)*4      tPIN is refer to  the number of pin inside CR 0 or 1 or 2 ... ____-CNF0[1:0] MODE0[1:0___CNF1[1:0] MODE1[1:0]____
		*CR |= ((dir <<(tPIN*4)) | (opt<<(tPIN*4+2))); //// Set up the direction and the option of the PIN
				
}
int R_GP(unsigned short port, unsigned short pin){
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(port == 1)
		{
			IDR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			IDR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
	{
		IDR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	state = ((*IDR & (1<<pin))>>pin);
	return state;
}
void W_GP(unsigned short port, unsigned short pin, unsigned short state){
		volatile unsigned long * ODR;
		unsigned long offset = 0x03;

	
	if(port == 1)
		{
			ODR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			ODR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
	{
		ODR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin)); // if the state is 1 put 1 in ODR else state is 0 put 0 in ODR
}
void toggle_GP(unsigned short port, unsigned short pin){
	if (R_GP(port,pin))
		{
			W_GP(port,pin,0);
		}
	else
		{
			W_GP(port,pin,1);
		}
}
