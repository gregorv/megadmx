/*  MegaDMX – Atmega DMX firmware for Toilet-Control
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
#include "main.h"
#include <util/delay.h>
#include <avr/wdt.h>
#include <util/setbaud.h>

void test(void);
void test_strobe(void);

void greetingFlash(void);

#define CHANNEL_COUNT 7

int main(void)
{
	wdt_enable(WDTO_1S);
	SIGNAL_LED_DDR |= (1 << SIGNAL_LED_PIN);
	greetingFlash();
	// test_strobe();
	// while(1) test();
	uart_init(UART_BAUD_SELECT(BAUD, F_CPU));
	dmx_addr_init();
	control_init();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
	uint16_t current_dmx_channel = 0;
	uint8_t package[CHANNEL_COUNT];
	for(;;) {
		unsigned int recvData = uart_getc();
		uint8_t data = (uint8_t)recvData;
		uint16_t dmx_addr = dmx_addr_read() + 1; // start frame
		if((recvData & UART_FRAME_ERROR) == UART_FRAME_ERROR) {
			current_dmx_channel = 0;
			SIGNAL_LED_TOGGLE;
		} else if((recvData & UART_BUFFER_OVERFLOW) ||
		          (recvData & UART_OVERRUN_ERROR)) {
			while(1) {}
		} else if(recvData & UART_NO_DATA) {
		} else {
			if(current_dmx_channel >= dmx_addr &&
			   current_dmx_channel < dmx_addr+CHANNEL_COUNT) {
				package[current_dmx_channel - dmx_addr] = data;
				if(current_dmx_channel == dmx_addr + CHANNEL_COUNT - 1) {
					control_ledstrip(package[0], package[1], package[2], package[3], package[4]);
					control_strobe(package[5]);
					if(package[6] > 127) {
						control_fog_on();
					} else {
						control_fog_off();
					}
				}
			}
			++current_dmx_channel;
		}
		wdt_reset();
	}
	return 0;
}

void greetingFlash(void)
{
	for(char i = 0; i < 5; ++i) {
		SIGNAL_LED_ON;
		_delay_ms(50);
	
		SIGNAL_LED_OFF;
		_delay_ms(50);
	}
}

void test(void)
{
	COLOR_LED_DDR |= (1 << COLOR_LED_RED);
	COLOR_LED_DDR |= (1 << COLOR_LED_GREEN);
	COLOR_LED_DDR |= (1 << COLOR_LED_BLUE);
	STROBE_LED_DDR |= (1 << STROBE_LED_PIN);
	FOG_RELAY_DDR |= (1 << FOG_RELAY_PIN);
	SIGNAL_LED_DDR |= (1 << SIGNAL_LED_PIN);

	COLOR_LED_OUT &= ~((1 << COLOR_LED_RED) | (1 << COLOR_LED_GREEN) | (1 << COLOR_LED_BLUE));
	FOG_RELAY_OUT &= ~(1 << FOG_RELAY_PIN);
	STROBE_LED_OUT |= (1 << STROBE_LED_PIN);
	SIGNAL_LED_OUT &= ~(1 << SIGNAL_LED_PIN);

	int time = 200;

	_delay_ms(time); wdt_reset();
	COLOR_LED_OUT |= (1 << COLOR_LED_RED);

	_delay_ms(time); wdt_reset();
	COLOR_LED_OUT |= (1 << COLOR_LED_GREEN);

	_delay_ms(time); wdt_reset();
	COLOR_LED_OUT |= (1 << COLOR_LED_BLUE);

	_delay_ms(time); wdt_reset();
	SIGNAL_LED_OUT |= (1 << SIGNAL_LED_PIN);

	_delay_ms(time); wdt_reset();
	FOG_RELAY_OUT |= (1 << FOG_RELAY_PIN);

	_delay_ms(time); wdt_reset();
	STROBE_LED_OUT &= ~(1 << STROBE_LED_PIN);
	_delay_ms(10); wdt_reset();
}

void test_strobe(void)
{
	STROBE_LED_OUT |= (1 << STROBE_LED_PIN);
	while(1) {
		_delay_ms(30); wdt_reset();
		STROBE_LED_OUT &= ~(1 << STROBE_LED_PIN);
		_delay_ms(15);
		STROBE_LED_OUT |= (1 << STROBE_LED_PIN);
	}
}

