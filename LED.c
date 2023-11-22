#include "LED.h"

long current_LED;
unsigned long current_LED_color;
long bit_counter;
long current_bit;
long reset_LED;
uint8_t bufferLED[number_of_LEDs][number_of_bits];

uint8_t bufferLED_test[number_of_LEDs*number_of_bits];
long bufferCounter_test;

LED LED_used[number_of_LEDs_used];

int currentLED;
int currentBit;
int resetCounter;

void LED_Init(void)
{
	unsigned long i;
	
  /* PROGRAMME TO CHANGE : put the priority in argument */	
	LED_PWM0_Init(PWM_LOAD, RCC_PWMDIV_8);		// PWM CLOCK = System Clock / 8 (System clock must be 80MHz) / LOAD = 12 (1 tick = 0.1us)
	//PWM0_Init();
	
	for(i=0;i<number_of_LEDs;i++)
	{
			colorLED_to_buffer(0x001000, i);
	}
	
	LED_SetToAvailable();		
}

void LED_SetToAvailable()
{
	DisableInterrupts();
	
	currentLED = 0;
	currentBit = 0;
	resetCounter = 0;
	
	bufferCounter_test = 0;
	
	PWM0_PWM0CMPA_R = 0;
	ENABLE_PWM0
	
	EnableInterrupts();
}

uint8_t LED_isBufferRead()
{
	return resetCounter >= ResetCounts;
}

void setColorSet(int colorSet, int intensity)
{
	// 0xFF << 24 -> GREEN
	// 0xFF << 16 -> RED
	// 0xFF << 8 -> BLUE
	
	if(colorSet)
	{
	colorLED_to_buffer((intensity & 0xFF) << 24, 0);
	colorLED_to_buffer((intensity & 0xFF) << 16, 1);
	colorLED_to_buffer((intensity & 0xFF) << 24, 2);
	colorLED_to_buffer((intensity & 0xFF) << 16, 3);
	colorLED_to_buffer((intensity & 0xFF) << 24, 4);
	colorLED_to_buffer((intensity & 0xFF) << 16, 5);
	colorLED_to_buffer((intensity & 0xFF) << 24, 6);
	}
	else
	{
	colorLED_to_buffer((intensity & 0xFF) << 8, 0);
	colorLED_to_buffer((intensity & 0xFF) << 24, 1);
	colorLED_to_buffer((intensity & 0xFF) << 8, 2);
	colorLED_to_buffer((intensity & 0xFF) << 24, 3);
	colorLED_to_buffer((intensity & 0xFF) << 8, 4);
	colorLED_to_buffer((intensity & 0xFF) << 24, 5);
	colorLED_to_buffer((intensity & 0xFF) << 8, 6);
	}
	
	LED_SetToAvailable();
}


void colorLED_to_buffer(unsigned long colorLED, unsigned long LEDnumber)
{
	long counter;

	for(counter=number_of_bits-1 ; counter>=0 ; counter--)
	{
		bufferLED[LEDnumber][counter] = colorLED & 0x01;
		colorLED = colorLED >> 1;
		//printf("%ld\t%ld\t%ld\n", counter, LEDnumber, bufferLED[counter][LEDnumber]);
	}
	
}

unsigned long color_addition(unsigned long color1, unsigned long color2)
{
	//0xABCD with A green, B; Red; C: blue; D: white
	unsigned long A, B, C, D;

	if(((color1>>24) + (color2>>24)) < 0xFF)								A = ( (color1>>24) + (color2>>24) ) & 0xFF;
	else																										A = 0xFF;

	if(((color1>>16)&0xFF) + ((color2>>16)&0xFF) < 0xFF)		B = ( (color1>>16 ) + (color2>>16 ) ) & 0xFF;
	else																										B = 0xFF;

	if(((color1>>8)&0xFF) + ((color2>>8)&0xFF) < 0xFF)			C = ( (color1>>8) + (color2>>8 ) ) & 0xFF;
	else																										C = 0xFF;

	if(((color1&0xFF) + (color2&0xFF)) < 0xFF)							D = ( (color1   ) + (color2    ) ) & 0xFF;
	else																										D = 0xFF;

	return ((A<<24) + (B<<16) + (C<<8) + D);
}

uint8_t LED_ReadBuffer_PWM_Handler()
{
	// Si on a lu tout le buffer, on s'arrête
	if(currentLED >= number_of_LEDs)  {
		PWM0_PWM0CMPA_R = 0;
		DISABLE_PWM0
		if(resetCounter < ResetCounts) {
			resetCounter++;
			return 0;
		}			
		return 0; // On dit qu'on a fini parce que la période de reset est terminée
	}
	
	LED_SetNextBit(bufferLED[currentLED][currentBit]);		
	if(currentBit < number_of_bits-1) {
		currentBit++;
	}
	else {
		currentBit = 0;
		currentLED++;
	}	
	return 0;
}

void LED_SetNextBit(uint8_t bitValue)
{	
	if((bitValue & 0x01) == 0x01) PWM0_PWM0CMPA_R = BIT_ON;
	else PWM0_PWM0CMPA_R = BIT_OFF;
	return;
	
	bufferLED_test[bufferCounter_test] = bitValue;
	bufferCounter_test++;
	return;
}

void LED_PrintBufferTest()
{
	int i;
	for(i=0 ; i<number_of_LEDs_used*number_of_bits ; i++)
	{
		printf("%d - %d\n", i, bufferLED_test[i]);
	}
}



