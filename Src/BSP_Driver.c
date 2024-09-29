/*****************************************************************
 * MiniConsole V3 - BSP Drivers
 *******************************************************************/

#include "BSP_Driver.h"

BSP_Driver_TypeDef * BSP = (BSP_Driver_TypeDef *)0x08000400;

// Overriding syscall __io_putchar(int ch) for redirecting printf output to USART2
int __io_putchar(int ch) {
	uint8_t * pData = (uint8_t *)&ch;
	BSP->Serial_Transmit(pData, 1);
	return ch;
}
