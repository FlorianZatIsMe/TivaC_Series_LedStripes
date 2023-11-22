#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>  // Diamond braces for sys lib: Standard I/O
//#include "uart.h"   // Quotes for user lib: UART lib
#include "GPIO.h"
#include "PWM.h"
#include "os.h"
#include "LED.h"
#include "I2C.h"
#include "Clock.h"

#define LED_to_use 16

void testLED_1(void);
void testLED_2(void);
void testLED_3(void);
void testLED_4(void);
void testFIFO_LED_1(void);
void setUnitTestSelection(uint8_t selection);
void setUnitTestDelay(uint8_t delay);
uint8_t getUnitTestSelection();
