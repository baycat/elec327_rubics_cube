#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>
#include "LEDinterface.h"
#include "rotationLogic.h"

uint8_t red[] = {0xF0, 10, 0, 0};
uint8_t blue[] = {0xF0, 0, 10, 0};
uint8_t green[] = {0xF0, 0, 0, 10};
uint8_t yellow[] = {0xF0, 10, 0, 10};
uint8_t orange[] = {0xF0, 10, 0, 5};
uint8_t purple[] = {0xF0,10, 10, 0};
uint8_t white[] = {0xF0, 10, 10, 10};
uint8_t off[] = {0xE0, 0, 0, 0};

void init_wdt(void){
    
    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO
    WDTCTL = WDT_ADLY_16;    // WDT 16ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}

int main(void){
    WDTCTL = WDTPW | WDTHOLD;
    ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_0; // input A0
    ADC10AE0 |= 0x01; // PA.0 ADC option select
    P1DIR &= ~BIT0;
    BCSCTL3 |= LFXT1S_2;
    init_wdt();
    
    rgb_init_spi();
    
    TA0CTL = TASSEL_1 + MC_1;     // ACLK, upmode
    TA0CCR0 = 20;              // Interrupt should happen every ~12 kHz / 12000
    TA0CCTL0 = CCIE;              // CCR0 interrupt enabled

    _enable_interrupts();

    uint8_t *LED1, *LED2, *LED3, *LED4, *LED5, *LED6, *LED7, *LED8, *LED9, *LED10, *LED11, *LED12, *LED13, *LED14, *LED15, *LED16, *LED17, *LED18;
    LED1 = yellow;
    LED2 = yellow;
    LED3 = yellow;
    LED4 = blue;
    LED5 = blue;
    LED6 = blue;
    LED7 = red;
    LED8 = red;
    LED9 = red;
    LED10 = green;
    LED11 = green;
    LED12 = green;
    LED13 = blue;
    LED14 = blue;
    LED15 = red;
    LED16 = red;
    LED17 = blue;
    LED18 = red;
    rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);
    while (1){


        ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
        __bis_SR_register(CPUOFF + GIE); // LPM0, ADC10_ISR will force exit
        if ((ADC10MEM < 0x002A)){

            rgb_set_LEDs(LED7, LED4, LED1, LED8, LED5, LED2, LED9, LED6, LED3, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);//F clockwise

        }
        else if (ADC10MEM > 0x039F){
            rgb_set_LEDs(LED3, LED6, LED9, LED2, LED5, LED8, LED1, LED4, LED7, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

        }
        else

        __bic_SR_register(LPM3_bits + GIE);
    }

}

// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register_on_exit(LPM3_bits); // exit LPM3 when returning to program (clear LPM3 bits)
}
// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register_on_exit(LPM3_bits); // exit LPM3 when returning to program (clear LPM3 bits)
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
}
