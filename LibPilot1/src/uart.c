/*
 * uart.c
 *
 *  Created on: Nov 3, 2014
 *      Author: millsapski
 */
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_hal_uart.h"
#include "uart.h"

UART_HandleTypeDef Uart1;
UART_HandleTypeDef Uart2;
__IO ITStatus Uart1Ready = RESET;
__IO ITStatus Uart2Ready = RESET;

int uart_init(){
	Uart1.Instance        = USART1;
	 Uart1.Init.BaudRate   = 9600;
	 Uart1.Init.WordLength = UART_WORDLENGTH_8B;
	 Uart1.Init.StopBits   = UART_STOPBITS_1;
	 Uart1.Init.Parity     = UART_PARITY_NONE;
	 Uart1.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	 Uart1.Init.Mode       = UART_MODE_TX_RX;

		  if(HAL_UART_Init(&Uart1) != HAL_OK)
		  {
		   	return 0;
		  }

	Uart2.Instance        = USART2;
	  Uart2.Init.BaudRate   = 9600;
	  Uart2.Init.WordLength = UART_WORDLENGTH_8B;
	  Uart2.Init.StopBits   = UART_STOPBITS_1;
	  Uart2.Init.Parity     = UART_PARITY_NONE;
	  Uart2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  Uart2.Init.Mode       = UART_MODE_TX_RX;

	  if(HAL_UART_Init(&Uart2) != HAL_OK)
	  {
	   	return 0;
	  }
	  return 1;
}

int uart2_print(char* buffer){
	return uart_sendSynchronous(&Uart2, buffer, strlen(buffer));
}
int uart1_print(char* buffer){
	return uart_sendSynchronous(&Uart1, buffer, strlen(buffer));
}

int uart_send(UART_HandleTypeDef *handle, uint8_t *buffer, int size){

	Uart2Ready=RESET;
	if(HAL_UART_Transmit_IT(handle, buffer, size)!= HAL_OK)
		  {
			return 0;
		  }
	return 1;
}
int uart_sendSynchronous(UART_HandleTypeDef *handle, uint8_t *buffer, int size){
	if(!uart_send(handle, buffer, size)){
		return 0;
	}
	  /* Wait for the end of the transfer */
	while(HAL_UART_GetState(handle)!=HAL_UART_STATE_READY){
		BSP_LED_On(LED4);
	}
	BSP_LED_Off(LED4);
	  return 1;
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *Handle)
{
	if(Handle==&Uart1){
		Uart1Ready = SET;
	}else{
		Uart2Ready = SET;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *Handle)
{
	if(Handle==&Uart1){
			Uart1Ready = SET;
		}else{
			Uart2Ready = SET;
		}
}

 void HAL_UART_ErrorCallback(UART_HandleTypeDef *Handle)
{
  BSP_LED_On(LED4);
}
