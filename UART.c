// UART.c
// Runs on LM3S811, LM3S1968, LM3S8962, LM4F120
// Simple device driver for the UART.
// Daniel Valvano
// June 17, 2013

/* This example accompanies the books
  "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
  ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013

"Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
 
 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "UART.h"
//#include <stdio.h>
	
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control





//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming 16 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init_WithBaudrate(int baudRate){
  SYSCTL_RCGC1_R |= (unsigned long)0x1 << 0; 					// Register RCGC1 - UART0 = 0x1: UART0 Clock Gating Control
	SYSCTL_RCGC2_R |= (unsigned long)0x1 << 0;					// Register RCGC2 - GPIOA = 0x1: Port A Clock Gating Control
	
  UART0_CTL_R &= (unsigned long)											// Register UARTCTL for UART0
							 ~((0x1 << 0)														// UARTEN = 0x0: disable UART
							 + (0x1 << 5));      										// HSE = 0x0: The UART is clocked using the system clock divided by 16 (see calculation of UART0_IBRD_R below)

	float BRD = CLOCK_GetSystemClock() * 1000000 / (16 * baudRate);
	float BRDF = BRD - (int)BRD;
	UART0_IBRD_R = (int)(BRD); // Register UARTIBRD for UART0
  UART0_FBRD_R = (int)(BRDF * 64 + 0.5);                     							// FBRD = round(0.40278 * 64 ) = 26
  //UART0_FBRD_R = 26;                     							// FBRD = round(0.40278 * 64 ) = 26

	// Register UARTLCRH - 8 bit word length (no parity bits, one stop bit, FIFOs)
	UART0_LCRH_R = (unsigned long)											// SPS = 0x0: stick parity is disabled
   (0x3 << 5																					// WLEN = 0x3
	| 0x1 << 4);																				// FEN = 0x1
																											// STP2 = 0x0: One stop bit is transmitted at the end of a frame.
																											// EPS = 0x0: Odd parity is performed, which checks for an odd number of 1s.
																											// PEN = 0x0: Parity is disabled and no parity bit is added to the data frame
																											// BRK = 0x0: UART Send Break (Normal use)
  UART0_CTL_R |= (unsigned long)0x1 << 0;       			// Register UARTCTL for UART0 - UARTEN = 0x1: enable UART

  GPIO_PORTA_AFSEL_R |= 															// Register GPIOAFSEL - for PORTA: enable alternate hardware function on pins
		(0x1 << 1)																				// PA1
	+ (0x1 << 0);         															// PA0
  GPIO_PORTA_DEN_R |=             										// Register GPIODEN for PORTA: enable digital I/O on pins
		(0x1 << 1)																				// PA1
	+ (0x1 << 0);         															// PA0

  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & (unsigned long)~(0xFF << 0))	// Register GPIOPCTL for PORTA
										+ (0x1 << 4)																				// PMC1 = 0x1 pin PA1 set to UART0
										+ (0x1 << 0); 																			// PMC0 = 0x1 pin PA0 set to UART0
  GPIO_PORTA_AMSEL_R &= (unsigned long)          			// Register GPIOAMSEL for PORTA disable analog functionality on pins
											~((0x1 << 0)										// PA1
											+( 0x1 << 1));									// PA0
}


//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}



// Print a character to OLED.
int fputc(int ch, FILE *f){
  if((ch == 10) || (ch == 13) || (ch == 27)){
    UART_OutChar(13);
    UART_OutChar(10);
    return 1;
  }
  UART_OutChar(ch);
  return 1;
}
// No input from UART, always return data.
int fgetc (FILE *f){
	char ch;
	ch = UART_InChar();
	UART_OutChar(ch);
  return ch;
}
// Function called when file error occurs.
int ferror(FILE *f){
  /* Your implementation of ferror */
  return EOF;
}

