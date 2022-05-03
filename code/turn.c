/*
 * implementMove.c
 *
 *  Created on: Apr 10, 2022
 *      Author: anyss
 */

/*
 * in:  check input values
 * out: display face
 */
#include <msp430.h> 

void turn(void) {
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
        else if ((ADC10MEM < 0x002A) && (wait0 == 0) && (ADC10CTL1 == INCH_1)){ //clockwise left turn
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

}
/*
 * shift over leds according to last move input
 *
 * then display faces
 */
