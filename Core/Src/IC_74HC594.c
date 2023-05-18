#include "IC_74HC594.h" 


#define CLK_PIN 3
#define CLK_PORT GPIOB

#define LATCH_PIN 0
#define LATCH_PORT GPIOE

#define DATA_PIN 5
#define DATA_PORT GPIOB

#define GND_PIN 2
#define GND_PORT GPIOE

unsigned char led_position[5] = { 0x08, 0x10,0x20,0x40,0x80};  //LED position
unsigned char led_code[10] = {0xAF, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xCF, 0xA2, 0xEF, 0xEB};// 0->9


void ic_74HC594_init(void)
{
//    gpio_init(CLK_PORT,CLK_PIN,0);
    gpio_init(LATCH_PORT,LATCH_PIN,0);
    gpio_init(DATA_PORT,DATA_PIN,0);
    gpio_init(GND_PORT,GND_PIN,0);
    gpio_write(GND_PORT,GND_PIN,0);
}

void LED74HC594(int positon, int num){
        char data = led_position[positon];
	for(char i=0;i<=7;i++){
		if((data&(1<<(7-i)))==0){
                    gpio_write(DATA_PORT,DATA_PIN,0);     
		}
		else{
                    gpio_write(DATA_PORT,DATA_PIN,1); 
		}
		gpio_write(CLK_PORT,CLK_PIN,0);  
                gpio_write(CLK_PORT,CLK_PIN,1);  
                
	}
        gpio_write(LATCH_PORT,LATCH_PIN,1);  
        gpio_write(LATCH_PORT,LATCH_PIN,0);  
        
        
        data = led_code[num];
	for(char i=0;i<=7;i++){
		if((data&(1<<(7-i)))==0){
                    gpio_write(DATA_PORT,DATA_PIN,0);     
		}
		else{
                    gpio_write(DATA_PORT,DATA_PIN,1); 
		}
		gpio_write(CLK_PORT,CLK_PIN,0);  
                gpio_write(CLK_PORT,CLK_PIN,1);  
                
	}
        gpio_write(LATCH_PORT,LATCH_PIN,1);  
        gpio_write(LATCH_PORT,LATCH_PIN,0); 
        
}





void quetled(int num)
{
    int unit = num % 10;
    int ten = (num / 10) % 10;
    int hundred = (num / 100) % 10;
    int thousand = (num / 1000) % 10;
    int tenThousand = (num / 10000) % 10;
      
	for (int i = 0; i<=2;i++)
	{       
                LED74HC594(0,tenThousand);		
		HAL_Delay(1);
                
                LED74HC594(1,thousand);		
		HAL_Delay(1);
          
		LED74HC594(2,hundred);		
		HAL_Delay(1);
		
		LED74HC594(3,ten);
		HAL_Delay(1);

		LED74HC594(4,unit);
		HAL_Delay(1);
	}
}
