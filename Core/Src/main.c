#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 
#include "LCD_Lib.h"
#include "uart.h"
#include <stdio.h>


//timer
uint32_t time20ms = 0;
uint32_t count=0;
int temp_phut;
int temp_giay;
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
char ms[]='ms';



//timer interrupt
void TIM1_UP_IRQHandler(void)
{

    if (++ count == 999)
    {
        count=0;
        giay++;
        if(59<giay)
        {
            giay=0;
            phut++;
            if(59<phut)
            {
              phut=0;
              gio++;
            }
        }
        
        
    }
    else
    {
        if((data&(1<<0))== 0 && state1==0)
        {   
          phut++;
          state1=1;
        }
        if((data&(1<<5))== 0 && state2==0)
        {
          phut--;
          state2=1;
        }
        if((data&(1<<6))== 0 && state3==0)
        {
          gio++;
          state3=1;
        }
        if((data&(1<<7))== 0 && state4==0)
        {
          gio--;
          state4=1;
        }
        
        
        if((data&(1<<0))==1 )
        {
          state1=0;
        }
        if((data&(1<<5))==(1<<5))
        {
          state2=0;
        } 
        if((data&(1<<6))==(1<<6))
        {
          state3=0;
        } 
        if((data&(1<<7))==(1<<7))
        {
          state4=0;
        } 
        
        if(temp_phut==phut && temp_giay==giay)
        {
          gpio_write(GPIOE,3,0);
        }
        else
        {
          gpio_write(GPIOE,3,1);
        }
        
    }
    TIM1->SR &= ~(TIM_SR_UIF);
}
//uart interrupt
void USART1_IRQHandler(void) 
{
    
    //nhan data
    if (USART1->SR & USART_SR_RXNE) 
    {
        Uart1.data = USART1->DR;
        if (Uart1.data == 0x0A) //enter
        {    
            Uart1.index = 0;
            
        } 
        else 
        {
            Uart1.buffer[Uart1.index++] = Uart1.data;
            if (Uart1.index == 1) 
            {  
                
                temp_phut=phut;
                temp_giay=giay;
            }
            if (Uart1.index >= 5) 
            {  
                Uart1.index = 0;
                
                
            }
        }
        int temp0 = Uart1.buffer[0]-'0';
        int temp1 = Uart1.buffer[1]-'0';
        phut=temp0*10+temp1;
        
        
        int temp3 = Uart1.buffer[3]-'0';
        int temp4 = Uart1.buffer[4]-'0';
        giay = temp3*10+temp4;  
        
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
 /////////////////////////////
        if(gio<10)
        {
          CLCD_SetCursor(&LCD1,0,0);
          CLCD_WriteString(&LCD1,"0");
          
          sprintf(lcd_send,"%d",gio);
          CLCD_SetCursor(&LCD1,1,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        else if(10<=gio)
        {
          sprintf(lcd_send,"%d",gio);
          CLCD_SetCursor(&LCD1,0,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        CLCD_SetCursor(&LCD1,2,0);
        CLCD_WriteString(&LCD1,":");

        if(phut<10)
        {
          CLCD_SetCursor(&LCD1,3,0);
          CLCD_WriteString(&LCD1,"0");
          
          sprintf(lcd_send,"%d",phut);
          CLCD_SetCursor(&LCD1,4,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        else if(10<=phut)
        {
          sprintf(lcd_send,"%d",phut);
          CLCD_SetCursor(&LCD1,3,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        CLCD_SetCursor(&LCD1,5,0);
        CLCD_WriteString(&LCD1,":");
        
        
        if(giay<10)
        {
          CLCD_SetCursor(&LCD1,6,0);
          CLCD_WriteString(&LCD1,"0");
          
          sprintf(lcd_send,"%d",giay);
          CLCD_SetCursor(&LCD1,7,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        else if(10<=giay)
        {
          sprintf(lcd_send,"%d",giay);
          CLCD_SetCursor(&LCD1,6,0);
          CLCD_WriteString(&LCD1,lcd_send);
        }
        CLCD_SetCursor(&LCD1,8,0);
        CLCD_WriteString(&LCD1,"!");
       
}
  
}





