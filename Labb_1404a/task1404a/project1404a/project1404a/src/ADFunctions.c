/*
 * ADFunctions.c
 *
 * Author: Michael Nilsson och Ola Dahl
 */ 

#include "asf.h"
#include "ADFunctions.h"

void adc_setup(void) /* Initierar och ställer in AD-omvandlaren för användning */
{    
	/* Startar klocka för pereferienhet*/
	pmc_enable_periph_clk(ID_ADC);
	
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	
	adc_enable_channel(ADC, ADC_CHANNEL_7);
	
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	
	adc_start(ADC);
}