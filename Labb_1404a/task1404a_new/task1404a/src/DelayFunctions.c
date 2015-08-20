//
//  DelayFunctions.c
//  Code to be used in task 1401c
//
//	Michael Nilsson och Ola Dahl.
//
//

#include "asf.h"
#include "DelayFunctions.h"

void delay_init(void)		/* Initializes the timer used for delays */
{
	pmc_enable_periph_clk(ID_TC4);
	tc_init(TC1,1,0);		 /* TC1, channel 1, TCLK1 och capturemode */
	tc_set_block_mode(TC1,0);
	tc_stop(TC1,1);			/* making sure the timer does not run  */
}


void delay(uint32_t us)		/* A simple implementation for a delay in us (not calibrated) */
{
	tc_start(TC1,1);
	while (tc_read_cv(TC1,1) < us*42);
	tc_stop(TC1,1);
}