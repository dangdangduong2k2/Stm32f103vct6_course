#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 


uint32_t time20ms = 0;

void TIM1_UP_IRQHandler(void)
{
    if (++ time20ms > 500)
    {
        time20ms = 0;
        gpio_write(GPIOA,9,0);     
    }
    else
    {
        gpio_write(GPIOA,9,1);
    }
    
    TIM1->SR &= ~(TIM_SR_UIF);
}


int main(void)
{
 
  //system config:

    //HAL
    HAL_Init();
    //system clock
    SystemClock_Config();
    //system peripheral
    system_clock_peripheral_init();
    //timer init
    timer1_Init();
    timer2_Init();

    
    
  //user config:
  
    //ic I/O
    ic_74AC165D_init();
    
    ic_74HC594_init();
    //I/O init:
    gpio_init(GPIOA,9,0);
    gpio_init(GPIOA,9,0);
  
  while (1)
  {
  }
  
}





