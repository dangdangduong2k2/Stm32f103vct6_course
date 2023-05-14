#include "timer.h"

void timer1_Init(void) //1ms
{
  TIM1->CR1 &= ~(1 << 4);
  TIM1->ARR = 999;
  TIM1->PSC = 71;
  TIM1->DIER |= (1 << 0);
  NVIC->IP[25] |= (0x01 << 4);
  NVIC->ISER[0] |= (1 << 25);
  TIM1->CR1 |= (1 << 0);
}

void timer2_Init(void) //1ms
{
  GPIOB->CRH |= GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1; 
  TIM2->PSC = 71;         
  TIM2->ARR = 999; 
  TIM2->CCMR2 = 0x6060;    
  TIM2->CCER |= 0x0300;    
  TIM2->CR1 = 0x0081; 
  AFIO->MAPR |= (1<<9);
  AFIO->MAPR &= ~(1<<8);
  
  TIM2->CCR3 = 900; 
  TIM2->CCR4 = 900; 
 
}




