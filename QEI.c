#include <stdio.h>
#include "QEI.h"
#include "PWM.h"
#include "GPIO.h"
#include "uart.h"    // functions to implment input/output

long motor1_revCount;
long motor2_revCount;

//------------QEI0------------
// Initialize the PORT D for QEI0 (Quadrature Encoder Interface)
// ...
// Input: none
// Output: none
void QEI0_Init(void)
{
	volatile unsigned long delay;
	
	motor1_revCount = 0;
	
	printf("\nSTART OF QEI0_Init()\n");
	printf("--------------------\n");
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
  SYSCTL_RCGC2_R			 |=  0x00000008;        // Enable PORT D clock
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
	SYSCTL_RCGC1_R     |=  0x00100;							// Enable QEI0 clock
  delay = SYSCTL_RCGC1_R;											// delay, IDK, it's supposed to do something

	//PORT D - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTD_LOCK_R			=  0x4C4F434B;				// Unlock the register GPIOCR for PORT B
  GPIO_PORTD_CR_R			 |=  0xC8;							// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PD3 (IDX0), PD6 (PhA0) and PD7 (PhB0)
	GPIO_PORTD_AFSEL_R	 |=  0xC8;							// Alternate function for pins PD3 (IDX0), PD6 (PhA0) and PD7 (PhB0)
  GPIO_PORTD_DEN_R		 |=  0xC8;							// Enable digital for pins PD3 (IDX0), PD6 (PhA0) and PD7 (PhB0)
	GPIO_PORTD_PCTL_R		 |=  0x66006000;				// Set alternate functions: PD3 (IDX0), PD6 (PhA0) and PD7 (PhB0)
  GPIO_PORTD_PCTL_R		 &=  0x66FF6FFF;
  GPIO_PORTD_AMSEL_R	 &= ~0xC8;							// Disable analog function for pins PD3 (IDX0), PD6 (PhA0) and PD7 (PhB0)

	//QEI0 - SPECIFIC REGISTER CONFIGURATION
	//--------------------------------------
	QEI0_QEICTL_R					= (0x1<<5)						// Enables capture velocity
											  | (0x0<<6);						// Predivider on QEICOUNT set to 1 (will be optimized later)
	QEI0_QEIMAXPOS_R			= QEIMAXPOS;					// A lot
	QEI0_QEILOAD_R				= QEILOAD_R;					// Set timer to calculate speed to 12.5ms at 80MHz

	//Interrupt configuration
	
	QEI0_QEIINTEN_R 		 |= 0x1<<1;							// Enables interrupt of the timer
  NVIC_PRI3_R = (NVIC_PRI3_R&0xFFFF0FFF) | (PRI_QEI0 << 13); // Priority (PRI_QEI0) of interrupt 13 (QEI0)
  NVIC_EN0_R |= 0x1 << 13;      							// Enable interrupt 13 in NVIC
	
	QEI0_QEICTL_R				 |= 0x01;								// Enable the counter
	QEI0_QEIPOS_R					= POS_ZERO;						// Initialize the position counter

	printf("QEI0_Init() - delay = SYSCTL_RCGC1_R = %ld\n",  delay);
	
	printf("END OF QEI0_Init()\n");
	printf("------------------\n");
}

//------------QEI1------------
// Initialize the PORT C for QEI1 (Quadrature Encoder Interface)
// ...
// Input: none
// Output: none
void QEI1_Init(void)
{
	volatile unsigned long delay;
	
	motor2_revCount = 0;
	
	printf("\nSTART OF QEI1_Init()\n");
	printf("--------------------\n");
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
  SYSCTL_RCGC2_R			 |=  0x1<<2;		        // Enable PORT C clock
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
	SYSCTL_RCGC1_R     |=  0x1<<9;							// Enable QEI1 clock
  delay = SYSCTL_RCGC1_R;											// delay, IDK, it's supposed to do something

	//PORT C - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTC_LOCK_R			=  0x4C4F434B;				// Unlock the register GPIOCR for PORT B
  GPIO_PORTC_CR_R			 |=  (0x1<<4)						// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PC4 (IDX1),
												|	 (0x1<<5)						// PC5 (PhA1) and
												|  (0x1<<6);					// PC6 (PhB1)
	GPIO_PORTC_AFSEL_R	 |=  (0x1<<4)						// Alternate function for pins PC4 (IDX1),
												|	 (0x1<<5)						// PC5 (PhA1) and
												|  (0x1<<6);					// PC6 (PhB1)
  GPIO_PORTC_DEN_R		 |=  (0x1<<4)						// Enable digital for pins PC4 (IDX1),
												|	 (0x1<<5)						// PC5 (PhA1) and
												|  (0x1<<6);					// PC6 (PhB1)
	GPIO_PORTC_PCTL_R		  =  (GPIO_PORTC_PCTL_R&0x000FFFFF) | 0x06660000;	// Set alternate functions: PC4 (IDX1), PC5 (PhA1) and PC6 (PhB1)
  GPIO_PORTC_AMSEL_R	 &= ~((0x1<<4)					// Disable analog function for pins PC4 (IDX1),
												|	  (0x1<<5)					// PC5 (PhA1) and
												|   (0x1<<6));				// PC6 (PhB1)

	//QEI1 - SPECIFIC REGISTER CONFIGURATION
	//--------------------------------------
	QEI1_QEICTL_R					= (0x1<<5)						// Enables capture velocity
											  | (0x0<<6)						// Predivider on QEICOUNT set to 1 (will be optimized later)
												| (0x1<<9);						// Invert PhA
	QEI1_QEIMAXPOS_R			= QEIMAXPOS;					// A lot
	QEI1_QEILOAD_R				= QEILOAD_R;					// Set timer to calculate speed to 12.5ms at 80MHz
	
	//Interrupt configuration
	
	QEI1_QEIINTEN_R 		 |= 0x1<<1;							// Enables interrupt of the timer
  NVIC_PRI9_R = (NVIC_PRI9_R&0xFF0FFFFF) | (PRI_QEI1 << 21); // Priority (PRI_QEI1) of interrupt 38 (QEI1)
  NVIC_EN1_R |= 0x1 << 6;      							// Enable interrupt 38 in NVIC

  EnableInterrupts();           							// Clears the I bit

	QEI1_QEICTL_R				 |= 0x01;								// Enable the counter
	QEI1_QEIPOS_R					= POS_ZERO;						// Initialize the position counter

	printf("QEI1_Init() - delay = SYSCTL_RCGC1_R = %ld\n",  delay);
	
	printf("END OF QEI1_Init()\n");
	printf("------------------\n");
}

//------------QEI0------------
// Update the revolution counter of the motor 1
// ...
// Input: none
// Output: none
void update_motor1_revCount(void)
{
	long POS;
	
	POS = QEI0_QEIPOS_R - POS_ZERO;
	
	if( (POS < (-REV_EDGES)) || (REV_EDGES < POS) )
	{
		motor1_revCount += POS/REV_EDGES;
		QEI0_QEIPOS_R -= (REV_EDGES) * (POS/REV_EDGES);
	}
}

//------------QEI1------------
// Update the revolution counter of the motor 2
// ...
// Input: none
// Output: none
void update_motor2_revCount(void)
{
	long POS;
	
	POS = QEI1_QEIPOS_R - POS_ZERO;
	
	if( (POS < (-REV_EDGES)) || (REV_EDGES < POS) )
	{
		motor2_revCount += POS/REV_EDGES;
		QEI1_QEIPOS_R -= (REV_EDGES) * (POS/REV_EDGES);
	}
}
