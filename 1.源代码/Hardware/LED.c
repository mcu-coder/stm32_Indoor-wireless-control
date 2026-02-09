#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	//因为PB14默认是特殊下载引脚，所以需要复用为普通IO口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_4| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	
}
//LED===============================================================================

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}

void LED1_OFF(void)  
{
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	}
}

//BEEP================================================================================

void BEEP_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

void BEEP_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void BEEP_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	}
}

//风扇==================================================================
void FAN_ON(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void FAN_OFF(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
//加热led================================================================================

void WARM_ON(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void WARM_OFF(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}



