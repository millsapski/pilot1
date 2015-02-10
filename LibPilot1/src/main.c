/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "EEPROM.h"
#include "uart.h"


#define I2C_ADDRESS        0x30F

/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = "!*";

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];

uint8_t read[4];
uint8_t firstRead;
uint8_t data[]={0xDE, 0xAD, 0xBE, 0xEF};

/* Private function prototypes -----------------------------------------------*/

static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{    
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  
  /* Configure LED4, LED6 and LED5 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED6);
  BSP_LED_Init(LED5);

  /* Configure the system clock to 168 Mhz */
  configure_system_clock();

  if(uart_init())
  	  BSP_LED_On(LED3);
    else
  	  BSP_LED_On(LED6);

  if(i2c_init()){
	  BSP_LED_On(LED3);
  }else{
	  BSP_LED_On(LED6);
	  while(1){

	  }
  }
  i2c_mode_wait=1;



  uart2_print(&"ReadyV1.3\n");
  /* Configure User Button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);


  /* Wait for User Button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 1)
  {
  }
  
  /* Wait for User Button release before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 0)
  {
  }
  /* The board sends the message and expects to receive it back */
uart2_print(&"Configuring MPU-9150...");
uint8_t data[]={0x01};
HAL_I2C_Mem_Write_IT(&I2cHandle, (uint16_t)0xd0, 0x6B, I2C_MEMADD_SIZE_8BIT, &data, 1);
	  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY && HAL_I2C_GetError(&I2cHandle!=HAL_I2C_ERROR_NONE))
	    {
		  BSP_LED_On(LED6);
	    }
	  HAL_Delay(20);

uint8_t rx[1];
	  HAL_I2C_Mem_Read_IT(&I2cHandle, 0xd0, 0x6B, I2C_MEMADD_SIZE_8BIT, &rx, 1);
	  	  while(HAL_I2C_GetState(&I2cHandle)!=HAL_I2C_STATE_READY && I2cHandle.Lock != HAL_UNLOCKED){
	  	  		BSP_LED_On(LED4);
	  	  	}
	  	  	BSP_LED_Off(LED4);
	  	  uint8_t byte = rx[0];

	  	  if (HAL_I2C_GetError(&I2cHandle)!=HAL_I2C_ERROR_NONE){
	  	  			while(1){
	  	  				BSP_LED_On(LED6);
	  	  			}
	  	  		}
	  		  uart2_print("Read: ");
	  		  uint8_t buffer[1];
	  		  sprintf(&buffer[0], "0x%02x", byte);
	  		  uart2_print(buffer);
	  		  uart2_print("\n");

uart2_print(&"Done\n");


  uint16_t reg=0x41;
  while(1)
  {
	  BSP_LED_Toggle(LED3);
	//  HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)0xa0, (uint8_t*)aTxBuffer, TXBUFFERSIZE);
	  //HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

	/*  HAL_I2C_Mem_Write_IT(&I2cHandle, (uint16_t)0xa0, count, 16, &data, 1);
	  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
	    {
	    }
	    */
	  uart2_print("Reading: ");
	  char res[6]; /* two bytes of hex = 4 characters, plus NULL terminator */
	  sprintf(&res[0], "%04x", reg);
	  uart2_print(res);
	//  uart1_print(res);
	  BSP_LED_Off(LED5);
	//  HAL_Delay(50);

	  uint8_t dArr[1];
	  HAL_I2C_Mem_Read_IT(&I2cHandle, 0xd0, 0x41, I2C_MEMADD_SIZE_8BIT, &dArr, 2);
	  while(HAL_I2C_GetState(&I2cHandle)!=HAL_I2C_STATE_READY && I2cHandle.Lock != HAL_UNLOCKED){
	  		BSP_LED_On(LED4);
	  	}
	  	BSP_LED_Off(LED4);
	  uint8_t byte = dArr[0];

	  if (HAL_I2C_GetError(&I2cHandle)!=HAL_I2C_ERROR_NONE){
	  			while(1){
	  				BSP_LED_On(LED6);
	  			}
	  		}
		  uart2_print("Read: ");
		  int16_t readVal = (dArr[0]<<8)|(dArr[1] & 0xff);
		  sprintf(&res[0], "0x%04x", readVal);
		  uart2_print(res);
		  BSP_LED_On(LED5);
	  uart2_print("\n");



	  float temp = (float)readVal/340.0 + 35.0;
	  int d1 = temp;            // Get the integer part (678).
	  float f2 = temp - d1;     // Get fractional part (678.0123 - 678 = 0.0123).
	  int d2 = (int)(f2 * 10000);   // Turn into integer (123).
	  //int d2 = (int)(f2 * 10000); // Or this one: Turn into integer.

	  // Print as parts, note that you need 0-padding for fractional bit.
	  // Since d1 is 678 and d2 is 123, you get "678.0123"


	  uart2_print("Temperature: ");
	  uint8_t buf[11];
	  sprintf(&buf, "%04d.%04d\n", d1, d2);
	  uart2_print(buf);
	  uart2_print(" degrees C\n");

	  HAL_Delay(40);
      if((reg++)==0x43){
    	  reg=0x41;
      }
  }

  /*##-3- Wait for the end of the transfer ###################################*/
  /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it i	s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
  {
  }

  /* Wait for User Button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 1)
  {
  }

  /* Wait for User Button release before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 0)
  {
  }



  /*##-5- Wait for the end of the transfer ###################################*/
  /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it’s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
  {
  }

  /*##-6- Compare the sent and received buffers ##############################*/


  /* Infinite loop */  
  while (1)
  {
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED5 on */
 // BSP_LED_On(LED5);

}


/**
  * @brief  I2C error callbacks
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
 void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Turn LED5 on: Transfer error in reception/transmission process */
  BSP_LED_On(LED6);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  */
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return BufferLength;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
