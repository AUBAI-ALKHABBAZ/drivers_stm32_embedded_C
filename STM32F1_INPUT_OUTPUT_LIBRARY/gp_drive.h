#define RCC_APB2ENR     (*((volatile unsigned long *) 0x40021018))

#define GPIO_A    		  (*((volatile unsigned long *) 0x40010800))
#define GPIO_B          (*((volatile unsigned long *) 0x40010C00))
#define GPIO_C          (*((volatile unsigned long *) 0x40011000))
	
///init_GP(port,..,..,..)-  List of Ports
#define PA 1
#define PB 2
#define PC 3

///init_GP(..,..,dir,..)-  Directions    MODEy[1:0] Port configuration register low (GPIOx_CRL) (x=A..G)
#define IN 0  		// Port configuration register 00: Input mode (reset state)
#define OUT10 1 	// Port configuration register 01: Output mode, max speed 10 MHz
#define OUT2  2		// Port configuration register 10: Output mode, max speed 2 MHz
#define OUT50 3		// Port configuration register 11: Output mode, max speed 50 MHz.

///init_GP(..,..,..,opt)- Direction options for input   CNFy[1:0] Port configuration register low (GPIOx_CRL) (x=A..G)  - In input mode (MODE[1:0]=00)
#define I_AN 0 // 00: Analog mode
#define I_F  1 // 01: Floating input (reset state)
#define I_PP 2 // 10: Input with pull-up / pull-down

///init_GP(..,..,..,opt)-  Direction options for output   -  CNFy[1:0] Port configuration register low (GPIOx_CRL) (x=A..G)  - In output mode  (MODE[1:0] > 00)
#define O_GP_PP 0 // 00: General purpose output push-pull
#define O_GP_OD 1 // 01: General purpose output Open-drain
#define O_AF_PP 2 // 10: Alternate function output Push-pull
#define O_AF_OD 3 // 11: Alternate function output Open-drain

/// State definition
#define LOW  0
#define HIGH 1


// define fucntions 
void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt);  //  Create a function to initial General ports
int R_GP(unsigned short port, unsigned short pin); //  Create a function to Read  from General ports
void W_GP(unsigned short port, unsigned short pin,unsigned short status); //  Create a function to Write  on General ports
void toggle_GP(unsigned short port, unsigned short pin); //  Create a function to toggle  the output ports
