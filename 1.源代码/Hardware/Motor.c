#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_10 | GPIO_Pin_11;    //PA3,PA4,PA5,PA6控制步进驱动引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}


//1相励磁函数，A-B-C-D    

void Motor_One(uint16_t speed)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9|GPIO_Pin_10 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_10 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10);	
	Delay_ms(speed);
}

//反转
void Motor_One1(uint16_t speed)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_10 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9|GPIO_Pin_10 | GPIO_Pin_11);	
	Delay_ms(speed);
}



//2相励磁函数   AB-BC-CD-DA

void Motor_two(uint16_t speed)
{	
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_9);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_10|GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9|GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_10 | GPIO_Pin_11);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9 | GPIO_Pin_10);	
	Delay_ms(speed);

	
}


//1.2混合励磁函数  A-AB-B-BC-C-CD-D-DA

void Motor_one_two(uint16_t speed)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_6);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5 | GPIO_Pin_6);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_5 | GPIO_Pin_6);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_6);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_6);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_4);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_5);	
	Delay_ms(speed);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5);	
	Delay_ms(speed);
}
