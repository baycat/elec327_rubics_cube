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

uint8_t *LED1copy, *LED2copy, *LED3copy, *LED4copy, *LED6copy, *LED7copy, *LED8copy, *LED9copy,
*LED10copy, *LED11copy, *LED12copy, *LED13copy, *LED15copy, *LED16copy, *LED17copy, *LED18copy,
*LED19copy, *LED20copy, *LED21copy, *LED22copy, *LED24copy, *LED25copy, *LED26copy, *LED27copy,
*LED28copy, *LED29copy, *LED30copy, *LED31copy, *LED33copy, *LED34copy, *LED35copy, *LED36copy,
*LED37copy, *LED38copy, *LED39copy, *LED40copy, *LED42copy, *LED43copy, *LED44copy, *LED45copy,
*LED46copy, *LED47copy, *LED48copy, *LED49copy, *LED51copy, *LED52copy, *LED53copy, *LED54copy;


void init_wdt(void){

    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO
    WDTCTL = WDT_ADLY_16;    // WDT 16ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}

int main(void){
    WDTCTL = WDTPW | WDTHOLD;
    ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_0;//+ CONSEQ_3; // input A7, decrements to A0, sequence of channels //    ADC10CTL1 = INCH_0;
    ADC10AE0 |= BIT0;//BIT7 + BIT6 + BIT5 + BIT3 + BIT1 + BIT0; // PA.0 ADC option select
    P1DIR &= ~(BIT0);//+BIT1+BIT3+BIT5+BIT6+BIT7);
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
    LED10 = white;
    LED11 = white;
    LED12 = white;
    LED13 = white;
    LED14 = white; //top
    LED15 = white;
    LED16 = white;
    LED17 = white;
    LED18 = white;
    LED19 = orange;
    LED20 = orange;
    LED21 = orange;
    LED22 = orange;
    LED23 = orange; //left
    LED24 = orange;
    LED25 = orange;
    LED26 = orange;
    LED27 = orange;
    LED28 = red;
    LED29 = red;
    LED30 = red;
    LED31 = red;
    LED32 = red; //right
    LED33 = red;
    LED34 = red;
    LED35 = red;
    LED36 = red;
    LED37 = yellow;
    LED38 = yellow;
    LED39 = yellow;
    LED40 = yellow;
    LED41 = yellow; //base
    LED42 = yellow;
    LED43 = yellow;
    LED44 = yellow;
    LED45 = yellow;
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
    int wait0 = 0;
    int wait1 = 0;
    int wait3 = 0;
    int wait5 = 0;
    int wait6 = 0;
    int wait7 = 0;
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
        else if ((ADC10MEM < 0x002A) && (wait0 == 0) && (ADC10CTL1 == INCH_1)){ //clockwise top turn

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
            //right top 3 become back top 3
            LED30 = LED54copy;
            LED33 = LED53copy;
            LED36 = LED52copy;
            //front top 3 become right top 3
            LED7 = LED36copy;
            LED8 = LED33copy;
            LED9 = LED30copy;
            //left top 3 become front top 3
            LED19 = LED7copy;
            LED22 = LED8copy;
            LED25 = LED9copy;
            //back top 3 become left top 3
            LED52 = LED19copy;
            LED53 = LED22copy;
            LED54 = LED25copy;

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
        else if ((ADC10MEM > 0x039F) && (wait3 == 0) && (ADC10CTL1 == INCH_3)){ //counterclockwise left turn
            LED19copy = LED19;
            LED20copy = LED20;
            LED21copy = LED21;
            LED22copy = LED22;
            LED24copy = LED24;
            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            //front
            LED3copy = LED3;
            LED6copy = LED6;
            LED9copy = LED9;

            //top
            LED12copy = LED12;
            LED15copy = LED15;
            LED18copy = LED18;

            //base
            LED37copy = LED37;
            LED40copy = LED40;
            LED43copy = LED43;

            //back
            LED46copy = LED46;
            LED49copy = LED49;
            LED52copy = LED52;

            //left shift
            LED19 = LED21copy;
            LED20 = LED24copy;
            LED21 = LED27copy;
            LED22 = LED20copy;
            LED24 = LED26copy;
            LED25 = LED19copy;
            LED26 = LED22copy;
            LED27 = LED25copy;

            //top becomes front
            LED12 = LED3copy;
            LED15 = LED6copy;
            LED18 = LED3copy;

            //back becomes top
            LED46 = LED18copy;
            LED49 = LED15copy;
            LED52 = LED12copy;

            //base becomes back
            LED37 = LED46copy;
            LED40 = LED49copy;
            LED43 = LED52copy;

            //front becomes base
            LED3 = LED43copy;
            LED6 = LED40copy;
            LED9 = LED37copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait3 = 1;
        }
        else if ((ADC10MEM < 0x002A) && (wait3 == 0) && (ADC10CTL1 == INCH_3)){ //clockwise left turn
            LED19copy = LED19;
            LED20copy = LED20;
            LED21copy = LED21;
            LED22copy = LED22;
            LED24copy = LED24;
            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            //front
            LED3copy = LED3;
            LED6copy = LED6;
            LED9copy = LED9;

            //top
            LED12copy = LED12;
            LED15copy = LED15;
            LED18copy = LED18;

            //base
            LED37copy = LED37;
            LED40copy = LED40;
            LED43copy = LED43;

            //back
            LED46copy = LED46;
            LED49copy = LED49;
            LED52copy = LED52;

            //left shift
            LED19 = LED25copy;
            LED20 = LED22copy;
            LED21 = LED19copy;
            LED22 = LED26copy;
            LED24 = LED20copy;
            LED25 = LED27copy;
            LED26 = LED24copy;
            LED27 = LED21copy;

            //top becomes back
            LED12 = LED52copy;
            LED15 = LED49copy;
            LED18 = LED46copy;

            //back becomes base
            LED46 = LED37copy;
            LED49 = LED40copy;
            LED52 = LED43copy;

            //base becomes front
            LED37 = LED9copy;
            LED40 = LED6copy;
            LED43 = LED3copy;

            //front becomes top
            LED3 = LED12copy;
            LED6 = LED15copy;
            LED9 = LED18copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait3 = 1;

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_3)){
            wait3 = 0;
        }

        else if ((ADC10MEM > 0x039F) && (wait3 == 0) && (ADC10CTL1 == INCH_5)){ //counterclockwise right turn
            LED28copy = LED28;
            LED29copy = LED29;
            LED30copy = LED30;
            LED31copy = LED31;
            LED33copy = LED33;
            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //top
            LED10copy = LED10;
            LED13copy = LED13;
            LED16copy = LED16;

            //front
            LED1copy = LED1;
            LED4copy = LED4;
            LED7copy = LED7;

            //back
            LED48copy = LED48;
            LED51copy = LED51;
            LED54copy = LED54;

            //base
            LED39copy = LED39;
            LED42copy = LED42;
            LED45copy = LED45;

            //right shift
            LED28 = LED30copy;
            LED29 = LED33copy;
            LED30 = LED36copy;
            LED31 = LED29copy;
            LED33 = LED35copy;
            LED34 = LED28copy;
            LED35 = LED31copy;
            LED36 = LED36copy;

            //front becomes top
            LED1 = LED10copy;
            LED4 = LED13copy;
            LED7 = LED16copy;

            //top becomes back
            LED10 = LED54copy;
            LED13 = LED51copy;
            LED16 = LED48copy;

            //back becomes base
            LED54 = LED45copy;
            LED51 = LED42copy;
            LED48 = LED39copy;

            //base becomes front
            LED45 = LED1copy;
            LED42 = LED4copy;
            LED39 = LED7copy;
        }
        else if ((ADC10MEM < 0x002A) && (wait5 == 0) && (ADC10CTL1 == INCH_5)){ //clockwise right turn
            LED28copy = LED28;
            LED29copy = LED29;
            LED30copy = LED30;
            LED31copy = LED31;
            LED33copy = LED33;
            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //top
            LED10copy = LED10;
            LED13copy = LED13;
            LED16copy = LED16;

            //front
            LED1copy = LED1;
            LED4copy = LED4;
            LED7copy = LED7;

            //back
            LED48copy = LED48;
            LED51copy = LED51;
            LED54copy = LED54;

            //base
            LED39copy = LED39;
            LED42copy = LED42;
            LED45copy = LED45;

            //right shift
            LED28 = LED34copy;
            LED29 = LED31copy;
            LED30 = LED28copy;
            LED31 = LED35copy;
            LED33 = LED29copy;
            LED34 = LED36copy;
            LED35 = LED33copy;
            LED36 = LED30copy;

            //front becomes base
            LED1 = LED45copy;
            LED4 = LED42copy;
            LED7 = LED39copy;

            //top becomes front
            LED10 = LED1copy;
            LED13 = LED4copy;
            LED16 = LED7copy;

            //back becomes top
            LED54 = LED10copy;
            LED51 = LED13copy;
            LED48 = LED16copy;

            //base becomes back
            LED45 = LED54copy;
            LED42 = LED51copy;
            LED39 = LED48copy;

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_5)){
            wait5 = 0;
        }
        else if ((ADC10MEM > 0x039F) && (wait6 == 0) && (ADC10CTL1 == INCH_6)){ //counterclockwise base turn
            LED37copy = LED37;
            LED38copy = LED38;
            LED39copy = LED39;
            LED40copy = LED40;
            LED42copy = LED42;
            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            //front
            LED1copy = LED1;
            LED2copy = LED2;
            LED3copy = LED3;

            //right
            LED28copy = LED28;
            LED31copy = LED31;
            LED34copy = LED34;

            //left
            LED21copy = LED21;
            LED24copy = LED24;
            LED27copy = LED27;

            //back
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;

            //base shift
            LED37 = LED39copy;
            LED38 = LED42copy;
            LED39 = LED45copy;
            LED40 = LED38copy;
            LED42 = LED44copy;
            LED43 = LED37copy;
            LED44 = LED40copy;
            LED45 = LED43copy;

            //front becomes right
            LED1 = LED34copy;
            LED2 = LED31copy;
            LED3 = LED28copy;

            //right becomes back
            LED28 = LED48copy;
            LED31 = LED47copy;
            LED34 = LED46copy;

            //back becomes left
            LED48 = LED27copy;
            LED47 = LED24copy;
            LED46 = LED21copy;

            //left becomes front
            LED21 = LED1copy;
            LED24 = LED2copy;
            LED27 = LED3copy;

        }
        else if ((ADC10MEM < 0x002A) && (wait5 == 0) && (ADC10CTL1 == INCH_5)){ //clockwise base turn
            LED37copy = LED37;
            LED38copy = LED38;
            LED39copy = LED39;
            LED40copy = LED40;
            LED42copy = LED42;
            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            //front
            LED1copy = LED1;
            LED2copy = LED2;
            LED3copy = LED3;

            //right
            LED28copy = LED28;
            LED31copy = LED31;
            LED34copy = LED34;

            //left
            LED21copy = LED21;
            LED24copy = LED24;
            LED27copy = LED27;

            //back
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;

            //base shift
            LED37 = LED43copy;
            LED38 = LED40copy;
            LED39 = LED37copy;
            LED40 = LED44copy;
            LED42 = LED38copy;
            LED43 = LED45copy;
            LED44 = LED42copy;
            LED45 = LED39copy;

            //front becomes left
            LED1 = LED21copy;
            LED2 = LED24copy;
            LED3 = LED27copy;

            //right becomes front
            LED28 = LED3copy;
            LED31 = LED2copy;
            LED34 = LED1copy;

            //back becomes right
            LED48 = LED28copy;
            LED47 = LED31copy;
            LED46 = LED34copy;

            //left becomes back
            LED21 = LED46copy;
            LED24 = LED47copy;
            LED27 = LED48copy;

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_6)){
            wait6 = 0;
        }
        else if ((ADC10MEM > 0x039F) && (wait7 == 0) && (ADC10CTL1 == INCH_7)){ //counterclockwise back turn
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;
            LED49copy = LED49;
            LED51copy = LED51;
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;

            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //back shift
            LED46 = LED48copy;
            LED47 = LED51copy;
            LED48 = LED54copy;
            LED49 = LED47copy;
            LED51 = LED53copy;
            LED52 = LED46copy;
            LED53 = LED49copy;
            LED54 = LED52copy;

            //right becomes top
            LED36 = LED18copy;
            LED35 = LED17copy;
            LED34 = LED16copy;
            //base becomes right
            LED45 = LED36copy;
            LED44 = LED35copy;
            LED43 = LED34copy;
            //left becomes base
            LED25 = LED43copy;
            LED26 = LED44copy;
            LED27 = LED45copy;
            //top becomes left
            LED16 = LED25copy;
            LED17 = LED26copy;
            LED18 = LED27copy;
        }
        else if ((ADC10MEM < 0x002A) && (wait7 == 0) && (ADC10CTL1 == INCH_7)){ //clockwise back turn
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;
            LED49copy = LED49;
            LED51copy = LED51;
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;

            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //back shift
            LED46 = LED52copy;
            LED47 = LED49copy;
            LED48 = LED46copy;
            LED49 = LED53copy;
            LED51 = LED47copy;
            LED52 = LED54copy;
            LED53 = LED51copy;
            LED54 = LED48copy;

            //right becomes base
            LED36 = LED45copy;
            LED35 = LED44copy;
            LED34 = LED43copy;
            //base becomes left
            LED45 = LED27copy;
            LED44 = LED26copy;
            LED43 = LED25copy;
            //left becomes top
            LED25 = LED16copy;
            LED26 = LED17copy;
            LED27 = LED18copy;
            //top becomes right
            LED16 = LED34copy;
            LED17 = LED35copy;
            LED18 = LED36copy;

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_7)){
            wait7 = 0;
        }

        else{

        }
        ADC10CTL0 &= ~ENC;
        switch(ADC10CTL1){
        case INCH_0:
            ADC10CTL1 = INCH_0;
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
