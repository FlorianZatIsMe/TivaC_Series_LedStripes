#include <stdio.h>  // Diamond braces for sys lib: Standard I/O
#include "uart.h"   // Quotes for user lib: UART lib
#include "GPIO.h"
#include "I2C.h"

//------------I2C0------------
// 
// 
// Input: none
// Output: none
void I2C0_Init(void)
{
	volatile unsigned long delay;
	
	printf("\nSTART OF I2C0_Init()\n");
	printf("--------------------\n");
	
	//I2C clock : page 348 or 460
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
	SYSCTL_RCGC1_R			 |=  0x00001000;				// Enable I2C0 clock
  delay = SYSCTL_RCGC1_R;             				// delay, IDK, it's supposed to do something
	
  SYSCTL_RCGC2_R			 |=  0x00000002;        // Enable PORT B clock
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
	
	//PORT B - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTB_LOCK_R			=  0x4C4F434B;				// Unlock the register GPIOCR for PORT B
  GPIO_PORTB_CR_R			 |=  0x0C;							// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PB2 and PB3
	GPIO_PORTB_AFSEL_R	 |=  0x0C;							// Alternate function for pins PB2 and PB3
  GPIO_PORTB_DEN_R		 |=  0x0C;							// Enable digital for pins PB2 and PB3
  GPIO_PORTB_PUR_R     |=  0x04;    // Enable pullup resistors on pins PB2 I2C0SCL and PB3 
	GPIO_PORTB_ODR_R		 |=  0x08;							// PB3 I2C0SDA open drain
	GPIO_PORTB_PCTL_R		 |=  0x00003300;				// Set alternate functions: PB2 as I2C0SCL and PB3 as I2C0SDA
  GPIO_PORTB_PCTL_R		 &=  0xFFFF33FF;
  GPIO_PORTB_AMSEL_R	 &= ~0x0C;							// Disable analog function for pins PB2 and PB3

	//I2C0 - REGISTER CONFIGURATION
	//-----------------------------
	I2C0_I2CMCR_R		=   0x00000020;				//The microcontroller is a slave
	I2C0_I2CMTPR_R = 39;
	I2C0_I2CSOAR_R  =   0x0000005B;				//Address of the uC
	I2C0_I2CSOAR2_R =   0x00000000;				//No second address
	I2C0_I2CPC_R    =   0x00000000;
	I2C0_I2CSACKCTL_R = 0x00000000;
	
	// Interrupt
	I2C0_I2CSIMR_R = 0x7;
	NVIC_PRI2_R = (NVIC_PRI2_R&0xFFFFFF1F) | (2 << 5); // Priority (PRI_PORTB) of interrupt 1 (GPIO Port B)
  NVIC_EN0_R |= 0x1 << 8;      								// Enable interrupt 1 in NVIC

	I2C0_I2CSCSR_R  =   0x00000001;				//Enables slave's operation

	printf("I2C0_Init() - delay = SYSCTL_RCGC2_R = %ld\n",  delay);

	printf("END OF I2C0_Init()\n");
	printf("------------------\n\n");

}

void I2C0_enableSlave(void)
{
	I2C0_I2CSCSR_R = 1;
}

void I2C0_disableSlave(void)
{
	
}
