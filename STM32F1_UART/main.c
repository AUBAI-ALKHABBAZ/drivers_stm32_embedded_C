/*
AUBA ALKHABBAZ
Stm32f103c8

The topic of this program is to:

- Simple init setup for UART
- Send a char using UART
- Recieve & send Char using UART

*/

#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"

char chat = 'C';
int un_com_2 = 0;
int main(void)
{
// Delays function	
systick_init();

	//-----------Init UART ------------///
	// Enable the Alternate Function for PINs
		RCC->APB2ENR |= 1;   
	// Enable UART2
		RCC->APB1ENR |=0x20000; // equal to 0b00100000000000000000   datasheet  page 148 -  APB1 peripheral clock enable register (RCC_APB1ENR) USART2 EN 
	// Enable the related PINs
	init_GP(PA,2,OUT50,O_AF_PP);
	init_GP(PA,3,IN,I_PP);
	init_GP(PC,13,OUT50, O_GP_PP);
	init_GP(PC,14,OUT50, O_GP_PP);
	// Setup the baude rate for 9600 bps
	USART2->BRR = 0xEA6;    // Baud rate register (USART_BRR) page 820
	// Enable Uart Transmit
	USART2->CR1 |= 8;  // Control register 1 (USART_CR1) page 821
	// Enable Uart Recive
	USART2->CR1 |= 4; // Control register 1 (USART_CR1)  page 821
	// Enable Uart
	USART2->CR1 |= 0x2000; // Control register 1 (USART_CR1)  page 821



while(1)
	{
	
		// Recieve Char
		while((USART2->SR & 0x20) == 0x00)  // Status register (USART_SR)  page 818
		{};
		chat = USART2->DR;
		// Transmit Char
		//DelayMs(100);
		while((USART2->SR & (1<<6)) == 0x80)   // Status register (USART_SR)  page 818
		{};
		USART2->DR = chat;
		if(chat == 'F')
		{
				W_GP(PC,13,0); /// Set the PIN 13 port C LOW
				W_GP(PC,14,1);
		}
		else if (chat == 'R')
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high
			W_GP(PC,14,0);
			
		}
		else {
			un_com_2 ++;
			//toggle_GP(PC,13);

		}
		
		
	}		
}
void UART_init(unsigned short usart , unsigned long BR)
{
	/// if using USART1 clock speed 72Mhz, else 36Mhz
	/// for USRT 3 -> PB10 (Tx) and PB11 (Rx)
	/// for USRT 2 -> PA2  (Tx) and PA3 (Rx)
	/// for USRT 1 -> PA9  (Tx) and PA10 (Rx)
		// Enable the Alternate Function for PINs
		RCC->APB2ENR |= 1; 
	unsigned long BRR_Cal;
	BRR_cal
	if(usart == 1){
			//-----------Init UART ------------///   
	// Enable UART1
		RCC->APB2ENR |=0x40000; // 
	// Enable the related PINs
	init_GP(PA,9,OUT50,O_AF_PP);
	init_GP(PA,10,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART1->BRR = 0xEA6;    // Baud rate register (USART_BRR) page 820
	// Enable Uart Transmit
	USART1->CR1 |= 8;  // Control register 1 (USART_CR1) page 821
	// Enable Uart Recive
	USART1->CR1 |= 4; // Control register 1 (USART_CR1)  page 821
	// Enable Uart
	USART1->CR1 |= 0x2000; // Control register 1 (USART_CR1)  page 821
	}
	else if (usart == 2){
	// Enable UART2
		RCC->APB1ENR |=0x20000; // equal to 0b00100000000000000000   datasheet  page 148 -  APB1 peripheral clock enable register (RCC_APB1ENR) USART2 EN 
	// Enable the related PINs
	init_GP(PA,2,OUT50,O_AF_PP);
	init_GP(PA,3,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART2->BRR = 0xEA6;    // Baud rate register (USART_BRR) page 820
	// Enable Uart Transmit
	USART2->CR1 |= 8;  // Control register 1 (USART_CR1) page 821
	// Enable Uart Recive
	USART2->CR1 |= 4; // Control register 1 (USART_CR1)  page 821
	// Enable Uart
	USART2->CR1 |= 0x2000; // Control register 1 (USART_CR1)  page 821
	}
	else if (usart == 3){
	// Enable UART3
		RCC->APB1ENR |=0x40000; 
	// Enable the related PINs
	init_GP(PB,10,OUT50,O_AF_PP);
	init_GP(PB,11,IN,I_PP);
	init_GP(PC,13,OUT50, O_GP_PP);
	init_GP(PC,14,OUT50, O_GP_PP);
	// Setup the baude rate for 9600 bps
	USART3->BRR = 0xEA6;    // Baud rate register (USART_BRR) page 820
	// Enable Uart Transmit
	USART3->CR1 |= 8;  // Control register 1 (USART_CR1) page 821
	// Enable Uart Recive
	USART3->CR1 |= 4; // Control register 1 (USART_CR1)  page 821
	// Enable Uart
	USART3->CR1 |= 0x2000; // Control register 1 (USART_CR1)  page 821
	}
}

