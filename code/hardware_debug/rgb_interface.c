/*
 * rgb_interface.c
 *
 *  Created on: Mar 12, 2021
 *      Author: ckemere
 */


#include <rgb_interface.h>


uint8_t start_frame[] = {0,0,0,0,0,0};
uint8_t end_frame[] = {0xFF,0xFF,0xFF,0xFF,0xFF};

// this array contains the RBG information for each of 64 possible temperatures, the 0th element is the 'off' state
uint8_t temp2rbg[65][5] = {{0xE0, 0, 0, 0}, // off
                           {0xF0,20,0,0},{0xF0,20,1,0},{0xF0,20,3,0},{0xF0,20,5,0},
                           {0xF0,20,7,0},{0xF0,20,9,0},{0xF0,20,11,0},{0xF0,20,12,0},
                           {0xF0,20,14,0},{0xF0,20,16,0},{0xF0,20,18,0},{0xF0,19,19,0},
                           {0xF0,17,20,0},{0xF0,15,20,0},{0xF0,14,20,0},{0xF0,12,20,0},
                           {0xF0,9,20,0},{0xF0,8,20,0},{0xF0,6,20,0},{0xF0,4,20,0},
                           {0xF0,2,20,0},{0xF0,0,20,0},{0xF0,0,20,1},{0xF0,0,20,3},
                           {0xF0,0,20,4},{0xF0,0,20,6},{0xF0,0,20,8},{0xF0,0,20,10},
                           {0xF0,0,20,12},{0xF0,0,20,14},{0xF0,0,20,16},{0xF0,0,20,17},
                           {0xF0,0,19,20},{0xF0,0,17,20},{0xF0,0,16,20},{0xF0,0,14,20},
                           {0xF0,0,12,20},{0xF0,0,10,20},{0xF0,0,8,20},{0xF0,0,6,20},
                           {0xF0,0,4,20},{0xF0,0,3,20},{0xF0,0,1,20},{0xF0,0,0,20},
                           {0xF0,2,0,20},{0xF0,4,0,20},{0xF0,6,0,20},{0xF0,8,0,20},
                           {0xF0,10,0,20},{0xF0,12,0,20},{0xF0,14,0,20},{0xF0,15,0,20},
                           {0xF0,17,0,20},{0xF0,19,0,19},{0xF0,20,0,18},{0xF0,20,0,16},
                           {0xF0,20,0,14},{0xF0,20,0,12},{0xF0,20,0,11},{0xF0,20,0,9},
                           {0xF0,20,0,7},{0xF0,20,0,5},{0xF0,20,0,3},{0xF0,20,0,1}};
uint8_t thisone[65][5] = {{0xE0, 0, 0, 0}, // off
                           {0xF0,20,0,0},{0xF0,20,1,0},{0xF0,20,3,0},{0xF0,20,5,0},
                           {0xF0,20,7,0},{0xF0,20,9,0},{0xF0,20,11,0},{0xF0,20,12,0},
                           {0xF0,20,14,0},{0xF0,20,16,0},{0xF0,20,18,0},{0xF0,19,19,0},
                           {0xF0,17,20,0},{0xF0,15,20,0},{0xF0,14,20,0},{0xF0,12,20,0},
                           {0xF0,9,20,0},{0xF0,8,20,0},{0xF0,6,20,0},{0xF0,4,20,0},
                           {0xF0,2,20,0},{0xF0,0,20,0},{0xF0,0,20,1},{0xF0,0,20,3},
                           {0xF0,0,20,4},{0xF0,0,20,6},{0xF0,0,20,8},{0xF0,0,20,10},
                           {0xF0,0,20,12},{0xF0,0,20,14},{0xF0,0,20,16},{0xF0,0,20,17},
                           {0xF0,0,19,20},{0xF0,0,17,20},{0xF0,0,16,20},{0xF0,0,14,20},
                           {0xF0,0,12,20},{0xF0,0,10,20},{0xF0,0,8,20},{0xF0,0,6,20},
                           {0xF0,0,4,20},{0xF0,0,3,20},{0xF0,0,1,20},{0xF0,0,0,20},
                           {0xF0,2,0,20},{0xF0,4,0,20},{0xF0,6,0,20},{0xF0,8,0,20},
                           {0xF0,10,0,20},{0xF0,12,0,20},{0xF0,14,0,20},{0xF0,15,0,20},
                           {0xF0,17,0,20},{0xF0,19,0,19},{0xF0,20,0,18},{0xF0,20,0,16},
                           {0xF0,20,0,14},{0xF0,20,0,12},{0xF0,20,0,11},{0xF0,20,0,9},
                           {0xF0,20,0,7},{0xF0,20,0,5},{0xF0,20,0,3},{0xF0,20,0,1}};

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
    for (byte1=0;byte1<4;byte1++){//send 32 bit frame in 8 bit chunks
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

// this function sets the color of each LED given temperature values, the temp2rbg table is given above
void set_temperature(int LED1_temp, int LED2_temp, int LED3_temp, int LED4_temp){
    // initialize array for each RBG
    uint8_t led1[4];
    uint8_t led2[4];
    uint8_t led3[4];
    uint8_t led4[4];
    // set RBG values using corresponding temperature value with temp2rbg table
    memcpy(led1, temp2rbg[LED1_temp], 4);
    memcpy(led2, temp2rbg[LED2_temp], 4);
    memcpy(led3, temp2rbg[LED3_temp], 4);
    memcpy(led4, temp2rbg[LED4_temp], 4);
    // send start frame, color frame for each LED, and end frame
    rgb_send_start();
    rgb_send_frame(&led1, false);
    rgb_send_frame(&led2, false);
    rgb_send_frame(&led3, false);
    rgb_send_frame(&led4, false);
    rgb_send_frame(&led4, false);
    rgb_send_frame(&led4, false);
    rgb_send_frame(&led4, false);
    rgb_send_frame(&led4, false);
    rgb_send_frame(&led4, false);
    rgb_send_end();
    LPM3;
}
