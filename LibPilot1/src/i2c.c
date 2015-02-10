
#include "i2c.h"
#include "stm32f4_discovery.h"

uint8_t i2c_init(){
	I2cHandle.Instance             = I2Cx;
	  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	  I2cHandle.Init.ClockSpeed      = 400000; //400000
	  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
	  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;
	  I2cHandle.Init.OwnAddress1     = 0x00;
	  I2cHandle.Init.OwnAddress2     = 0xFE;

	  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    return 0;
	  }
	  return 1;
}

uint8_t i2c_memWriteByte(uint16_t device, uint16_t address, uint16_t data){
	I2cReady = 0;
	uint8_t dArr[]={data};
	HAL_I2C_Mem_Write_IT(&I2cHandle, device, address, 16, (uint8_t*)dArr, 1);
	while(I2cReady==0){

	}

	if (HAL_I2C_GetError(&I2cHandle)!=HAL_I2C_ERROR_NONE){
		return 0;
	}
	return 1;
}

uint8_t i2c_memReadByte(uint16_t device, uint16_t address){
	I2cReady = 0;
	uint8_t dArr[1];
	HAL_I2C_Mem_Read_IT(&I2cHandle, device, address, 16, (uint8_t*)dArr, 1);
	i2c_waitReady();
	return dArr[0];
}

void i2c_waitReady(){
	while(HAL_I2C_GetState(&I2cHandle)!=HAL_I2C_STATE_READY && I2cHandle.Lock != HAL_UNLOCKED && I2cReady == 0){
		BSP_LED_On(LED4);
	}
	BSP_LED_Off(LED4);
}


///callback functions
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
	I2cReady = 1;
}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	I2cReady = 1;
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2cHandle){
  I2cReady=1;
}
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle){
  I2cReady=1;
}
