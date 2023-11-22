#include <stdio.h>  // Diamond braces for sys lib: Standard I/O
#include <stdint.h>
#include "uart.h"   // Quotes for user lib: UART lib
#include "GPIO.h"
#include "PWM.h"

#define number_of_LEDs			 144
#define number_of_LEDs_used	 50
#define number_of_bits			 32
#define reset_counter				 80
#define ResetCounts					 70

// PWM DEFINES
#define PWM_LOAD	12
#define BIT_OFF  	3						// See void set_current_bit_status(unsigned long status_is_on)
#define BIT_ON  	6						// See void set_current_bit_status(unsigned long status_is_on)

// 0x0000

typedef struct {
   unsigned long color;
   long position;
   long direction;
   long position_min;
   long position_max;
} LED;

void LED_Init(void);
void LED_SetToAvailable(void);
uint8_t LED_isBufferRead();

void setColorSet(int colorSet, int intensity);
void colorLED_to_buffer(unsigned long colorLED, unsigned long LEDnumber);
unsigned long color_addition(unsigned long color1, unsigned long color2);

uint8_t LED_ReadBuffer_PWM_Handler();
void LED_SetNextBit(uint8_t bitValue);