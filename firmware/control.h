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

#ifndef CONTROL_H
#define CONTROL_H

#define COLOR_LED_RED	PC1
#define COLOR_LED_GREEN	PC2
#define COLOR_LED_BLUE	PC0
#define COLOR_LED_IN	PINC
#define COLOR_LED_OUT	PORTC
#define COLOR_LED_DDR	DDRC

#define STROBE_LED_PIN	PC4
#define STROBE_LED_IN	PINC
#define STROBE_LED_OUT	PORTC
#define STROBE_LED_DDR	DDRC

#define FOG_RELAY_PIN	PD2
#define FOG_RELAY_IN	PIND
#define FOG_RELAY_OUT	PORTD
#define FOG_RELAY_DDR	DDRD

void control_init(void);
void control_ledstrip(uint8_t dimmer, uint8_t red, uint8_t green, uint8_t blue, uint8_t strobe);
void control_strobe(uint8_t strobe);
void control_fog_on(void);
void control_fog_off(void);

#endif
