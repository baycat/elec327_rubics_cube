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

uint8_t *LED1, *LED2, *LED3, *LED4, *LED5, *LED6, *LED7, *LED8, *LED9,
*LED10, *LED11, *LED12, *LED13, *LED14, *LED15, *LED16, *LED17, *LED18,
*LED19, *LED20, *LED21, *LED22, *LED23, *LED24, *LED25, *LED26, *LED27,
*LED28, *LED29, *LED30, *LED31, *LED32, *LED33, *LED34, *LED35, *LED36,
*LED37, *LED38, *LED39, *LED40, *LED41, *LED42, *LED43, *LED44, *LED45,
*LED46, *LED47, *LED48, *LED49, *LED50, *LED51, *LED52, *LED53, *LED54;

uint8_t *LED1copy, *LED2copy, *LED3copy, *LED4copy, *LED5copy, *LED6copy, *LED7copy, *LED8copy, *LED9copy,
*LED10copy, *LED11copy, *LED12copy, *LED13copy, *LED14copy, *LED15copy, *LED16copy, *LED17copy, *LED18copy,
*LED19copy, *LED20copy, *LED21copy, *LED22copy, *LED23copy, *LED24copy, *LED25copy, *LED26copy, *LED27copy,
*LED28copy, *LED29copy, *LED30copy, *LED31copy, *LED32copy, *LED33copy, *LED34copy, *LED35copy, *LED36copy,
*LED37copy, *LED38copy, *LED39copy, *LED40copy, *LED41copy, *LED42copy, *LED43copy, *LED44copy, *LED45copy,
*LED46copy, *LED47copy, *LED48copy, *LED49copy, *LED50copy, *LED51copy, *LED52copy, *LED53copy, *LED54copy;


void init_wdt(void){

    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO
    WDTCTL = WDT_ADLY_16;    // WDT 16ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}

int main(void){
    WDTCTL = WDTPW | WDTHOLD;
    ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_0;//+ CONSEQ_3; // input A7, decrements to A0, sequence of channels //    ADC10CTL1 = INCH_0;
    ADC10AE0 |= BIT7 + BIT6 + BIT5 + BIT3 + BIT1 + BIT0; // PA.0 ADC option select
    P1DIR &= ~BIT0;
    BCSCTL3 |= LFXT1S_2;
    init_wdt();

    rgb_init_spi();

    TA0CTL = TASSEL_1 + MC_1;     // ACLK, upmode
    TA0CCR0 = 20;              // Interrupt should happen every ~12 kHz / 12000
    TA0CCTL0 = CCIE;              // CCR0 interrupt enabled

    _enable_interrupts();

    LED1 = green;
    LED2 = green;
    LED3 = green;
    LED4 = green;
    LED5 = green; //front
    LED6 = green;
    LED7 = green;
    LED8 = green;
    LED9 = green;
    LED10 = orange;
    LED11 = orange;
    LED12 = orange;
    LED13 = orange;
    LED14 = orange; //top
    LED15 = orange;
    LED16 = orange;
    LED17 = orange;
    LED18 = orange;
    LED19 = green;
    LED20 = white;
    LED21 = white;
    LED22 = green;
    LED23 = white; //left
    LED24 = white;
    LED25 = green;
    LED26 = white;
    LED27 = white;
    LED28 = yellow;
    LED29 = yellow;
    LED30 = yellow;
    LED31 = yellow;
    LED32 = yellow; //right
    LED33 = yellow;
    LED34 = yellow;
    LED35 = yellow;
    LED36 = yellow;
    LED37 = red;
    LED38 = red;
    LED39 = red;
    LED40 = red;
    LED41 = red; //base
    LED42 = red;
    LED43 = red;
    LED44 = red;
    LED45 = red;
    LED46 = blue;
    LED47 = blue;
    LED48 = blue;
    LED49 = blue;
    LED50 = blue; //back
    LED51 = blue;
    LED52 = blue;
    LED53 = blue;
    LED54 = blue;
    // note: base of each board faces touches main face board, back board same orientation as face board
    rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                 LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                 LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                 LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                 LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                 LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
    int wait0 = 1;
    int wait1 = 1;
    while (1){

        //ADC10CTL0 &= ~ENC;
        //while (ADC10CTL1 & BUSY);
        ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
        __bis_SR_register(CPUOFF + GIE); // LPM0, ADC10_ISR will force exit
        if ((ADC10MEM > 0x039F) && (wait0 == 0) && (ADC10CTL1 == INCH_0)){ //counterclockwise face turn

            //front
             LED1copy = LED1;
             LED2copy = LED2;
             LED3copy = LED3;
             LED4copy = LED4;
             LED6copy = LED6;
             LED7copy = LED7;
             LED8copy = LED8;
             LED9copy = LED9;
             //top
             LED10copy = LED10;
             LED11copy = LED11;
             LED12copy = LED12;
             //left
             LED19copy = LED19;
             LED20copy = LED20;
             LED21copy = LED21;
             //right
             LED28copy = LED28;
             LED29copy = LED29;
             LED30copy = LED30;
             //base
             LED37copy = LED37;
             LED38copy = LED38;
             LED39copy = LED39;

             //face shift
             LED1 = LED7copy;
             LED2 = LED4copy;
             LED3 = LED1copy;
             LED4 = LED8copy;
             LED6 = LED2copy;
             LED7 = LED9copy;
             LED8 = LED6copy;
             LED9 = LED3copy;
             //top front 3 become right front 3
             LED10 = LED28copy;
             LED11 = LED29copy;
             LED12 = LED30copy;
             //left front 3 become top front 3
             LED19 = LED10copy;
             LED20 = LED11copy;
             LED21 = LED12copy;
             //base front 3 become left front 3
             LED37 = LED19copy;
             LED38 = LED20copy;
             LED39 = LED21copy;
             //right front 3 become base front 3
             LED28 = LED37copy;
             LED29 = LED38copy;
             LED30 = LED39copy;

             rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                                          LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                                          LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                                          LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                                          LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                                          LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);

            wait0 = 1;
            //rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

        }
        else if ((ADC10MEM < 0x002A) && (wait0 == 0) && (ADC10CTL1 == INCH_0)){ //clockwise face turn
                LED1copy = LED1;
                LED2copy = LED2;
                LED3copy = LED3;
                LED4copy = LED4;
                LED6copy = LED6;
                LED7copy = LED7;
                LED8copy = LED8;
                LED9copy = LED9;

                //top
                LED10copy = LED10;
                LED11copy = LED11;
                LED12copy = LED12;
                //left
                LED19copy = LED19;
                LED20copy = LED20;
                LED21copy = LED21;
                //right
                LED28copy = LED28;
                LED29copy = LED29;
                LED30copy = LED30;
                //base
                LED37copy = LED37;
                LED38copy = LED38;
                LED39copy = LED39;

                //rgb_set_LEDs(LED3, LED6, LED9, LED2, LED5, LED8, LED1, LED4, LED7, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

                LED1 = LED3copy;
                LED2 = LED6copy;
                LED3 = LED9copy;
                LED4 = LED2copy;
                LED6 = LED8copy;
                LED7 = LED1copy;
                LED8 = LED4copy;
                LED9 = LED7copy;

                //top front 3 become left front 3
                LED10 = LED19copy;
                LED11 = LED20copy;
                LED12 = LED21copy;
                //left front 3 become base front 3
                LED19 = LED37copy;
                LED20 = LED38copy;
                LED21 = LED39copy;
                //base front 3 become right front 3
                LED37 = LED28copy;
                LED38 = LED29copy;
                LED39 = LED30copy;
                //right front 3 become top front 3
                LED28 = LED10copy;
                LED29 = LED11copy;
                LED30 = LED12copy;
                rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                             LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                             LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                             LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                             LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                             LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait0 = 1;
            //rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_0)){
            wait0 = 0;
        }
        else if ((ADC10MEM > 0x039F) && (wait1 == 0) && (ADC10CTL1 == INCH_1)){ //counterclockwise top turn
            //top
            LED10copy = LED10;
            LED11copy = LED11;
            LED12copy = LED12;
            LED13copy = LED13;
            LED15copy = LED15;
            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;
            //face
            LED7copy = LED7;
            LED8copy = LED8;
            LED9copy = LED9;
            //left
            LED19copy = LED19;
            LED22copy = LED22;
            LED25copy = LED25;
            //right
            LED30copy = LED30;
            LED33copy = LED33;
            LED36copy = LED36;
            //back
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            //top shift
            LED10 = LED12copy;
            LED11 = LED15copy;
            LED12 = LED18copy;
            LED13 = LED11copy;
            LED15 = LED17copy;
            LED16 = LED10copy;
            LED17 = LED13copy;
            LED18 = LED16copy;
            //right top 3 become front top 3
            LED30 = LED9copy;
            LED33 = LED8copy;
            LED36 = LED7copy;
            //front top 3 become left top 3
            LED7 = LED19copy;
            LED8 = LED22copy;
            LED9 = LED25copy;
            //left top 3 become back top 3
            LED19 = LED52copy;
            LED22 = LED53copy;
            LED25 = LED54copy;
            //back top 3 become right top 3
            LED52 = LED36copy;
            LED53 = LED33copy;
            LED54 = LED30copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait1 = 1;
        }
        else if ((ADC10MEM < 0x002A) && (wait0 == 0) && (ADC10CTL1 == INCH_1)){

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait1 = 1;
        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_1)){
            wait1 = 0;
        }
        else{

        }
        ADC10CTL0 &= ~ENC;
        switch(ADC10CTL1){
        case INCH_0:
            ADC10CTL1 = INCH_1;
            break;
        case INCH_1:
            ADC10CTL1 = INCH_3;
            break;
        case INCH_3:
            ADC10CTL1 = INCH_5;
            break;
        case INCH_5:
            ADC10CTL1 = INCH_6;
            break;
        case INCH_6:
            ADC10CTL1 = INCH_7;
            break;
        case INCH_7:
            ADC10CTL1 = INCH_0;
            break;

        }
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
