#include "uart.h"
#include "stm32f401xe.h"

void UART_Init(void)
{
    RCC->AHB1ENR |= (1 << 0);

    // PA2 Alternate Function (TX)
    GPIOA->MODER &= ~(3 << (2 * 2));
    GPIOA->MODER |=  (2 << (2 * 2));

    // PA3 Alternate Function (RX)
    GPIOA->MODER &= ~(3 << (3 * 2));
    GPIOA->MODER |=  (2 << (3 * 2));

    // Alternate Function 7
    GPIOA->AFR[0] &= ~(0xF << (2 * 4));
    GPIOA->AFR[0] |=  (7 << (2 * 4));

    GPIOA->AFR[0] &= ~(0xF << (3 * 4));
    GPIOA->AFR[0] |=  (7 << (3 * 4));

    // Enable USART2 clock
    RCC->APB1ENR |= (1 << 17);

    // Baud rate
    USART2->BRR = 0x008B;

    // Frame format
    USART2->CR1 &= ~(1 << 12);
    USART2->CR1 &= ~(1 << 10);

    // Enable TX
    USART2->CR1 |= (1 << 3);

    // Enable RX
    USART2->CR1 |= (1 << 2);

    // Enable USART
    USART2->CR1 |= (1 << 13);
}

/* Write the next function here */
void UART_SendChar(char ch)
{
    while (!(USART2->SR & (1 << 7)));

    USART2->DR = ch;
}

/* Then this function */
void UART_SendString(char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}

/* Then this function */
char UART_ReadChar(void)
{
    while (!(USART2->SR & (1 << 5)));

    return USART2->DR;
}