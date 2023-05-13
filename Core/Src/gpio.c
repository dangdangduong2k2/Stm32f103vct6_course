#include "gpio.h"


void gpio_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_Type)//0 :output,1: input
{
    if ( 0 <GPIO_Pin <=7)
    {
        if ( GPIO_Type == 1 )
        {
            GPIOx->CRL |= 1 << (GPIO_Pin*4+3);
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+2));
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+1));
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+0));
        }
        
        if ( GPIO_Type == 0 )
        {
            
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+3));
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+2));
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+1));
            GPIOx->CRL |= 1 << (GPIO_Pin*4+0);
        }
    }
    
    if ( 8 <= GPIO_Pin <=15)
    {
      
        GPIO_Pin= GPIO_Pin - 8;
        if ( GPIO_Type == 1 )
        {
            GPIOx->CRH |= 1 << (GPIO_Pin*4+3);
            GPIOx->CRH &= ~(1 << (GPIO_Pin*4+2));
            GPIOx->CRH &= ~(1 << (GPIO_Pin*4+1));
            GPIOx->CRL &= ~(1 << (GPIO_Pin*4+0));
        }
        
        if ( GPIO_Type == 0 )
        {
            
            GPIOx->CRH &= ~(1 << (GPIO_Pin*4+3));
            GPIOx->CRH &= ~(1 << (GPIO_Pin*4+2));
            GPIOx->CRH &= ~(1 << (GPIO_Pin*4+1));
            GPIOx->CRH |= 1 << (GPIO_Pin*4+0);
        }
    }
    
}

uint8_t gpio_read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0;
  
    if ((GPIOx->IDR & (1 <<(GPIO_Pin))) != 0)
    {
        bitstatus = 1;
    }
    
    else
    {
        bitstatus = 0;
    }
    
    return bitstatus;
}


void gpio_write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t State)//1 : set, 0, reset
{
    
    if(State == 1)
    {
        GPIOx->BSRR |= (1<< GPIO_Pin);
    }
    
    if(State == 0)
    {
        GPIOx->BRR |= (1<< GPIO_Pin);
    }
}

