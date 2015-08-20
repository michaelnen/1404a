#include "BlinkLED.h"
#include "Dek.h"
#include "DelayFunctions.h"

register_ctrl *const p_PIOB_SODR = (register_ctrl *) 0x400E1030U;	/* defines the address for setting the output pins of the B register */
register_ctrl *const p_PIOB_CODR = (register_ctrl *) 0x400E1034U;

void startBlink()
{
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

	}
}

/*Blinkning f�r bokstav S*/
void letterS(int delay_tm)
{
	/* R�knare */
	int k;
	int l=0;
	
	/*Kort blink 3 g�nger*/
	for (k=0; k<3; k++)
	{
		PIOB_SODR = pin(27);
		
		delay(delay_tm);
		
		PIOB_CODR = pin(27);
		
		/*G�r en paus de tv� f�rsta g�ngerna*/
		if(l<2){
			delay(delay_tm);
		}
		l++;
	}
	
	
}

/*Blinkning f�r bokstav O*/
void letterO(int delay_tm)
{
	/* R�knare */
	int k;
	int l=0;
	
	/*l�ngt blink 3 g�nger*/
	for (k=0; k<3; k++)
	{
		PIOB_SODR = pin(27);
		
		delay(delay_tm * 3);
		
		PIOB_CODR = pin(27);
		
		/*G�r en paus de tv� f�rsta g�ngerna*/
		if(l<2){
			delay(delay_tm);
		}
		
		l++;
	}
}

/*Paus mellan bokst�ver med l�ngden delay*/
void paus(int delay_tm)
{
	delay(delay_tm);
}