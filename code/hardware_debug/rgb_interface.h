/*
 * rgb_interface.h
 *
 *  Created on: Mar 12, 2021
 *      Author: ckemere
 */

#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>


void rgb_init_spi(void);
void rgb_send_frame(const uint8_t *frame1, bool wait_for_completion);
void rgb_send_start();
void rgb_send_end();

void set_temperature(int LED1_temp, int LED2_temp, int LED3_temp, int LED4_temp);

#endif /* RGB_INTERFACE_H_ */
