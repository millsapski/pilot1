/*
 * PWMOut.c
 *
 *  Created on: Feb 15, 2015
 *      Author: millsapski
 */

#include "PWMOut.h"
#include "stm32f4xx_hal_tim.h"
#include "main.h"

TIM_HandleTypeDef tim2Handle;
TIM_HandleTypeDef tim5Handle;
TIM_HandleTypeDef tim4Handle;
TIM_OC_InitTypeDef ocInit;

/*pinmap:
TIM2:
	A5
	B3
	B10
	B11
TIM5:
	A0
	A1
	A2
	A3

 */


int PWMOut_init(){

	__TIM2_CLK_ENABLE();
	__TIM5_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	uint16_t PWMOut_pins[] = {GPIO_PIN_5, GPIO_PIN_3, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};
	GPIO_TypeDef * PWMOut_ports[] ={GPIOA, GPIOB, GPIOB, GPIOB, GPIOA, GPIOA, GPIOA, GPIOA};
	uint8_t af[] = {GPIO_AF1_TIM2,GPIO_AF1_TIM2,GPIO_AF1_TIM2,GPIO_AF1_TIM2, GPIO_AF2_TIM5, GPIO_AF2_TIM5, GPIO_AF2_TIM5, GPIO_AF2_TIM5};

	for(int i=0; i<8; i++){
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = PWMOut_pins[i];
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = af[i];

		HAL_GPIO_Init(PWMOut_ports[i], &GPIO_InitStruct);
	}

	TIM_Base_InitTypeDef TIM_InitStruct;
	//TIM_InitStruct.Prescaler = 84; //1 tick every microsecond

	TIM_InitStruct.Prescaler = 84; //1 tick every microsecond
	TIM_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_InitStruct.Period = 20000;
	TIM_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_InitStruct.RepetitionCounter = 0;


	tim2Handle.Instance = TIM2;
	tim2Handle.Init = TIM_InitStruct;
	BSP_LED_On(LED5);
	if(HAL_TIM_PWM_Init(&tim2Handle)!=HAL_OK){
		return 1;
	}
	tim5Handle.Instance = TIM5;
	tim5Handle.Init = TIM_InitStruct;
	if(HAL_TIM_PWM_Init(&tim5Handle)!=HAL_OK){
			return 1;
		}

	PWMOut_initCCP();

	return HAL_OK;
}


void PWMOut_setPulseWidth(int channel, int pulseWidth){ //takes in pulseWidth in ms, channels 0-7
	TIM_TypeDef* timer;
	if(channel<4){
		timer = TIM2;
	}else{
		timer = TIM4;
	}
	switch(channel%4){
	case(0):
		timer->CCR1 = pulseWidth;
	break;
	case(1):
			timer->CCR2 = pulseWidth;
	break;
	case(2):
			timer->CCR3 = pulseWidth;
	break;
	case(3):
			timer->CCR4 = pulseWidth;
	break;

	}
}

int PWMOut_start(){
	uint32_t chans[] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};
	for(int i=0; i<4; i++){
	int pwmStartResp = HAL_TIM_PWM_Start(&tim2Handle, chans[i]);
	if(pwmStartResp!=HAL_OK){
		return pwmStartResp;
	}
	pwmStartResp = HAL_TIM_PWM_Start(&tim5Handle, chans[i]);
	if(pwmStartResp!=HAL_OK){
		return pwmStartResp;
	}
	}
	return HAL_OK;
}


int PWMOut_initCCP(){
	ocInit.OCMode = TIM_OCMODE_PWM1;
	ocInit.Pulse = 500;
	ocInit.OCPolarity = TIM_OCPOLARITY_HIGH;
	ocInit.OCIdleState = TIM_OCIDLESTATE_RESET;
	uint32_t chans[] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};
	for(int i=0; i<4; i++){
		int resp = HAL_TIM_PWM_ConfigChannel(&tim2Handle, &ocInit, chans[i]);
		if(resp!=HAL_OK){
			return resp;
		}
		resp = HAL_TIM_PWM_ConfigChannel(&tim5Handle, &ocInit, chans[i]);
		if(resp!=HAL_OK){
			return resp;
		}
	}
	return HAL_OK;
}
