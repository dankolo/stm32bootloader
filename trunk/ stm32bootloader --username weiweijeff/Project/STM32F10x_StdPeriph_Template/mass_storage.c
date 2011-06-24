/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : mass_storage.c
* Author             : MCD Application Team
* Version            : V2.0.0
* Date               : 04/27/2009
* Description        : This file provides a set of functions needed to manage the
*                      communication between the STM32F10x USB and the SD Card 
*                      and NAND Flash .
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "sdcard.h"
#include "fsmc_nand.h"
#include "nand_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Mass_Storage_Init
* Description    : Initializes the peripherals used by the mass storage driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Mass_Storage_Init(void)
{
  /* Disable the Pull-Up*/
  USB_Cable_Config(DISABLE);

}

/*******************************************************************************
* Function Name  : Mass_Storage_Start
* Description    : Starts the mass storage demo.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Mass_Storage_Start (void)
{
  

  

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    
  /* Enable and GPIOD clock */
  USB_Disconnect_Config();
  
  /* MAL configuration */
  MAL_Config();

  Set_USBClock();
  
  USB_Init();
  USB_Cable_Config(ENABLE);
  //while (bDeviceState != CONFIGURED);
}

/*******************************************************************************
* Function Name  : Mass_Storage_Recovery
* Description    : Erases the NAND Flash Content.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Mass_Storage_Recovery (void)
{
#if 0  

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 
  /* FSMC Initialization */
  FSMC_NAND_Init();

  NAND_Format();  
#endif  
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
