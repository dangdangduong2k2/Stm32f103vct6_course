#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 
#include "LCD_Lib.h"
#include "uart.h"
#include <stdio.h>
#include <math.h>


//timer
uint32_t time20ms = 0;
uint32_t count=0;
int temp_phut;
int temp_giay;
int pwm;
int giatri;
//button, 7seg
int num=0;
int state1;
int state2;
int state3;
int state4;

int lock;
uint8_t start_count=0;
//LCD
CLCD_Name LCD1;
char lcd_send[16];
int gio=14;
int phut=58;
int giay=59;
//uart
uart1 Uart1;
char  buff[2];
char char_count[7];
char ms[2]="ms";



//timer interrupt
void TIM1_UP_IRQHandler(void)
{
    TIM1->SR &= ~(TIM_SR_UIF);
    if (++ time20ms == 999)
    {
        time20ms=0;
    }
    else
    {
        
    }
    
}
void TIM3_IRQHandler(void)
{
    
  TIM3->SR &= ~TIM_SR_UIF;
  if(Uart1.accept==1)
  {
      Uart1.timer50ms++;
  }
  if(Uart1.timer50ms==50)
  {
      Uart1.index = 0;     
      Uart1.user_buffer[0]=Uart1.buffer[0];
      Uart1.user_buffer[1]=Uart1.buffer[1];
      Uart1.user_buffer[2]=Uart1.buffer[2];
      Uart1.user_buffer[3]=Uart1.buffer[3];
      Uart1.user_buffer[4]=Uart1.buffer[4];
      Uart1.accept=0;
      Uart1.timer50ms=0;
      Uart1.buffer[0]='\0';
      Uart1.buffer[1]='\0';
      Uart1.buffer[2]='\0';
      Uart1.buffer[3]='\0';
      Uart1.buffer[4]='\0';
  }
}
//uart interrupt
void USART1_IRQHandler(void) 
{
    
    //nhan data
    if (USART1->SR & USART_SR_RXNE) 
    {   
        Uart1.accept=1;
        Uart1.data = USART1->DR;
        if (Uart1.data == 0x0A) //enter
        {    
            Uart1.index = 0;    
        } 
        else 
        {
            Uart1.buffer[Uart1.index++] = Uart1.data;

            if (Uart1.index >= 5) 
            {  
                Uart1.index = 0;        
            }
        }
    
        USART1->SR &= ~USART_SR_RXNE;
    } 
    
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
    timer3_Init();
    //uart1 init
    uart1_init();
    
    
  //user config:
  
    //ic I/O
    ic_74AC165D_init();
    //led 7 
    ic_74HC594_init();
    //I/O init:
    gpio_init(GPIOE,3,0);//loa
    
    //lcd setup
    gpio_init(GPIOD,0,0);
    gpio_init(GPIOD,1,0);
    gpio_init(GPIOD,2,0);
    gpio_init(GPIOD,3,0);
    gpio_init(GPIOD,4,0);
    gpio_init(GPIOD,5,0);
    gpio_init(GPIOD,6,0);
    gpio_init(GPIOD,7,0);
    
    gpio_write(GPIOD,4,1);
    
    CLCD_4BIT_Init(&LCD1, 16, 2,
    GPIOD, GPIO_PIN_7, GPIOD, GPIO_PIN_5,
    GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1,
    GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3);
    
while (1)
{
        shiftIn();
     
}
  
}





