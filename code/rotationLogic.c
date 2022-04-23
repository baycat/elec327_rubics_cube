/*
 * rotationLogic.c
 *
 *  Created on: 19 Apr. 2022
 *      Author: elliotmetcalf
 */
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "LEDinterface.h"

 uint8_t *LED1copy, *LED2copy, *LED3copy, *LED4copy, *LED5copy, *LED6copy, *LED7copy, *LED8copy, *LED9copy, *LED10copy, *LED11copy, *LED12copy, *LED13copy, *LED14copy, *LED15copy, *LED16copy, *LED17copy, *LED18copy;


//void clockwisefaceturn(const uint8_t *LED1,const uint8_t *LED2, const uint8_t *LED3, const uint8_t *LED4, const uint8_t *LED5, const uint8_t *LED6, const uint8_t *LED7, const uint8_t *LED8, const uint8_t *LED9, const uint8_t *LED10, const uint8_t *LED11,const uint8_t *LED12, const uint8_t *LED13, const uint8_t *LED14, const uint8_t *LED15, const uint8_t *LED16, const uint8_t *LED17, const uint8_t *LED18){
 void counterclockwisefaceturn(uint8_t *LED1, uint8_t *LED2, uint8_t *LED3, uint8_t *LED4, uint8_t *LED5, uint8_t *LED6, uint8_t *LED7, uint8_t *LED8, uint8_t *LED9, uint8_t *LED10, uint8_t *LED11, uint8_t *LED12, uint8_t *LED13, uint8_t *LED14, uint8_t *LED15, uint8_t *LED16, uint8_t *LED17, uint8_t *LED18){

    LED1copy = LED1;
    LED2copy = LED2;
    LED3copy = LED3;
    LED4copy = LED4;
    LED6copy = LED6;
    LED7copy = LED7;
    LED8copy = LED8;
    LED9copy = LED9;

    //rgb_set_LEDs(LED7, LED4, LED1, LED8, LED5, LED2, LED9, LED6, LED3, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);//F clockwise

    LED1 = LED7copy;
    LED2 = LED4copy;
    LED3 = LED1copy;
    LED4 = LED8copy;
    LED6 = LED2copy;
    LED7 = LED9copy;
    LED8 = LED6copy;
    LED9 = LED3copy;
    rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);


}

void clockwisefaceturn(uint8_t *LED1, uint8_t *LED2, uint8_t *LED3, uint8_t *LED4, uint8_t *LED5, uint8_t *LED6, uint8_t *LED7, uint8_t *LED8, uint8_t *LED9, uint8_t *LED10, uint8_t *LED11, uint8_t *LED12, uint8_t *LED13, uint8_t *LED14, uint8_t *LED15, uint8_t *LED16, uint8_t *LED17, uint8_t *LED18){

    LED1copy = LED1;
    LED2copy = LED2;
    LED3copy = LED3;
    LED4copy = LED4;
    LED6copy = LED6;
    LED7copy = LED7;
    LED8copy = LED8;
    LED9copy = LED9;

    //rgb_set_LEDs(LED3, LED6, LED9, LED2, LED5, LED8, LED1, LED4, LED7, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

    LED1 = LED3copy;
    LED2 = LED6copy;
    LED3 = LED9copy;
    LED4 = LED2copy;
    LED6 = LED8copy;
    LED7 = LED1copy;
    LED8 = LED4copy;
    LED9 = LED7copy;
    rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);


}
