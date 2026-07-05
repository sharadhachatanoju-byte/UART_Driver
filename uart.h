#ifndef UART_H_
#define UART_H_

#include<stdint.h>


void UART_Init(void);
void UART_SendChar(char ch);
void UART_SendString(char *str);
char UART_ReadChar(void);

#endif