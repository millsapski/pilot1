/*
 * EEPROM.c
 *
 *  Created on: Nov 11, 2014
 *      Author: millsapski
 */

#include "EEPROM.h"
#include "main.h"

uint8_t EEPROM_clear(){
	for(int i=0; i<=EEPROM_MAX_ADDRESS; i++){
		i2c_memWriteByte(EEPROM_BUS_ADDRESS, i, 0x11);
		HAL_Delay(20);
	}
	return 0;
}
uint8_t EEPROM_test(){
	//EEPROM_clear();
	for(uint16_t i=0; i<EEPROM_MAX_ADDRESS; i++){
		BSP_LED_Toggle(LED3);
		EEPROM_writeByte(i, 0xFF);
		if(HAL_I2C_GetError(&I2cHandle)!=HAL_I2C_ERROR_NONE){
			BSP_LED_On(LED4);
			//return 0;
		}else{
			BSP_LED_Off(LED4);
		}
	//	i2c_waitReady();
		HAL_Delay(10);
	}
	for(int i=0; i<EEPROM_MAX_ADDRESS; i++){
		uint8_t b = EEPROM_readByte(i);
		if(HAL_I2C_GetError(&I2cHandle)!=HAL_I2C_ERROR_NONE){
			BSP_LED_On(LED4);
					//return 0;
		}
		if(b!=i%255){
			BSP_LED_On(LED5);
			return 0;
		}
	}
	return 1;
}
uint8_t EEPROM_readByte(uint16_t addy){
	return i2c_memReadByte(EEPROM_BUS_ADDRESS, addy);
}
uint8_t EEPROM_writeByte(uint16_t addy, uint8_t data){
	return i2c_memWriteByte(EEPROM_BUS_ADDRESS, addy, data);
}
