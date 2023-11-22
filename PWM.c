#include "PWM.h"

unsigned int motor1CMP;
unsigned int m;
//unsigned int motor2CMP;

//------------PWM0------------
// Initialize the PWM0
// Pin used: PD2 (M0FAULT0), PB6 (M0PWM0), PB7 (M0PWM1)
// Input: none
// Output: none
void PWM0_Init(void)
{
	volatile unsigned long delay;
	
	printf("\nSTART OF PWM0_Init()\n");
	printf("--------------------\n");
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
	SYSCTL_RCGC0_R			 |=  0x00100000;				// Register RCGC0 Enable PWM clock
  delay = SYSCTL_RCGC0_R;             				// delay, IDK, it's supposed to do something
  //while((SYSCTL_RCGC0_R & (0x1 << 20))==1);  // wait something
	
//printf("1\n");
	
  SYSCTL_RCGC2_R			 |=  0x0000000A;        // Enable PORT B (0x02) and PORT D (0x08) clock
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
  //while((SYSCTL_RCGC2_R & (0xA))==1);  // wait something
	
printf("2\n");
	
	//PORT B - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTB_LOCK_R			=  0x4C4F434B;				// Unlock the register GPIOCR for PORT B
  GPIO_PORTB_CR_R			 |=  0xC0;							// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PB6 and PB7
	GPIO_PORTB_AFSEL_R	 |=  0xC0;							// Alternate function for pins PB6 and PB7
//printf("3\n");
	
//	GPIO_PORTB_AFSEL_R	 &=  ~0xC0;		// No alternate function for pins PB6 and PB7
//  GPIO_PORTB_PUR_R     |=  0xC0;    // Enable pullup resistors on pins PF0 and PF4
	
  GPIO_PORTB_DEN_R		 |=  0xC0;							// Enable digital for pins PB6 and PB7 
	GPIO_PORTB_PCTL_R		 |=  0x44000000;				// Set alternate functions: PB6 as M0PWM0 and PB7 as M0PWM1
  GPIO_PORTB_PCTL_R		 &=  0x44FFFFFF;
  GPIO_PORTB_AMSEL_R	 &= ~0xC0;							// Disable analog function for pins PB6 and PB7
//printf("4\n");

/*
	//Interrupt configuration

  GPIO_PORTB_IS_R &= ~(0x1 << 6);     				// PB6 is edge-sensitive
//  GPIO_PORTB_IBE_R |= 0x1 << 6;   					// PB6 is  both edges
  GPIO_PORTB_IBE_R &= ~(0x1 << 6);   					// PB6 is not both edges
  GPIO_PORTB_IEV_R |= 0x1 << 6;    						// PB6 rising edge event
//  GPIO_PORTB_IEV_R &= ~(0x1 << 6);    						// PB6 falling edge event
  GPIO_PORTB_ICR_R |= 0x1 << 6;      					// clear interrupt related to pin 6
  GPIO_PORTB_IM_R |= 0x1 << 6;    						// Enable interrupt on PB6
  NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF1FFF) | (PRI_PORTB << 13); // Priority (PRI_PORTB) of interrupt 1 (GPIO Port B)
  NVIC_EN0_R |= 0x1 << 1;      								// Enable interrupt 1 in NVIC
*/
	//PORT D - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTD_LOCK_R			=  0x4C4F434B;	// Unlock the register GPIOCR for PORT B
  GPIO_PORTD_CR_R			 |=  0x04;							// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PD2
	GPIO_PORTD_AFSEL_R	 |= 0x04;								// Alternate function for pins PD2
  GPIO_PORTD_DEN_R		 |=  0x04;							// Enable digital for pins PD2 
	GPIO_PORTD_PCTL_R		 |=  0x00000400;				// Set alternate function: PD2 as M0FAULT0
  GPIO_PORTD_PCTL_R		 &=  0xFFFFF4FF;
  GPIO_PORTD_AMSEL_R	 &= ~0x04;							// Disable analog function for pins PD2 
//printf("5\n");
	
	//PWM0 - REGISTER CONFIGURATION
	//-----------------------------
	SYSCTL_RCC_R					= (SYSCTL_RCC_R&~(0x7<<17)) |	(0x2<<17)	// Set the PWM clock as the clock system divided by 8
	//SYSCTL_RCC_R					= (SYSCTL_RCC_R&~(0x7<<17)) |	(0x3<<17)	// Set the PWM clock as the clock system divided by 16
											  | (0x1<<20);
	PWM0_PWMFAULT_R				=  0x03;							// The M0PWM0 (PB6) and M0PWM1 (PB7) output signals are driven to the value specified by PWMFAULTVAL.
	PWM0_PWMFAULTVAL_R		=  0x01;							// In case of fault M0PWM0 (PB6) is high and M0PWM1 (PB7) is low
	PWM0_PWM0CTL_R				=  0x04;							// DEBUG set: counter always runs
	PWM0_PWM0LOAD_R				=  LOAD;							// Set the load value (counter goes from load value to 0)
	PWM0_PWM0CMPA_R				=  0;					// PWM0 Compare A
	PWM0_PWM0CMPB_R				=  33;	// PWM0 Compare B (see note 1 below)
	PWM0_PWM0GENA_R				=  0x0C8;							//PWM0 Compare A down means pwmA High (ACTCMPAD = 0x3) / Load reached means pwmA Low (ACTLOAD = 0x2)
	PWM0_PWM0GENB_R				=  0x80C;							// PWM0 Compare B down means pwmB Low (ACTCMPBD = 0x2) / Load reached means pwmA High (ACTLOAD = 0x3)  (see note 1 below)
	PWM0_PWM0CTL_R			 |=  0x01;							// ENABLE set
//printf("6\n");
	
	// Interrupt
	
	PWM0_PWMINTEN_R      |=  0x01;							// Enable interrupt for PWM generator 0
	PWM0_PWM0INTEN_R      =  0x01;							// Interrupt wwhen counter = 0
	PWM0_PWM0ISC_R			  =  0x01;							// Clears interrupt of PWM generator 0
	PWM0_PWMISC_R        |=  0x01;							// Clears main interrupt
//printf("7\n");
	
  NVIC_PRI2_R = (NVIC_PRI2_R&0xFFFFFFFF) | (PRI_PWM0GEN0 << 21); // Priority (PRI_PWM0GEN0) of interrupt 10 (PWM0 GEN0)
  NVIC_EN0_R |= 0x1 << 10;      								// Enable interrupt 10 in NVIC
//printf("8\n");
	
	motor1_setSpeed(0);													// Set motor to stop and initialize motor1CMP
	//motor2_setSpeed(0);													// Set motor to stop and initialize motor2CMP
	
//	ENABLE_MOTOR2
	ENABLE_PWM

	printf("PWM0_Init() - delay = SYSCTL_RCGC2_R = %ld\n",  delay);

	printf("END OF PWM0_Init()\n");
	printf("------------------\n\n");

	/***********
	Note 1 below																																				pwmA: ---__
	The cycle of pwmB is inverted to avoid pwmA and pwmB to be high at the same time		pwmB: __---
	***********/
}


//------------PWM0------------
// Initialize the PWM0
// Pin used: PD2 (M0FAULT0), PB6 (M0PWM0), PB7 (M0PWM1)
// Input: none
// Output: none

// I only use the PB6 for the LED

void LED_PWM0_Init(uint16_t PWM0LOAD, uint8_t RCC_PWMDIV)
{
	volatile unsigned long delay;
	
	printf("\nSTART OF PWM0_Init()\n");
	printf("--------------------\n");
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
	SYSCTL_RCGC0_R			 |=  (unsigned long)0x1 << 20;				// Register RCGC0 - PWM0 = 0x1: Enable PWM clock
  delay = SYSCTL_RCGC0_R;             			// delay, IDK, it's supposed to do something	
  SYSCTL_RCGC2_R			 |=  (unsigned long)	// Register RCGC2: Enable Clock Gating Control for
												((0x1 << 1)					// GPIOB
												+(0x1 << 3));       // GPIOD
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
	printf("This is important, I don't know why\n");
	
	//PORT B - REGISTER CONFIGURATION (PWM pins)
	//-------------------------------
  GPIO_PORTB_LOCK_R			= 0x4C4F434B;				// Register GPIOLOCK for PORTB: Unlock the register GPIOCR for PORT B
  GPIO_PORTB_CR_R			 |= (unsigned long)		// Register GPIOCR for PORTB: Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to the pins
												( (0x1 << 6)				// PB6
												+ (0x1 << 7));			// PB7	
	GPIO_PORTB_AFSEL_R	 |= (unsigned long) 	// Register GPIOAFSEL for PORTB: Alternate function selected for pins 
												( (0x1 << 6)				// PB6
												+ (0x1 << 7));			// PB7
  GPIO_PORTB_DEN_R		 |= (unsigned long)		// Register GPIODEN for PORTB: Enable digital for pins 
												( (0x1 << 6)				// PB6
												+ (0x1 << 7));			// PB7
	GPIO_PORTB_PCTL_R		 &=~(unsigned long) 	// Register GPIOPCTL for PORTB: Clear alternate functions for
												( (0xF << 24)				// PMC6 (PB6)
												+ (0xF << 28));			// PMC7 (PB7)
	GPIO_PORTB_PCTL_R		 |= (unsigned long) 	// Register GPIOPCTL for PORTB: Set alternate functions for
												( (0x4	<< 24)			// PMC6 (PB6) = 0x4 (M0PWM0)
												+ (0x4 << 28));			// PMC7 (PB7) = 0x4 (M0PWM1)
  GPIO_PORTB_AMSEL_R	 &=~(unsigned long)		// Register GPIOAMSEL for PORTB: Disable analog function for pins
												( (0x1 << 6)				// PB6
												+ (0x1 << 7));			// PB7
	
	//PORT D - REGISTER CONFIGURATION (PWM fault pin) (we could add M0PWM1 one day maybe)
	//-------------------------------
  GPIO_PORTD_LOCK_R			=  0x4C4F434B;				// Register GPIOLOCK for PORTD: Unlock the register GPIOCR for PORT B
  GPIO_PORTD_CR_R			 |= (unsigned long)			// Register GPIOCR for PORTD: Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN
													(0x1 << 2);					// PD2
	GPIO_PORTD_AFSEL_R	 |= (unsigned long)			// Register GPIOAFSEL for PORTD: Alternate function for pin
													(0x1 << 2);					// PD2
  GPIO_PORTD_DEN_R		 |= (unsigned long)			// Register GPIODEN for PORTD: Enable digital for pin
													(0x1 << 2);					// PD2
	GPIO_PORTD_PCTL_R		 &=~(unsigned long) 		// Register GPIOPCTL for PORTD: Clear alternate functions for
												  (0xF << 8);					// PMC2 (PD2)
	GPIO_PORTD_PCTL_R		 |= (unsigned long) 		// Register GPIOPCTL for PORTD: Set alternate functions for
												  (0x4	<< 8);				// PMC2 (PD2) = 0x4 (M0FAULT0)

	//PWM0 - REGISTER CONFIGURATION
	//-----------------------------
	SYSCTL_RCC_R					&=~(unsigned long)	// Register RCC
													 (0x7 << 17);			// PWMDIV = 0
	SYSCTL_RCC_R					|= (unsigned long)	// Register RCC
												(  (RCC_PWMDIV << 17)			// PWMDIV = 0x2: PWM clock = System clock / 8
												+  (0x1 << 20));		// USEPWMDIV = 0x1: PWM clock = PWMDIV
	PWM0_PWMFAULT_R				= (unsigned long)		// Register PWMFAULT
												( (0x1 << 0)				// FAULT0 = 0x1: The M0PWM0 (PB6) output signals is driven to the PWM0 bit in the PWMFAULTVAL register
												+ (0x1 << 1));			// FAULT1 = 0x1: The M0PWM1 (PB7) output signals is driven by the PWM1 bit in the PWMFAULTVAL register
	PWM0_PWMFAULTVAL_R		= (unsigned long)		// Register PWMFAULTVAL: In case of fault M0PWM0 (PB6) is high and M0PWM1 (PB7) is low
												( (0x1 << 0)				// PWM0: The MnPWM0 output signal is driven High during fault conditions if the FAULT0 bit in the PWMFAULT register is set.
												+ (0x1 << 1));			// PWM1: The MnPWM1 output signal is driven High during fault conditions if the FAULT1 bit in the PWMFAULT register is set
	PWM0_PWM0CTL_R				= (unsigned long)		// Register PWM0CTL
													(0x1 << 2);				// DEBUG = 0x1: The counter always runs when in Debug mode
	PWM0_PWM0LOAD_R				=  PWM0LOAD;						// Register PWM0LOAD: Set the load value (counter goes from load value to 0) = 12 pour les LED
	PWM0_PWM0CMPA_R				=  0;								// Register PWM0CMPA: PWM0 Compare A
	PWM0_PWM0CMPB_R				=  0;								// Register PWM0CMPB: PWM0 Compare B
	PWM0_PWM0GENA_R				= (unsigned long)		// Register PWM0GENA
												( (0x2 << 2)				// ACTLOAD = 0x3: Drive pwmA High when Counter = PWM0_PWM0LOAD_R (counter goes from LOAD to 0)
											  + (0x3 << 6));			// ACTCMPAD = 0x2: Drive pwmA Low when Counter = PWM0_PWM0CMPA_R
	PWM0_PWM0GENB_R				= (unsigned long)		// Register PWM0GENB
												( (0x2 << 2)				// ACTLOAD = 0x2: Drive pwmA High when Counter = PWM0_PWM0LOAD_R (counter goes from LOAD to 0)
											  + (0x3 << 10));			// ACTCMPBD = 0x3: Drive pwmA Low when Counter = PWM0_PWM0CMPB_R
	PWM0_PWM0CTL_R			 |=  0x1;							// Register PWM0CTL - ENABLE = 0x1 set: The PWM generation block is enabled and produces PWM signals
	
	// Interrupt	
	PWM0_PWMINTEN_R      |=  0x01;							// Register PWMINTEN - INTPWM0 = 0x1: Enable interrupt for PWM generator 0
	PWM0_PWM0INTEN_R      =  0x01 << 0;					// Register PWM0INTEN - INTCNTZERO = 0x1: Interrupt wwhen counter = 0
	PWM0_PWM0ISC_R			  =  0x01;							// Register PWM0ISC - INTCNTZERO = 0x1: Clears interrupt of PWM generator 0
	PWM0_PWMISC_R        |=  0x01;							// Register PWMISC - INTPWM0 Clears main interrupt
	
  NVIC_PRI2_R = (NVIC_PRI2_R&0xFFFFFFFF) | (PRI_PWM0GEN0 << 21); // Priority (PRI_PWM0GEN0) of interrupt 10 (PWM0 GEN0)
  NVIC_EN0_R |= 0x1 << 10;      								// Enable interrupt 10 in NVIC
		
	m=0; // cette variable est très importance, elle permet aux led d'aller super vite, ne me demande pas pourquoi, je n'en sais rien

	printf("PWM0_Init() - delay = SYSCTL_RCGC2_R = %ld\n",  delay);
	
	printf("END OF PWM0_Init()\n");
	printf("------------------\n\n");
}


//----------------------------
// Set the speed of the motor 1
// Update the value of PWM0_PWM0CMPA_R between
// Input: speed parameter [0 ; LOAD-1]
// Output: none
void motor1_setSpeed(unsigned long speed)
{/*
	motor1CMP = speed;
	
	if(speed == 0)
	{
		DISABLE_PWM
	}
	else
	{
		if(speed >= LOAD) motor1CMP = LOAD-1;	// if speed to high, set the speed to its maximum value
		ENABLE_PWM
		PWM0_PWM0CMPA_R = motor1CMP;				// PWM0 Compare A
	}*/
}


//----------------------------
// Set the speed of the motor 2
// Update the value of PWM0_PWM0CMPB_R between
// Input: speed parameter [0 ; LOAD-1]
// Output: none
void motor2_setSpeed(unsigned long speed)
{/*
	motor2CMP = speed;
	
	if(speed == 0)
	{
		DISABLE_MOTOR2
	}
	else
	{
		if(speed >= LOAD) motor2CMP = LOAD-1;	// if speed to high, set the speed to its maximum value
		ENABLE_MOTOR2
		PWM0_PWM0CMPB_R = LOAD - motor2CMP;				// PWM0 Compare B
	}*/
}

//----------------------------
// Set the current bit to 1 or 0
// Update the value of PWM0_PWM0CMPA_R between
// Input: 1 or 0
// Output: none
void set_current_bit_status(unsigned long status_is_on)
{
		ENABLE_PWM
		//if(status_is_on)	PWM0_PWM0CMPA_R = BIT_ON;				// PWM0 Compare A
		//else							PWM0_PWM0CMPA_R = BIT_OFF;			// PWM0 Compare A
}
