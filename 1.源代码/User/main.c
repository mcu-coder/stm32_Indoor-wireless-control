#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "DHT11.h"
#include "sys.h"
#include "usart.h"
#include "usart2.h"
#include "string.h"
#include "stdio.h"
#include "timer.h"
#include "mq2.h"
#include "Motor.h"
#include "gizwits_product.h"
#include "Delay.h"

//显示全局变量===============================================================================================================================
uint16_t ADValue;
uint16_t Voltage;
u8 temp = 0,humi = 0;
u8 hongwai=0;
int key_num;      //按键返回值

//得到数据变量===========================================
void shuju()
{
		ADValue = AD_GetValue();	
		Voltage = 99 - 99 * ADValue / 4095;
		DHT11_Read_Data(&temp,&humi);	
}
//按键==========================================
u8 mode_flag = 0;   //模式控制：0-自动 ，1-手动
u8 alarm_flag=0;
u8 chuanglian_flag=0;
u8 guangzhao_flag=0;
void anjian()
{
		key_num=Key_GetNum();
//		OLED_ShowString(3,14,":");
		//OLED_ShowNum(3,14,key_num,1);	
		if(key_num==1)  {hongwai=1;}	
		else{hongwai=0;}
		
//		if(key_num == 2)
//			{
//				if(++mode_flag==2)mode_flag=0;
//			}	
		//报警
		if(key_num==3)  
			{
				if(++alarm_flag==2)alarm_flag=0;
			}	
		//窗帘		
		if(key_num==4)  
			{
				if(++chuanglian_flag==2)chuanglian_flag=0;
			}	
		//光照
		if(key_num==5)  
			{
				if(++guangzhao_flag==2)guangzhao_flag=0;
			}				
}
//自动控制============================================
//u8 flag=0;
u8 kongtiao_1=0;
void auto1()
{
		//照明控制
	if(guangzhao_flag==0)
	{
		if(Voltage>50)
		{	
			LED1_ON();
		}
		if(Voltage<=50)
		{	
			LED1_OFF();
		}	
	} 
	//风扇控制
	if(temp>30)
	{	
		FAN_ON();
		WARM_ON();
		kongtiao_1=1;
	}
	 
}

//显示界面==============================================================
void xianshi()
{
	//第一行
		OLED_ShowChinese(1,1,0); //温
		OLED_ShowChinese(1,2,1); //度	
		OLED_ShowString(1,5,":");
		OLED_ShowNum(1,6,temp,2);
		OLED_ShowChinese(1,5,2); //湿
		OLED_ShowChinese(1,6,1); //度	
		OLED_ShowString(1,13,":");
		OLED_ShowNum(1,14,humi,2);
	
	//第二行
		OLED_ShowChinese(2,1,4); //空
		OLED_ShowChinese(2,2,5); //调
		OLED_ShowString(2,5,":");
		if(kongtiao_1==1)
		{
			OLED_ShowChinese(2,4,16); //开
		}
		else
		{
			OLED_ShowChinese(2,4,17); //关
		} 
	 
}

void userHandle(void)
{

    currentDataPoint.valuealarm = hongwai;//Add Sensor Data Collection
    currentDataPoint.valuekongtiao = kongtiao_1;//Add Sensor Data Collection
    currentDataPoint.valuetemp = temp ;//Add Sensor Data Collection
    currentDataPoint.valuehumi = humi ;//Add Sensor Data Collection
    currentDataPoint.valueliangdu = Voltage ;//Add Sensor Data Collection

}

int main(void)
{
	Delay_init();
	LED_Init();
	OLED_Init();
	DHT11_Init();  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	Key_Init();
	Motor_Init();
	gizwitsInit();
	gizwitsSetMode(WIFI_AIRLINK_MODE);	
	Delay_ms(1000);
	Delay_ms(1000);
	while (1)
	{
		shuju();
		xianshi();
		anjian();
		auto1();
		userHandle();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
	}
}
