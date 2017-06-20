/*  MegaDMX – ATmega8 DMX Firmware for Toilet-Control
    Copyright (C) 2017 Gregor Vollmer <git@dynamic-noise.net>

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
#ifndef DMX_ADDR_H
#define DMX_ADDR_H

void dmx_addr_init(void);
uint16_t dmx_addr_read(void);

/* DMX Address Pins */
#define DMX_ADDR_4_PIN	PB2
#define DMX_ADDR_4_IN	PINB
#define DMX_ADDR_4_OUT	PORTB
#define DMX_ADDR_4_DDR	DDRB

#define DMX_ADDR_3_PIN	PB1
#define DMX_ADDR_3_IN	PINB
#define DMX_ADDR_3_OUT	PORTB
#define DMX_ADDR_3_DDR	DDRB

#define DMX_ADDR_2_PIN	PB0
#define DMX_ADDR_2_IN	PINB
#define DMX_ADDR_2_OUT	PORTB
#define DMX_ADDR_2_DDR	DDRB

#define DMX_ADDR_1_PIN	PD7
#define DMX_ADDR_1_IN	PIND
#define DMX_ADDR_1_OUT	PORTD
#define DMX_ADDR_1_DDR	DDRD

#define DMX_ADDR_0_PIN	PD6
#define DMX_ADDR_0_IN	PIND
#define DMX_ADDR_0_OUT	PORTD
#define DMX_ADDR_0_DDR	DDRD

#endif
