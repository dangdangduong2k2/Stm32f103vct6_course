#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
  
extern GPIO_TypeDef* GPIOx;  
  
  
void gpio_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_Type);//0 :output,1: input;
void gpio_write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t State);
uint8_t gpio_read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


  

  


#ifdef __cplusplus
}
#endif

#endif 