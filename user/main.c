#include "usart.h"
#include "ledCkc.h"
#include "delay.h"
u8 receiveFlag=0;

//设置USART1中断服务函数
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res = USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
		receiveFlag=1;
	}
}

int main(void)
{
	delay_init();
	//设置系统中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	ledInit();
	
	usartInit();
	while(1)
	{
		if(receiveFlag)
		{
			receiveFlag=0;
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			delay_ms(20);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}
	}
}
