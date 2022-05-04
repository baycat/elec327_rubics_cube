#include <msp430.h>
#include <rgb_interface.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * main.c
 */

void init_wdt(void){
    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO
    WDTCTL = WDT_ADLY_250;    // WDT 16ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}

uint8_t red[] = {0xF0, 10, 0, 0};
uint8_t blue[] = {0xF0, 0, 10, 0};
uint8_t green[] = {0xF0, 0, 0, 10};
uint8_t teal[] = {0xF0, 0, 10, 10};
uint8_t off[] = {0xE0, 0, 0, 0};
// RBG

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    init_wdt();
    rgb_init_spi();

    _enable_interrupts();

    while (1) {
        // initialize temperature values for each LED
        // notice each LED is one step ahead of the one before it
        // initialize variables to hold temperature values for
        //      each LED while LED is off
        int temp1 = 1;
        int t1 = temp1;
        int temp2 = 2;
        int t2 = temp2;
        int temp3 = 3;
        int t3 = temp3;
        int temp4 = 0;
        int t4 = temp4;

        // 4 iteration cycle
        int cycle = 0;
        while (cycle < 4) {
            // each cycle one of the LEDs is turned off, rotates between all four
            // that same LED is incremented
            // when that LED turns on in the next iteration, it will be a different color since it was incremented
            // this loop creates a rotating effect of incrementing color
            if(cycle == 0) {    // cycle is either 0,1,2, or 3; each LED corresponds to one of these
                t4 = temp4 + 4; // increment temperature by 4
                if (t4 > 64) {      // only 64 colors are available so loop around when 64 is reached
                    t4 = t4 - 64;
                }
                temp4 = 0;         // 64 is the temperature for 'off'
            } else if (cycle == 1) {
                t1 = temp1 + 4;
                if (t1 > 64) {
                    t1 = t1 - 64;
                }
                temp1 = 0;
            } else if (cycle == 2) {
                t2 = temp2 + 4;
                if (t2 > 64) {
                    t2 = t2 - 64;
                }
                temp2 = 0;
            } else if (cycle == 3) {
                t3 = temp3 + 4;
                if (t3 > 64) {
                    t3 = t3 - 64;
                }
                temp3 = 0;
            }
            set_temperature(temp1,temp2,temp3,temp4);   // sets color of each LED depending on temperature value
            temp1 = t1; // sets each temperature to next temperature step
            temp2 = t2;
            temp3 = t3;
            temp4 = t4;

            cycle = cycle + 1;  // ensures loop continues
            if (cycle == 4) {
                cycle = 0;
            }
        }
    }

    return 0;
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
