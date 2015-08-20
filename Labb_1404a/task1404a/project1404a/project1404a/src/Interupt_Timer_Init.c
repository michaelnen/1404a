/*
 * Interupt_Timer_Init.c
 *
 * Created: 1/22/2015 7:29:37 PM
 *  Author: Ola
 */ 

#include "asf.h"
#include "Interupt_Timer_Init.h"

void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	/* Configure power management of timer clocks */
	pmc_enable_periph_clk(ID_TC0);
	
	/* Configure TC for a 44,1kHz frequency and trigger on
	RC compare. */
	tc_find_mck_divisor(44100, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG); 
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / 44100);
	
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	tc_start(TC0, 0);
}