#include <stdio.h>
#include "GPIO.h"
#include "UART.h"    // functions to implment input/output

void PORTC_Init(void)
{
	//PORT F - STANDARD REGISTER CONFIGURATION
	//-------------------------------
	volatile unsigned long delay;
	
  SYSCTL_RCGC2_R     |=  0x04;        // Enable PORT C clock
  delay = SYSCTL_RCGC2_R;             // delay, IDK, it's supposed to do something
  GPIO_PORTC_LOCK_R   =  0x4C4F434B;  // Unlock the register GPIOCR
  GPIO_PORTC_CR_R    |=  0x70;        // Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PF0 (maybe PF0 has to be set to 0 see page 671) to PF4
		
	//PORT F - SPECIFIC REGISTER CONFIGURATION
	//----------------------------------------
  GPIO_PORTC_AFSEL_R &= (unsigned long)~0x70;        // No alternate function for pins PF0 to PF4
	GPIO_PORTC_PUR_R   |=  0x60;        // Enable pullup resistors on pins PF0 and PF4
  GPIO_PORTC_DEN_R   |=  0x60;        // Enable digital for pins PF0 to PF4  
	GPIO_PORTC_AMSEL_R &= (unsigned long)~0x70;        // Disable analog function for pins PF0 to PF4 -> JE PENSE QUE CE TRUC NE SERT A RIEN
  GPIO_PORTC_DIR_R   &= (unsigned long)~0x70;        // PF0 and PF4 input, PF1 to PF3 output 
	
	printf("PORTC_Init() - delay = SYSCTL_RCGC2_R = %ld\n\n",  delay);
}

//------------PORT E------------
// Initialize the PORT E
// GPIO ; Digital ; PE0 and PE4 input with pull-up resistors ; PE1 to PE3 output
// Input: none
// Output: none
void PORTE_Init(void)
{
	//PORT E - STANDARD REGISTER CONFIGURATION
	//----------------------------------------
	volatile unsigned long delay;
	
  SYSCTL_RCGC2_R     |=  0x10;        // Enable PORT E clock
  delay = SYSCTL_RCGC2_R;             // delay, IDK, it's supposed to do something
  GPIO_PORTE_LOCK_R   =  0x4C4F434B;  // Unlock the register GPIOCR
  GPIO_PORTE_CR_R    |=  0x1F;        // Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PF0 (maybe PF0 has to be set to 0 see page 671) to PF4
		
	//PORT F - SPECIFIC REGISTER CONFIGURATION
	//----------------------------------------
  GPIO_PORTE_AFSEL_R &= (unsigned long)~0x1F;        // No alternate function for pins PE0 to PE4
  GPIO_PORTE_PCTL_R   =  0x00000000;  // Clear alternate function -> JE PENSE QUE CE TRUC NE SERT A RIEN
  GPIO_PORTE_PUR_R   |=  0x11;        // Enable pullup resistors on pins PE0 and PE4
  GPIO_PORTE_DEN_R   |=  0x1F;        // Enable digital for pins PE0 to PE4   
	
  GPIO_PORTE_AMSEL_R &= (unsigned long)~0x1F;        // Disable analog function for pins PE0 to PE4 -> JE PENSE QUE CE TRUC NE SERT A RIEN
  GPIO_PORTE_DIR_R    =  0x0E;        // PE0 and PE4 input, PE1 to PE3 output   
	
	printf("PORTE_Init() - delay = SYSCTL_RCGC2_R = %ld\n",  delay);
}

//------------PORT F------------
// Initialize the PORT F
// GPIO ; Digital ; PF0 and PF4 input with pull-up resistors ; PF1 to PF3 output
// Input: none
// Output: none
void PORTF_Init(void)
{
	//PORT F - STANDARD REGISTER CONFIGURATION
	//----------------------------------------
	volatile unsigned long delay;
	
  SYSCTL_RCGC2_R     |=  0x20;        // Enable PORT F clock
  delay = SYSCTL_RCGC2_R;             // delay, IDK, it's supposed to do something
  GPIO_PORTF_LOCK_R   =  0x4C4F434B;  // Unlock the register GPIOCR
  GPIO_PORTF_CR_R    |=  0x1F;        // Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PF0 (maybe PF0 has to be set to 0 see page 671) to PF4
		
	//PORT F - SPECIFIC REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTF_AFSEL_R &= (unsigned long)~0x1F;        // No alternate function for pins PF0 to PF4
  GPIO_PORTF_PCTL_R   =  0x00000000;  // Clear alternate function -> JE PENSE QUE CE TRUC NE SERT A RIEN
  GPIO_PORTF_PUR_R   |=  0x11;        // Enable pullup resistors on pins PF0 and PF4
  GPIO_PORTF_DEN_R   |=  0x1F;        // Enable digital for pins PF0 to PF4  
	
  GPIO_PORTF_AMSEL_R &= (unsigned long)~0x1F;        // Disable analog function for pins PF0 to PF4 -> JE PENSE QUE CE TRUC NE SERT A RIEN
  GPIO_PORTF_DIR_R    =  0x0E;        // PF0 and PF4 input, PF1 to PF3 output   
	
	printf("PORTF_Init() - delay = SYSCTL_RCGC2_R = %ld\n\n",  delay);
}

//------------PORT F------------
// Initialize the PORT F enabling interrupt on PF4 (digital input)
// 
// Input: none
// Output: none
void PORTF_InterruptInit(void)
{
	volatile unsigned long delay;
	
	printf("\nSTART OF PORTF_InterruptInit()\n");
	printf("------------------------------\n");
	
	//CLOCK - REGISTER CONFIGURATION
	//------------------------------
  SYSCTL_RCGC2_R			 |=  0x1 << 5; 	     		// Enable PORT F
  delay = SYSCTL_RCGC2_R;            					// delay, IDK, it's supposed to do something
	
	//PORT F - REGISTER CONFIGURATION
	//-------------------------------
  GPIO_PORTF_LOCK_R			=  0x4C4F434B;				// Unlock the register GPIOCR for PORT F
  GPIO_PORTF_CR_R			 |=  0x1 << 4;					// Allow change on the registers GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN to PF4
	GPIO_PORTF_AFSEL_R	 &= (unsigned long)~(0x1 << 4);				// No alternate function for pin PF4
  GPIO_PORTF_PCTL_R		 &= (unsigned long)~(0xF << 16);				// Clear alternate functions for pin PF4
  GPIO_PORTF_PUR_R   |=  0x10;        				// Enable pullup resistors on pin PF4
  GPIO_PORTF_DEN_R		 |=  0x1 << 4;					// Enable digital for pins PB6 and PB7 
  GPIO_PORTF_AMSEL_R	 &= (unsigned long)~(0x1 << 4);				// Disable analog function for pins PB6 and PB7 
  GPIO_PORTF_DIR_R    &= (unsigned long)~(0x1 << 4);       	 // PF4 input

	//Interrupt configuration

  GPIO_PORTF_IS_R &= (unsigned long)~(0x1 << 4);     				// PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= (unsigned long)~(0x1 << 4);   					// PF4 is not both edges
  GPIO_PORTF_IEV_R &= (unsigned long)~(0x1 << 4);    				// PF4 falling edge event
  GPIO_PORTF_ICR_R |= 0x1 << 4;      					// clear interrupt related to pin 4
  GPIO_PORTF_IM_R |= 0x10;      							// Enable interrupt on PF4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF0FFFFF) | (PRI_PORTF << 21); // Priority (PRI_PORTF) of interrupt 30 (GPIO Port F)
  NVIC_EN0_R |= 0x1 << 30;      								// Enable interrupt 30 in NVIC
		
	printf("PORTF_InterruptInit() - delay = SYSCTL_RCGC2_R = %ld\n",  delay);

	printf("END OF PORTF_InterruptInit()\n");
	printf("----------------------------\n\n");
}

//------------SYSTICK------------
// Initialize the Timer SYSTICK with interrupt
// 
// Input: none
// Output: none
void SysTick_InterruptInit(void)
{/*
	printf("\nSTART OF SysTick_InterruptInit()\n");
	printf("--------------------------------\n");
	
	SYSTICK_STCTRL_R 		= 0x00000000;															// Disables SysTick
	SYSTICK_STRELOAD_R	= STRELOAD;																// Update the timer value (max here)
	SYSTICK_STCURRENT_R	= STRELOAD;																// Set the current timer
	NVIC_PRI3_R = (NVIC_PRI3_R&0x0FFFFFFF) | (0x03<<29);		// Set interrupt priority to PRI_SYSTICK
	SYSTICK_STCTRL_R 		= 0x00000007;															// Enable clock with interrupt
	
	printf("END OF SysTick_InterruptInit()\n");
	printf("------------------------------\n");*/
}

//------------PLL------------
// Set the uC clock to 80MHz using the PLL
// 
// Input: none
// Output: none
void PLL_Init(void){
	
	unsigned int buffer;
	
	//printf("\nSTART OF PLL_Init()\n");
	//printf("-------------------\n");
	
//  SYSCTL_RCC_R = (SYSCTL_RCC_R & (unsigned long)~(0x1F << 6))							// clear XTAL field, bits 10-6
//							 + (0x15 << 6);  														// 10101, configure for 16 MHz crystal (select the crystal value and oscillator source)
	
	
  SYSCTL_RCC2_R |= 0x80000000; 														// Use RCC2 - USERCC2
  SYSCTL_RCC2_R |=  0x1 << 11;  													// Bypass PLL while initializing: BYPASS2, PLL bypass
  SYSCTL_RCC2_R &= (unsigned long)~(0x7 << 4);  													// configure for main oscillator source
  SYSCTL_RCC2_R &= (unsigned long)~(0x1 << 13); 													// activate PLL by clearing PWRDN
  SYSCTL_RCC2_R |= (0x1 << 30); 													// use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R& (unsigned long)~(0x7F << 22)) 					// clear system clock divider		
                + (0x4<<22);     			 										// configure for 80 MHz clock

  while((SYSCTL_RIS_R & (0x1 << 6))==0);  // wait for the PLL to lock by polling PLLLRIS

  SYSCTL_RCC2_R &= (unsigned long)~(0x1 << 11);													// enable use of PLL by clearing BYPASS
/*
//Update UART settings for the baudrate to remain equal to 115 200
	UART0_IBRD_R = 43;																			// IBRD = int(80,000,000 / (16 * 115,200)) = int(43.40)
	UART0_FBRD_R = 26;                     // FBRD = round(0.40278 * 64 ) = 26
//	UART0_IBRD_R = 108;																			// IBRD = int(80,000,000 / (16 * 115,200)) = int(43.40)
//	UART0_FBRD_R = 32;                     // FBRD = round(0.40278 * 64 ) = 26
	UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);				// apply changes on IBRD
		*/
	buffer = SYSCTL_RCC2_R;
	//printf("8.SYSCTL_RCC2_R: %#x\n", buffer);

	//printf("\nEND OF PLL_Init()\n");
	//printf("-----------------\n");	
}

//------------DELAY------------
// Delay function expressed ticks
// 
// Input: delay in tick
// Output: none
void delay_ticks(unsigned long nticks)
{/*
	unsigned long start;	
	unsigned long end;
	
	//unsigned long temp;

	start = SYSTICK_STCURRENT_R;
	SYSTICK_STCTRL_R &= (unsigned long)~(0x1<<16);
	
	if(start >= nticks)
	{
		end = start - nticks;
		while( (SYSTICK_STCURRENT_R > end) && !(SYSTICK_STCTRL_R&(0x1<<16)) );
		/*
		temp = SYSTICK_STCURRENT_R;
		printf("1-Sart: %#x\n",start);
		printf("1-Calculated end: %#x\n", end);
		printf("1-Actual end: %#x\n", temp);
		printf("1-Calculated nticks: %ld\n", start-temp);
		printf("1-Turn: %#x\n\n", SYSTICK_STCTRL_R&(0x1<<16));
		
	}
	else
	{
		end = STRELOAD - nticks + start;
		while(!(SYSTICK_STCTRL_R & (0x1 << 16) ));
		SYSTICK_STCTRL_R &= (unsigned long)~(0x1<<16);
		while( (SYSTICK_STCURRENT_R > end) && !(SYSTICK_STCTRL_R&(0x1<<16)) );
		
		//
		temp = SYSTICK_STCURRENT_R;
		printf("2-Sart: %#x\n",start);
		printf("2-Calculated end: %#x\n", end);
		printf("2-Actual end: %#x\n", temp);
		printf("2-Calculated nticks: %ld\n", STRELOAD - temp + start);
		printf("2-Turn: %#x\n\n", SYSTICK_STCTRL_R&(0x1<<16));
		
	}*/
}

//------------DELAY------------
// Delay function expressed in ms using SysTick
// 
// Input: delay in ms
// Output: 0 if correct input 1 otherwise
void delay_ms(unsigned long nms)
{
	unsigned long i;
	for(i=0;i<nms;i++) delay_ticks(80000); // 1ms / clock period (ns)
}
