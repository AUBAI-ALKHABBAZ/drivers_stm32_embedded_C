
#include "stm32f10x.h"                  // Device header
void delay(int rep);
int main(void)
{
	RCC->APB2ENR |= 0x10; /// Or  0b10000 --> Anabling Preiph GPIOC
	GPIOC->CRH &= 0xFF0FFFFF;  /// Reset the PORT C PIN 13 and PIN 15
	GPIOC->CRH |= 0x30300000;  /// Set Port C PIN 13 and 15 as Output 
	//GPIOC->ODR  |= 0x2000;     /// Set Port C Pin 13 
	//GPIOC->ODR  |= 0b0010000000000000; // in binary mode 
	GPIOC->ODR  |= 0x10000; 
	//return 0 ;
	while(1){
	GPIOC->ODR  |= 0x2000;     /// on  Set Port C Pin 13 
	delay(10);
	GPIOC->ODR  &= ~0x2000;     /// off  Set Port C Pin 13 	
	delay(10);
	}
	
}


/// Random time delay Function
void delay(int rep)
{
	for(;rep>0;rep--)
	{
	int i;
	for(i=0; i< 100000;i++)
	{}
	}
}