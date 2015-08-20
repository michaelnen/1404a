/*
 * main.c
 *
 * Author: Ola Dahl, Michael Nilsson
 */

#include "asf.h"
#include "conf_board.h"

#include "DelayFunctions.h"
#include "LCDFunctions.h"
#include "ADFunctions.h"
#include "Interupt_Timer_Init.h"
#include "BlinkLED.h"
#include "Dek.h"

uint32_t result=1234;
int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	
	board_init();
	sysclk_init();

	// Insert application code here, after the board has been initialized.
	
	//Initiera delay
	delay_init();	
	
	
	
	//Initiera LCD
	LCDInit();
	
	//Initiera AD-omvandlare
	adc_setup();
	
	//Starta upp LCD
	setupLCD();
	
	
	//Initiera interupt
	configure_tc();
	
	int delay_time = 200000;	/* variable determining the length of a delay */
	
	PIOB_init(27);
	for (;;)	/* repeat blink in infinity */
	{

		letterS(delay_time);
		
		paus(delay_time * 3);
		
		letterO(delay_time);
		
		paus(delay_time * 3);
		
		letterS(delay_time);

		paus(delay_time * 5);
		
		clearDisplay();
		delay(delay_time);
		
		printNumber(result);
		
		
		
	}
	
	return 0;	
	
}


void TC0_Handler()
{
	volatile uint32_t ul_dummy;
	
	//Nollställ statusbit för att bekräfta interupt
	ul_dummy = tc_get_status(TC0, 0);
	
	UNUSED(ul_dummy); //Förhindra varning
	
	//Gör saker
	adc_start(ADC);
	result = adc_get_latest_value(ADC);
}







