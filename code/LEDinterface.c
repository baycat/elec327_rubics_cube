/*
 * LEDinterface.c
 *
 *  Created on: 18 Apr. 2022
 *      Author: elliotmetcalf
 */

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "LEDinterface.h"

uint8_t start_frame[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t end_frame[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void rgb_init_spi(void){
    //COPI on p1.2, SCLK on p1.4
    P1SEL = BIT2 + BIT4;
    P1SEL2 = BIT2 + BIT4;

    UCA0CTL1=UCSWRST; //disable serial interface
    UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;    // data cap at 1st clk edge, MSB first, master mode, synchronous
    UCA0CTL1 |= UCSSEL_2;                           // select SMCLK
    UCA0BR0 = 0;                                    //set frequency
    UCA0BR1 = 0;                                    //
    UCA0CTL1 &= ~UCSWRST;           // Initialize USCI state machine

}
//writes a 32 bit frame to the spi buffer
void rgb_send_frame(const uint8_t *frame1, bool wait_for_completion){
    int byte1;
    for (byte1=0;byte1<4;byte1++){//send 72 bit frame in 8 bit chunks
        UCA0TXBUF=frame1[byte1];
        while (!(IFG2 & UCA0TXIFG));  // USCI_A0 TX buffer ready?
    }
    if (wait_for_completion)
        while (!(IFG2 & UCA0RXIFG));  // USCI_A0 RX buffer ready? (indicates transfer complete)
}

void rgb_send_start() {
    rgb_send_frame(start_frame, false);
}

void rgb_send_end() {
    rgb_send_frame(end_frame, true);
}

void rgb_set_LEDs(const uint8_t *LED1,const uint8_t *LED2, const uint8_t *LED3, const uint8_t *LED4, const uint8_t *LED5, const uint8_t *LED6, const uint8_t *LED7, const uint8_t *LED8, const uint8_t *LED9, const uint8_t *LED10, const uint8_t *LED11,const uint8_t *LED12, const uint8_t *LED13, const uint8_t *LED14, const uint8_t *LED15, const uint8_t *LED16, const uint8_t *LED17, const uint8_t *LED18) {
    rgb_send_start();
    rgb_send_frame(LED1, false);
    rgb_send_frame(LED2, false);
    rgb_send_frame(LED3, false);
    rgb_send_frame(LED4, false);
    rgb_send_frame(LED5, false);
    rgb_send_frame(LED6, false);
    rgb_send_frame(LED7, false);
    rgb_send_frame(LED8, false);
    rgb_send_frame(LED9, false);
    rgb_send_frame(LED10, false);
    rgb_send_frame(LED11, false);
    rgb_send_frame(LED12, false);
    rgb_send_frame(LED13, false);
    rgb_send_frame(LED14, false);
    rgb_send_frame(LED15, false);
    rgb_send_frame(LED16, false);
    rgb_send_frame(LED17, false);
    rgb_send_frame(LED18, false);
    rgb_send_end();
}
