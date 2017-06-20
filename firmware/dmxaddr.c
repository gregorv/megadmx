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

#include <avr/io.h>
#include "dmxaddr.h"

void dmx_addr_init(void)
{
	DMX_ADDR_0_OUT |= (1<<DMX_ADDR_0_PIN);
	DMX_ADDR_1_OUT |= (1<<DMX_ADDR_1_PIN);
	DMX_ADDR_2_OUT |= (1<<DMX_ADDR_2_PIN);
	DMX_ADDR_3_OUT |= (1<<DMX_ADDR_3_PIN);
	DMX_ADDR_4_OUT |= (1<<DMX_ADDR_4_PIN);
}

uint16_t dmx_addr_read(void)
{
	uint16_t addr = 0;
	if((DMX_ADDR_0_IN & (1 << DMX_ADDR_0_PIN)) == 0) addr += 1;
	if((DMX_ADDR_1_IN & (1 << DMX_ADDR_1_PIN)) == 0) addr += 2;
	if((DMX_ADDR_2_IN & (1 << DMX_ADDR_2_PIN)) == 0) addr += 4;
	if((DMX_ADDR_3_IN & (1 << DMX_ADDR_3_PIN)) == 0) addr += 8;
	if((DMX_ADDR_4_IN & (1 << DMX_ADDR_4_PIN)) == 0) addr += 16;
	return addr;
}
