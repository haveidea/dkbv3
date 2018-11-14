/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#include "bsp_led.h"
#include "bsp_usart1.h"
int FUNC = -1;
uint8_t BOARD_INDEX, ROW_INDEX, COL_INDEX;
int PACKAGE_LEN;
uint8_t coeff_buff[300];
int ii=0;
uint8_t buffer[310] = {0};

extern void TimingDelay_Decrement(void);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
   if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  
      __breakpoint(0);  // halt program execution here         
  }
	
	while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();	
}

void USART1_IRQHandler(void)
{ 
	uint8_t i=0; 
	uint8_t Clear = Clear;;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {	
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		i = USART1 -> DR;
		
  }
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		Clear = USART1 -> SR;
		Clear = USART1 -> DR;
	}
	
	//if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  //{	
    /* Read one byte from the receive data register */
    i = USART_ReceiveData(USART1); 
		
		if(i == 0x00) {FUNC = 0x00;}
		else if(i == 0x01) {FUNC = 0x01;}
		else if(i == 0x02) {FUNC = 0x02;}
		else if(i == 0x03) {FUNC = 0x03;}
		else if(i == 0x04) {FUNC = 0x04;}
		else if(i == 0x05) {FUNC = 0x05;}
		else if(i == 0x06) {FUNC = 0x06;}
		else if(i == 0x07) {FUNC = 0x07;}
		else if(i == 0x08) {FUNC = 0x08;}
		else if(i == 0x09) {FUNC = 0x09;}
		else if(i == 0x0a) {FUNC = 0x0a;}
		else if(i == 0x0b) {FUNC = 0x0b;}
	  else if(i == 0x0c) {FUNC = 0x0c;}
		else if(i == 0x0d) {FUNC = 0x0d;}
		else if(i == 0x0e) {FUNC = 0x0e;}
		else if(i == 0x0f) {FUNC = 0x0f;}
		else if(i == 0x10) {FUNC = 0x10;}
		else if(i == 0x11) {FUNC = 0x11;}
		else if(i == 0x12) {FUNC = 0x12;}
		else if(i == 0x13) {FUNC = 0x13;}
		else if(i == 0x14) {FUNC = 0x14;}
		else {FUNC = 0x00;}
		
  //}
  
}




/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
