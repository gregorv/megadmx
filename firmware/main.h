/*  Sousvide-Temperature Controller Firmware
    Copyright (C) 2016 Gregor Vollmer <git@dynamic-noise.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


#define SIGNAL_LED_OUT PORTC
#define SIGNAL_LED_PIN PC5
#define SIGNAL_LED_DDR DDRC
#define SIGNAL_LED_ON SIGNAL_LED_OUT |= (1 << SIGNAL_LED_PIN)
#define SIGNAL_LED_OFF SIGNAL_LED_OUT &= ~(1 << SIGNAL_LED_PIN)
#define SIGNAL_LED_TOGGLE SIGNAL_LED_OUT ^= (1 << SIGNAL_LED_PIN)

#define UART_PORT PORTB
#define UART_PORT_PIN PB1
#define UART_PORT_DDR DDRB

#define BAUD_TOL 1
#define BAUD 250000UL

#define UART_TX_BUFFER_SIZE 16
#define UART_RX_BUFFER_SIZE 128

#include "uart.h"
#include "dmxaddr.h"
#include "control.h"

#endif//MAIN_H
