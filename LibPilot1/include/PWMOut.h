#ifndef _PWM_OUT
#define _PWM_OUT

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "io.h"

int PWMOut_init();
int PWMOut_initCCP();
int PWMOut_start();

#endif
