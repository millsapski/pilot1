/*
 * uart.h
 *
 *  Created on: Nov 3, 2014
 *      Author: millsapski
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal_uart.h"

#define UART1_ENABLED
#define UART2_ENABLED

#define USART1_CLK_ENABLE()              __USART1_CLK_ENABLE();
#define USART1_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USART1_TX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USART1_FORCE_RESET()             __USART1_FORCE_RESET()
#define USART1_RELEASE_RESET()           __USART1_RELEASE_RESET()
#define USART1_TX_PIN                    GPIO_PIN_6
#define USART1_TX_GPIO_PORT              GPIOB
#define USART1_TX_AF                     GPIO_AF7_USART1
#define USART1_RX_PIN                    GPIO_PIN_7
#define USART1_RX_GPIO_PORT              GPIOB
#define USART1_RX_AF                     GPIO_AF7_USART1



//#define USART2                           USART2
#define USART2_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define USART2_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USART2_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USART2_FORCE_RESET()             __USART2_FORCE_RESET()
#define USART2_RELEASE_RESET()           __USART2_RELEASE_RESET()
#define USART2_TX_PIN                    GPIO_PIN_2
#define USART2_TX_GPIO_PORT              GPIOA
#define USART2_TX_AF                     GPIO_AF7_USART2
#define USART2_RX_PIN                    GPIO_PIN_3
#define USART2_RX_GPIO_PORT              GPIOA
#define USART2_RX_AF                     GPIO_AF7_USART2

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

extern UART_HandleTypeDef Uart1;
extern UART_HandleTypeDef Uart2;
extern __IO ITStatus Uart1Ready;
extern __IO ITStatus Uart2Ready;

int uart_sendSynchronous(UART_HandleTypeDef *handle, uint8_t *buffer, int size);
extern int uart_send(UART_HandleTypeDef *handle, uint8_t *buffer, int size);
extern int uart1_print(char* buffer);
extern int uart2_print(char* buffer);

#endif /* UART_H_ */
