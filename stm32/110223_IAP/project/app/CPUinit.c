//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : CPUInit.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_systick.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_iwdg.h"
#include "cpuinit.h"


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function Declaration
----------------------------------------------------------------------------------*/   
void NVIC_Configuration(u8 mode);
void USART_Configuration(void);
void GPIO_Configuration(void);
void SysTick_Configuration(void);
void RCC_Configuration(void);
void STM32F10X_Init(void);
void RTC_Configuration(void);
void WatchDog_Config(void);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  MCU Initialization
      STM32F103의 각 부분을 초기화
  Arg :
	char mode
  Return :
	void
----------------------------------------------------------------------------------*/ 
void CPUInit(char mode)
{
  /* Configure the system clocks */
    RCC_Configuration();
  
    /* Configure GPIOs */
    GPIO_Configuration();
      
    /* NVIC Configuration */
    NVIC_Configuration(mode);

    /* System Tick counter config */
    SysTick_Configuration();
	
    /* USART configuration */
    USART_Configuration();
	
	/* WatchDog configuration */
	WatchDog_Config();			
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  MCU의 각 System Clock 부분 초기화
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
		
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		
		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);
		
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
    
	/* Enable GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
						 RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_USART1 |
						 RCC_APB2Periph_AFIO, ENABLE);

	/* Enable TIM2, TIM3 and TIM4 clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5
						   , ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  MCU의 각 GPIO 부분을 초기화 하고, 기능 설정을 한다.
  	여기서 포트 지정을 잘못하면, 포트 입출력이 제대로 동작되지 않으니, 주의~!
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART1/2 Tx (PA.09, PA02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART1/2 Rx (PA.10, PA03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_3 | GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

// GPIO C setting - input
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_0 |
	  								GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
// GPIO C - output
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_10 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
// GPIO D - input
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOD,GPIO_Pin_10,Bit_SET);	// PC RST Default - NONE;
	GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_RESET);	// PC Wakeup Default - NONE;

	// GPIO D - output
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11	| 
	  								GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  								
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// GPIO D - input
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// GPIO E - output - LED
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	  								GPIO_Pin_4 | GPIO_Pin_5;		// +jwshin 101228 Port5 추가...
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  								
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOD,GPIO_Pin_10,Bit_SET);	// PC RST Default - NONE;
	GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_RESET);	// PC Wakeup Default - NONE;
/*	
	// USART 1/2/3 Tx Send Signal 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
*/
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  MCU의 Interrupt Vector Table 지정
  Arg :
	u8 mode
  Return :
	void
----------------------------------------------------------------------------------*/ 
void NVIC_Configuration(u8 mode)
{

  	NVIC_DeInit();
	NVIC_InitTypeDef NVIC_InitStructure;      
         

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  BOOT_MODE는 Flash Writer를 사용하여 Writing 할 경우에 사용하며, 
  WORK_MODE는 IAP DownLoader를 Flash에 Loading한 상태에서 사용한다.
  (반드시 지킬 것~! 맞지 않으면 Board가 동작안됨.)
  2010.12.28 Shin Jung Wook...  : 반드시 icf File도 변경이 되어야만 함.
----------------------------------------------------------------------------------*/ 
	switch(mode)											
	{
	case	WORK_MODE:	//0x8002000
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
		break;
	case	BOOT_MODE:  //0x8000000
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		break;
	default:
		break;
	}

	// Configure one bit for preemption priority 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable USART1 RX IRQ Channel */
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART3 Interrupt */
	/* 현재 미사용이므로, Remark */				// -jwshin 101220
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	 

	
	/* Enable the USART4 Interrupt */
	/* 현재 미사용이므로, Remark */				// -jwshin 101220
//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQChannel;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : USART Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(void)
{  
	USART_InitTypeDef USART_InitStructure;
	
	/* USART1 configured as follow:
		- BaudRate = 9600 baud  
		- Word Length = 8 Bits
		- One Stop Bit
		- Parity Odd
		- Hardware flow control desabled
		- Receive and transmit enabled
	*/
//	USART_InitStructure.USART_BaudRate = 19200;
//	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_BaudRate = 115200;			// +jwshin 110111
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);
	
	/* Enable the USART Receive interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART1, USART_IT_TC, ENABLE);

 	USART_Cmd(USART1, ENABLE);
	
	
// 	Uart 2 Configuration
//	USART_InitStructure.USART_BaudRate = 115200;	 // +jwshin 110111
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_CTS;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
 	USART_Cmd(USART2, ENABLE);
	
// 	Uart 4 Configuration
	
	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART4, &USART_InitStructure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(UART4, ENABLE);
}

/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : Configures SysTick.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configuration(void)
{
	/* SysTick end of count event each 1ms with input clock equal to 9MHz (HCLK/8, default) */
//	SysTick_SetReload(9000);    // every 1ms
	SysTick_SetReload(90000);   // every 10ms
	
	/* Enable SysTick interrupt */
	SysTick_ITConfig(ENABLE);
	
	/* Clear SysTick Counter */
	SysTick_CounterCmd(SysTick_Counter_Clear);
	
	/* Enable the SysTick Counter */
	SysTick_CounterCmd(SysTick_Counter_Enable);
}

/*******************************************************************************
* Function Name  : WatchDog_Config
* Description    : Configures WatchDog
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WatchDog_Config(void)
{
//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_IWDG, ENABLE);
  
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(1000);
	IWDG_Enable();
}
