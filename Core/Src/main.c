#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 


uint32_t time20ms = 0;
int num=0;
int state1;
int state2;
void TIM1_UP_IRQHandler(void)
{
  
 
    if (++ time20ms > 20)
    {
        time20ms = 0;
        
    }
    else
    {
       
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
    //led 7 
    ic_74HC594_init();
    //I/O init:
    
  
  while (1)
  {
    
        
        shiftIn();
        if((data&(1<<0))== 0 && state1==0)
        {   
          num++;
          state1=1;
        }
        if((data&(1<<5))== 0 && state2==0)
        {
          num--;
          state2=1;
        }
        
        if((data&(1<<0))==1 )
        {
          state1=0;
        }
        if((data&(1<<5))==(1<<5))
        {
          state2=0;
        }
       
        quetled(num);
        
    
  }
  
}





