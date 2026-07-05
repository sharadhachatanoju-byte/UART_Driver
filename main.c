#include "main.h"
#include "uart.h"

int main(void)
{
	UART_Init();

	while(1)
	{
		UART_SendString("Hello Shiva\n");
	}
}
