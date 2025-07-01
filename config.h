#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <string.h>
void gpioConfig();
void systemClockConfig(void);
void delay(uint32_t time);
void uartConfig();
void UART2_SendChar(char ch);
void UART2_SendString(char *str);