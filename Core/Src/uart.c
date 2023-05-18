#include "uart.h"

void uart1_init(void)
{
  GPIOA->CRH &= ~(GPIO_CRH_CNF9  | GPIO_CRH_MODE9); // reset PA9
  GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10); // reset PA10

  GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0;  // 0b11 50MHz output
  GPIOA->CRH |= GPIO_CRH_CNF9_1; // PA9: output @ 50MHz - Alt-function Push-pull
  GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 RX - Mode = 0b00 (input) - CNF = 0b01 (input floating)

  // configure USART1 registers
  USART1->BRR = 0x00001D4C;

  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
  USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS);

    // Enable USART1 interrupt in NVIC
  NVIC_EnableIRQ(USART1_IRQn);
  USART1->CR1 |= (USART_CR1_UE); 
}


void uart_sendchar(uint8_t ch)
{
   
    while (!(USART1->SR & USART_SR_TXE));

    USART1->DR = ch;
}


void uart_sendstring(const char* str)
{
    while (*str != '\0')
    {
        uart_sendchar(*str); 
        str++; 
    }
    
}

