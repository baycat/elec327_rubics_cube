#include <msp430.h> 


/**
 * main.c
 */



/*
 * game logic
 *
 *
 * loop until success
 *
 *      check input
 *
 *      modify face displays
 *
 *      check for success
 *
 * display 'win'
 *
 */



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	return 0;
}
