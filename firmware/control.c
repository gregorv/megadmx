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
#include <avr/interrupt.h>
#include "control.h"

#define STROBE_OFF STROBE_LED_OUT |= (1 << STROBE_LED_PIN)
#define STROBE_ON STROBE_LED_OUT &= ~(1 << STROBE_LED_PIN)

struct rgb_dimmer_t {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t phase;
};

struct strobe_t {
	uint8_t dimmer;
	uint8_t power;
	uint8_t phase_dimmer;
	uint8_t phase_power;
};

volatile struct rgb_dimmer_t g_dimmer;
volatile struct strobe_t g_strobe;

void control_stop_dimmer(void);
void control_start_dimmer(void);

void control_init(void)
{
	COLOR_LED_DDR |= (1 << COLOR_LED_RED);
	COLOR_LED_DDR |= (1 << COLOR_LED_GREEN);
	COLOR_LED_DDR |= (1 << COLOR_LED_BLUE);
	STROBE_LED_DDR |= (1 << STROBE_LED_PIN);
	FOG_RELAY_DDR |= (1 << FOG_RELAY_PIN);
	STROBE_OFF;

	TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00); // f_cpu / 1
	TIMSK0 |= (1 << TOIE0); // timer overflow interrupt enable

	TCCR2A = (1 << WGM21); // CTC Mode
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // f_cpu / 1024
	OCR2A = 195; // ~100 Hz
	TIMSK2 |= (1 << OCIE2A); // CTC match interrupt enable
}

void control_ledstrip(uint8_t dimmer, uint8_t red, uint8_t green, uint8_t blue, uint8_t strobe)
{
	cli();
	g_dimmer.red = (uint8_t)(((uint32_t)dimmer * (uint32_t)red) >> 8);
	g_dimmer.green = (uint8_t)(((uint32_t)dimmer * (uint32_t)green) >> 8);
	g_dimmer.blue = (uint8_t)(((uint32_t)dimmer * (uint32_t)blue) >> 8);
	if(strobe == 0) {
		g_strobe.dimmer = 0;
		control_start_dimmer();
	} else {
		strobe >>= 1;
		strobe = 3 + (127 - strobe);
		if(g_strobe.dimmer != strobe) {
			if(g_strobe.dimmer == 0) {
				g_strobe.phase_dimmer = 1;
			}
			g_strobe.dimmer = strobe;
		}
	}
	sei();
}

void control_strobe(uint8_t frequency)
{
	if(frequency == 0) {
		g_strobe.power = 0;
		STROBE_OFF;
	} else {
		frequency >>= 1;
		frequency = 3 + (127 - frequency);
		if(g_strobe.power != frequency) {
			if(g_strobe.power == 0) {
				g_strobe.phase_power = 1;
			}
			g_strobe.power = frequency;
		}
	}
}

void control_fog_on(void)
{
	FOG_RELAY_OUT |= (1 << FOG_RELAY_PIN);
}

void control_fog_off(void)
{
	FOG_RELAY_OUT &= ~(1 << FOG_RELAY_PIN);
}

void control_start_dimmer(void)
{
	g_dimmer.phase = 0;
	TIMSK0 |= (1 << TOIE0); // timer overflow interrupt enable
}

void control_stop_dimmer(void)
{
	COLOR_LED_OUT &= ~((1 << COLOR_LED_RED) | (1 << COLOR_LED_GREEN) | (1 << COLOR_LED_BLUE));
	TIMSK0 &= ~(1 << TOIE0); // timer overflow interrupt enable
}

ISR (TIMER0_OVF_vect)
{
	if(g_dimmer.phase == 0) {
		if(g_dimmer.red) {
			COLOR_LED_OUT |= (1 << COLOR_LED_RED);
		} else {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_RED);
		}
		if(g_dimmer.green) {
			COLOR_LED_OUT |= (1 << COLOR_LED_GREEN);
		} else {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_GREEN);
		}
		if(g_dimmer.blue) {
			COLOR_LED_OUT |= (1 << COLOR_LED_BLUE);
		} else {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_BLUE);
		}
	} else {
		if(g_dimmer.phase == g_dimmer.red) {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_RED);
		}
		if(g_dimmer.phase == g_dimmer.green) {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_GREEN);
		}
		if(g_dimmer.phase == g_dimmer.blue) {
			COLOR_LED_OUT &= ~(1 << COLOR_LED_BLUE);
		}
	}
	++g_dimmer.phase;
}

ISR(TIMER2_COMPA_vect)
{
	if(g_strobe.power) {
		--g_strobe.phase_power;
		if(g_strobe.phase_power == 0) {
			STROBE_ON;
			g_strobe.phase_power = g_strobe.power;
		} else {
			STROBE_OFF;
		}
	}
	if(g_strobe.dimmer) {
		--g_strobe.phase_dimmer;
		if(g_strobe.phase_dimmer == 0) {
			g_strobe.phase_dimmer = g_strobe.dimmer;
			control_start_dimmer();
		} else {
			control_stop_dimmer();
		}
	}
}
