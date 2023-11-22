/*
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPIO.h"
#include "UART.h"
#include "LED.h"
*/
#include "unitTest.h"
#include "Clock.h"

int colorIntensity;
int dimingDirection;
int colorSet;

uint32_t nSysTickTicks;
uint32_t timeArray[100][2];
uint16_t timeArrayCounter;

int __main(void)
{
	int i;
	uint8_t ready = 2;
	
	colorSet = 0;
	colorIntensity = 0x00;
	dimingDirection = 1;
		
	DisableInterrupts();
	
	CLOCK_PLL_Init(CLOCK_PLL_80MHz);
	UART_Init_WithBaudrate(115200);
	//UART_Init_WithBaudrate(9600);
	
	nSysTickTicks = 0;
	timeArrayCounter = 0;

	CLOCK_SysTickInitFromTicks(0x2FFFFF, 0);
	CLOCK_SysTickEnable(1);
	
	PORTF_Init();
	LED_Init();
	
	EnableInterrupts();	// Clears the I bit
		
	uint32_t color = 0x101;
	
	while(0)
	{
		CLOCK_delay_ms(300);
		
		LED_SetToAvailable();
		
		for(i=0;i<number_of_LEDs;i=i+2)
		{
				colorLED_to_buffer(0x00000000, i);
				colorLED_to_buffer(color, i+1);
		}
		
		
		if(color == 0x0)
		{
			color = 0x101;
		}
		else
		{
			color = color << 1;
		}
		
	}
	
	setUnitTestSelection(3);
	testLED_3();
		
	while(1)
	{		
		if(LED_isBufferRead())
		{
			colorIntensity = (colorIntensity + dimingDirection);
			if(colorIntensity <= 0 || colorIntensity >= 100) dimingDirection *= -1;
			setColorSet(colorSet, colorIntensity);
			delay_ms(10);
		}
	}
	
		
	return 0;
}



void PWM0_0_Handler(void)
{
	// premier bit est le plus fort
	// 0 - 8 vert
	// 9 - 16 rouge
	// 17 à 24 bleu
	
	LED_ReadBuffer_PWM_Handler();
	
	/*
	if(timeArrayCounter < 100)
	{
		//timeArray[timeArrayCounter ][0] = nSysTickTicks;
		timeArray[timeArrayCounter ][1] = CLOCK_GetSYSTICK_CurrentTimer();
		timeArrayCounter++;
	}//*/
	
	PWM0_PWM0ISC_R			  =  0x01;							// Clears interrupt of PWM generator 0
}

void SysTick_Handler()
{
	/*
	nSysTickTicks++;
	
	if(timeArrayCounter == 100)
	{		
		int n;
		
		for(i=1;i<100;i++)
		{
			n = (int) ((timeArray[i-1][1] - timeArray[i][1]));
			//n = (int) ((timeArray[i][0] - timeArray[i][1]));
			printf("%d\n", n);
		}
		timeArrayCounter++;
	}
	//*/
}


