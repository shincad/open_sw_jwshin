/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V2.0.2
* Date               : 09/22/2008
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL)
// #define USE_STM3210B_EVAL
// #define USE_STM3210E_EVAL
#define IQS_BOARD_DNP         // +jwshin 101228
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define GPIO_KEY_BUTTON                   GPIOB
  #define RCC_APB2Periph_GPIO_KEY_BUTTON    RCC_APB2Periph_GPIOB
  #define GPIO_PIN_KEY_BUTTON               GPIO_Pin_9
  #define PAGE_SIZE                         (0x400)
  #define FLASH_SIZE                        (0x20000) /* 128K */
#elif defined USE_STM3210E_EVAL
  #define GPIO_KEY_BUTTON                   GPIOG    
  #define RCC_APB2Periph_GPIO_KEY_BUTTON    RCC_APB2Periph_GPIOG
  #define GPIO_PIN_KEY_BUTTON               GPIO_Pin_8
  #define PAGE_SIZE                         (0x800)
  #define FLASH_SIZE                        (0x80000) /* 512K */
#elif defined IQS_BOARD_DNP
  #define GPIO_KEY_BUTTON                   GPIOC
  #define RCC_APB2Periph_GPIO_KEY_BUTTON    RCC_APB2Periph_GPIOC
  #define GPIO_PIN_KEY_BUTTON               GPIO_Pin_7
  #define PAGE_SIZE                         (0x800)
  #define FLASH_SIZE                        (0x40000) /* 256K */
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
