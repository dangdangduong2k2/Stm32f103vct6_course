#include "uart.h"

void uart1_init(void)
{
    
    GPIOA->CRH &= ~(0xF << 4); // Clear CNF and MODE bits for pin 9
    GPIOA->CRH |= (0xA << 4);  // Set pin 9 as Alternate Function, Push-pull
    GPIOA->CRH &= ~(0xF << 8); // Clear CNF and MODE bits for pin 10
    GPIOA->CRH |= (0x4 << 8);  // Set pin 10 as Input Floating

    // Configure USART1
    USART1->CR1 &= ~(USART_CR1_UE);     // Disable USART1
    USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS); // 8-bit data, no parity
    USART1->CR2 &= ~(USART_CR2_STOP);   // 1 stop bit
    USART1->BRR = 104;                // Baudrate: 9600 @ 16MHz
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE); // Enable transmitter and receiver
    USART1->CR1 |= USART_CR1_RXNEIE;

    // Enable USART1 interrupt in NVIC
    NVIC_EnableIRQ(USART1_IRQn);
    USART1->CR1 |= (USART_CR1_UE); 
}