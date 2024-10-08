#include "HardwareSerial.h"
/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Ibus class is inspired by blogposts:
 *   https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 *   http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
 * 
 *  - IMPORTENT!!! - 
 * this class has been modified to fit to the project.
 */

#include "Arduino.h"
#include "ibus.h"

Ibus ibus;

void Ibus::begin(HardwareSerial& serial, uint8_t rx_pin , uint8_t tx_pin)
{
	this->serial = &serial;
	this->serial->begin(IBUS_BAUD_RATE, SERIAL_8N1 ,rx_pin,tx_pin);
	enable();
}

void Ibus::IbusLoop(void *arg)
{
	const uint16_t tickToWait = IBUS_SEND_INTERVAL_MS/portTICK_PERIOD_MS;
	for(;;){
		ibus.sendPacket();
		vTaskDelay(tickToWait);
	}
}

uint8_t * Ibus::createPacket(void) {
  // Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled. Thrown if this is not static!
  static uint8_t packetBytesList[IBUS_PACKET_BYTES_COUNT];
  packetBytesList[0] = 0x20;
  packetBytesList[1] = 0x40;
  uint_fast16_t checksum = 0xFFFF - 0x20 - 0x40;
  for(size_t i = 2; i < (IBUS_CHANNELS_COUNT * 2) + 2; i++) {
    packetBytesList[i] = this->controlValuesList[i - 2];
    checksum -= packetBytesList[i];
  }
  packetBytesList[IBUS_PACKET_BYTES_COUNT - 2] = lowByte(checksum);
  packetBytesList[IBUS_PACKET_BYTES_COUNT - 1] = highByte(checksum);
  return packetBytesList;
}

void Ibus::sendPacket() {
  uint8_t * packetBytesList = this->createPacket();
  for(size_t i = 0; i < IBUS_PACKET_BYTES_COUNT; i++) {
    this->serial->write(packetBytesList[i]);
  }
}

void Ibus::enable() {
	this->isEnabled = true;
	xTaskCreatePinnedToCore(              // create a new Ibus Task to send commands to FC
			Ibus::IbusLoop,
			"IbusLoop",
			1000,
			nullptr,
			IBUS_LOOP_PRIORITY,
			&IbusTaskHandle,
			IBUS_LOOP_CORE
		);
}

void Ibus::disable() {
  	this->isEnabled = false;
	if(IbusTaskHandle != nullptr){   // to prevent self destructing of the task
		vTaskDelete(IbusTaskHandle); // delete the Ibus task to free resources
		IbusTaskHandle = nullptr; 	 // floting pointer to nullptr
	} 								
}

void Ibus::setControlValuesList(uint16_t list[IBUS_CHANNELS_COUNT]) {
  for(size_t i = 0; i < (IBUS_CHANNELS_COUNT); i++)
    setChannel(i,list[i]);
}

void Ibus::setChannel(uint8_t ch , uint16_t val) {
    this->controlValuesList[ch*2] = lowByte(val);
    this->controlValuesList[(ch*2)+1] = highByte(val);
}

uint16_t Ibus::getChannel(uint8_t ch)
{
    return (uint16_t)(controlValuesList[ch*2] | controlValuesList[(ch*2)+1] << 8);
}
