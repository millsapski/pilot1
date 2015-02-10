/*
 * EEPROM.h
 *
 *  Created on: Nov 11, 2014
 *      Author: millsapski
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"

#define EEPROM_BUS_ADDRESS 0xa0
#define EEPROM_MAX_ADDRESS 512

uint8_t EEPROM_clear();
uint8_t EEPROM_test();
uint8_t EEPROM_readByte(uint16_t addy);
uint8_t EEPROM_writeByte(uint16_t addy, uint8_t data);

#endif /* EEPROM_H_ */
