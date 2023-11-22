#include "unitTest.h"

uint8_t unitTestSelection = 0;
uint8_t unitTestDelay = 100;
uint8_t counter = 0;


// To be put in main function, before the while(1) loop
void testLED_1(void)
{	
	unsigned long i=1;
	uint8_t test_data = 0;
	int32_t data, last_test_data = 0, flag=1;
	uint8_t seq[6][2] = {{8,8} , {0,8} , {4,4} , {8,4} , {0,12} , {4,12}};
	uint8_t seq_i = 0;
	
	//printf("testLED_1\n");

	while(unitTestSelection == 1)
	{	
		if(LED_isBufferRead())
		{
			if(FIFO_Get(&test_data))
			{
				delay_ms(unitTestDelay);
				DisableInterrupts();
				
//				data = ((test_data&0xF0)<<seq[seq_i][0]) + ((test_data&0x0F)<<seq[seq_i][1]);
//				data = ((test_data&0xF0)<<8) + ((test_data&0x0F)<<8);		//GREEN + RED
//				data = ((test_data&0xF0)<<0) + ((test_data&0x0F)<<8);		//BLUE + RED
//				data = ((test_data&0xF0)<<4) + ((test_data&0x0F)<<4);		//RED + BLUE
//				data = ((test_data&0xF0)<<8) + ((test_data&0x0F)<<4);		//GREEN + BLUE
//				data = ((test_data&0xF0)<<0) + ((test_data&0x0F)<<12);	//BLUE + GREEN
//				data = ((test_data&0xF0)<<4) + ((test_data&0x0F)<<12);	//RED + GREEN
				
				colorLED_to_buffer(data, test_data%number_of_LEDs_used);
				colorLED_to_buffer(0, last_test_data%number_of_LEDs_used);
				last_test_data = test_data;
				LED_SetToAvailable();
				
				if(i==0 || i==255)
				{
					flag = -1*flag;
					seq_i = (seq_i+1) % 6;
				}
				i = i + flag;
				FIFO_Put(i);
				
				I2C0_enableSlave();
				EnableInterrupts();	// Clears the I bit
			}
			else
			{
				for(i=0;i<256;i++)
				{
						FIFO_Put(i);
				}
				i=255;
			}	
		}
	}
}

void testLED_2(void)
{	
	unsigned long i = 1;
	uint8_t test_data = 0;
	int32_t data, flag=1;
	uint8_t seq[6][2] = {{8,8} , {0,8} , {4,4} , {8,4} , {0,12} , {4,12}};
	uint8_t seq_i = 0;
	
	//printf("testLED_2\n");

	while(unitTestSelection == 2)
	{	
		if(LED_isBufferRead())
		{
			if(FIFO_Get(&test_data))
			{
				delay_ms(unitTestDelay);
				DisableInterrupts();
				
				data = ((test_data&0xF0)<<seq[seq_i][0]) + ((test_data&0x0F)<<seq[seq_i][1]);
//				data = ((test_data&0xF0)<<8) + ((test_data&0x0F)<<8);		//GREEN + RED
//				data = ((test_data&0xF0)<<0) + ((test_data&0x0F)<<8);		//BLUE + RED
//				data = ((test_data&0xF0)<<4) + ((test_data&0x0F)<<4);		//RED + BLUE
//				data = ((test_data&0xF0)<<8) + ((test_data&0x0F)<<4);		//GREEN + BLUE
//				data = ((test_data&0xF0)<<0) + ((test_data&0x0F)<<12);	//BLUE + GREEN
//				data = ((test_data&0xF0)<<4) + ((test_data&0x0F)<<12);	//RED + GREEN
				
				colorLED_to_buffer(data, test_data%number_of_LEDs_used);
				
				LED_SetToAvailable();
				
				if(i==0 || i==255)
				{
					flag = -1*flag;
					seq_i = (seq_i+1) % 6;
				}
				i = i + flag;
				FIFO_Put(i);
				
				I2C0_enableSlave();
				EnableInterrupts();	// Clears the I bit
			}
			else
			{
				for(i=0;i<256;i++)
				{
						FIFO_Put(i);
				}
				i=255;
			}	
		}
	}
}

void testLED_3(void)
{	
	unsigned long i, j, k;
	unsigned long current_LED_color;
	LED LED_used[LED_to_use];
	
	//printf("testLED_3\n");
	
//*	
	for(i=0;i<4;i++)
	{
	LED_used[i].color = (0x2 << (24 + i)) + (0x2 << (16 + 4 - i));
	LED_used[i].direction = 1;
	LED_used[i].position = 0;
	LED_used[i].position_min = 0;
	LED_used[i].position_max = number_of_LEDs_used + i;
		
	LED_used[4+i].color = (0x2 << (8 + i)) + (0x2 << (24 + 4 - i));
	LED_used[4+i].direction = 1;
	LED_used[4+i].position = 0;
	LED_used[4+i].position_min = 0;
	LED_used[4+i].position_max = number_of_LEDs_used + i + 4;
		
	LED_used[8+i].color = (0x2 << (16 + i)) + (0x2 << (8 + 4 - i));
	LED_used[8+i].direction = 1;
	LED_used[8+i].position = 0;
	LED_used[8+i].position_min = 0;
	LED_used[8+i].position_max = number_of_LEDs_used + i + 8;
	}
	
	while(unitTestSelection == 3)
	{			
		if(LED_isBufferRead())
		{
			CLOCK_delay_ms(50);
			DisableInterrupts();
			
			for(i=0 ; i<LED_to_use ; i++)
			{
				if(LED_used[i].position >= LED_used[i].position_max)			LED_used[i].direction = -1;
				else if(LED_used[i].position <=LED_used[i].position_min)	LED_used[i].direction = 1;
			}

			for(i=0;i<number_of_LEDs_used;i++)
			{
				j = 0;
				
				while(j < LED_to_use)
				{
					if(i == LED_used[j].position)
					{
						current_LED_color = 0x00;
						
						for(k=0;k<number_of_LEDs_used;k++)
						{
							//if(i == LED_used[k].position) current_LED_color = color_addition(current_LED_color, LED_used[k].color);
							if(i == LED_used[k].position) current_LED_color = LED_used[k].color & 0xFFFFFF00;
						}
						
						colorLED_to_buffer(0, LED_used[j].position-LED_used[j].direction);
						colorLED_to_buffer(current_LED_color, i);
						j = LED_to_use;
					}
					j++;
				}
				
				if(j == number_of_LEDs_used)  colorLED_to_buffer(0x0000, i);
			
			}

			for(i=0 ; i<LED_to_use ; i++)
			{
				LED_used[i].position += LED_used[i].direction;
			}
			
			LED_SetToAvailable();
			EnableInterrupts();	// Clears the I bit
		}
	}
}

void testLED_4(void)
{	
	unsigned long i, j, k;
	unsigned long current_LED_color;
	LED LED_used[LED_to_use];
	
	for(i=0;i<4;i++)
	{
	LED_used[i].color = (0x2 << (24 + i)) + (0x2 << (16 + 4 - i));
	LED_used[i].direction = 1;
	LED_used[i].position = 0;
	LED_used[i].position_min = 0;
	LED_used[i].position_max = number_of_LEDs_used + i;
		
	LED_used[4+i].color = (0x2 << (8 + i)) + (0x2 << (24 + 4 - i));
	LED_used[4+i].direction = 1;
	LED_used[4+i].position = 0;
	LED_used[4+i].position_min = 0;
	LED_used[4+i].position_max = number_of_LEDs_used + i + 4;
		
	LED_used[8+i].color = (0x2 << (16 + i)) + (0x2 << (8 + 4 - i));
	LED_used[8+i].direction = 1;
	LED_used[8+i].position = 0;
	LED_used[8+i].position_min = 0;
	LED_used[8+i].position_max = number_of_LEDs_used + i + 8;
	}
	
	while(unitTestSelection == 4)
	{	
		if(LED_isBufferRead())
		{
			CLOCK_delay_ms(50);
			DisableInterrupts();
			
			for(i=0 ; i<LED_to_use ; i++)
			{
				if(LED_used[i].position >= LED_used[i].position_max)			LED_used[i].direction = -1;
				else if(LED_used[i].position <=LED_used[i].position_min)	LED_used[i].direction = 1;
			}

			for(i=0;i<number_of_LEDs_used;i++)
			{
				j = 0;
				
				while(j < LED_to_use)
				{
					if(i == LED_used[j].position)
					{
						current_LED_color = 0x0000;
						
						for(k=0;k<number_of_LEDs_used;k++)
						{
							if(i == LED_used[k].position) current_LED_color = color_addition(current_LED_color, LED_used[k].color);
						}
						
						colorLED_to_buffer(current_LED_color, i);
						j = LED_to_use;
					}
					j++;
				}
				
				if(j == number_of_LEDs_used)  colorLED_to_buffer(0x0000, i);
			
			}

			for(i=0 ; i<LED_to_use ; i++)
			{
				LED_used[i].position += LED_used[i].direction;
			}
			
			LED_SetToAvailable();
			EnableInterrupts();	// Clears the I bit
		}
	}
}

void testFIFO_LED_1(void)
{
	// Goes with unitTest_1(); from ESP-32 CAM
	
	uint8_t test_data;
	int32_t  last_test_data = 0;
	
		while(1)
		{	
			if(LED_isBufferRead())
			{
				if(FIFO_Get(&test_data))
				{
					//delay_ms(20);
					DisableInterrupts();
					colorLED_to_buffer(test_data<<8, test_data%number_of_LEDs_used);
					colorLED_to_buffer(0, last_test_data%number_of_LEDs_used);
					last_test_data = test_data;
					LED_SetToAvailable();
					I2C0_enableSlave();
					
					printf("\ntestFIFO_LED_1\n");
					printf("%d\n",getFIFO_size());
					
					EnableInterrupts();	// Clears the I bit
				}	
			}
		}
}

void setUnitTestSelection(uint8_t selection)
{
	unitTestSelection = selection;
	printf("selection : %d\n", unitTestSelection);
}

uint8_t getUnitTestSelection() { return unitTestSelection; }

void setUnitTestDelay(uint8_t delay)
{
	unitTestDelay = delay;
	printf("delay : %d\n", unitTestDelay);
}

