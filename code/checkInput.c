/*
 * checkInput.c
 *
 *  Created on: Apr 10, 2022
 *      Author: anyss
 */


/*
 * in:  potentiometer values
 * out: which potentiometer, what direction
 */

/*
 * poll potentiometer values and check for
 * 2 bit ADC the pot rests between 1800 and 2200, and when turned it goes to 2600 or 1000
 *
 * output / store
 * is movement left or right, what face
 */

//read adc ex code
// Global variables
unsigned int ADC_value=0;

// Function prototypes
void ConfigureAdc(void);

void main(void)
{
	{
		WDTCTL = WDTPW + WDTHOLD;		// Stop WDT
		BCSCTL1 = CALBC1_1MHZ;			// Set range   DCOCTL = CALDCO_1MHZ;
		BCSCTL2 &= ~(DIVS_3);			// SMCLK = DCO = 1MHz
		P1SEL |= BIT3;					// ADC input pin P1.3
		ConfigureAdc();					// ADC set-up function call
		__enable_interrupt();			// Enable interrupts.

		while(1)
		{
			__delay_cycles(1000);				// Wait for ADC Ref to settle
			ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start
			__bis_SR_register(CPUOFF + GIE);	// Low Power Mode 0 with interrupts enabled
			ADC_value = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value

		}

	}
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	__bic_SR_register_on_exit(CPUOFF);        // Return to active mode }
}

// Function containing ADC set-up
void ConfigureAdc(void)
{

	ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
	ADC10AE0 |= BIT3;                         // ADC input enable P1.3
}