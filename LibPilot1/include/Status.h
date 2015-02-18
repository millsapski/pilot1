#ifndef _STATUS_H_
#define _STATUS_H_

typedef struct{
	HAL_StatusTypeDef PWMOutInit, PWMInInit, I2CInit, SPIInit, UART1Init, UART2Init, UART3Init;
}Init_Status;


typedef enum{
	FDU_ERROR_NONE, FDU_ERROR_NONFATAL, FDU_ERROR_FATAL
}Fault_Type;


#endif
