/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "stm32f10x.h"
#include "sdcard.h"
#include<stdio.h>
#include "stm3210e_eval_fsmc_nor.h"



#define BLOCK_SIZE            512 /* Block Size in Bytes */



SD_CardInfo  SDCardInfo;
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
BYTE drv /* Physical drive number (0) */
)
{
  switch(drv)
  {
  case 0:
    {
     NVIC_InitTypeDef NVIC_InitStructure;
     SD_Init();
     SD_GetCardInfo(&SDCardInfo);
     SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
     SD_EnableWideBusOperation(SDIO_BusWide_4b);
     SD_SetDeviceMode(SD_DMA_MODE);
     NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure); 
    }
    break;
  case 1:
    {
      /* Enable the FSMC Clock */
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
      /* Configure FSMC Bank1 NOR/SRAM2 */
      NOR_Init();
    }
  }
return 0;
}


/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
BYTE drv /* Physical drive number (0) */
)
{
return 0;
}


/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
BYTE drv, /* Physical drive number (0) */
BYTE *buff, /* Pointer to the data buffer to store read data */
DWORD sector, /* Start sector number (LBA) */
BYTE count /* Sector count (1..255) */
)
{
uint16_t Transfer_Length;
uint32_t Memory_Offset;

Transfer_Length =  count * 512;
Memory_Offset = sector * 512;
SD_ReadBlock(Memory_Offset, (uint32_t *)buff, Transfer_Length);
  return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
BYTE drv, /* Physical drive number (0) */
const BYTE *buff, /* Pointer to the data to be written */
DWORD sector, /* Start sector number (LBA) */
BYTE count /* Sector count (1..255) */
)
{
uint16_t Transfer_Length;
uint32_t Memory_Offset;

Transfer_Length =  count * 512;
Memory_Offset = sector * 512;

  SD_WriteBlock(Memory_Offset, (uint32_t *)buff, Transfer_Length);
//NAND_Write(Memory_Offset, (uint32_t *)buff, Transfer_Length);

return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Get current time                                                      */
/*-----------------------------------------------------------------------*/

DWORD get_fattime ()
{
return ((2006UL-1980) << 25)       // Year = 2006
| (2UL << 21)       // Month = Feb
| (9UL << 16)       // Day = 9
| (22U << 11)       // Hour = 22
| (30U << 5)       // Min = 30
| (0U >> 1)       // Sec = 0
;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
 
DRESULT disk_ioctl (
BYTE drv, // Physical drive number (0) 
BYTE ctrl, // Control code
void *buff // Buffer to send/receive control data
)
{
DRESULT res = RES_OK;
uint32_t status = SD_NO_TRANSFER;
//uint32_t status = NAND_READY;



switch (ctrl) {
case CTRL_SYNC : /// Make sure that no pending write process
status = SD_GetTransferState();
if (status == SD_NO_TRANSFER)
//status = FSMC_NAND_GetStatus();
//if (status == NAND_READY)
{res = RES_OK;}
else{res = RES_ERROR;}
break;

case GET_SECTOR_COUNT :   // Get number of sectors on the disk (DWORD)
*(DWORD*)buff = 131072; // 4*1024*32 = 131072
res = RES_OK;
break;

case GET_SECTOR_SIZE :   // Get R/W sector size (WORD) 
*(WORD*)buff = 512;
res = RES_OK;
break;

case GET_BLOCK_SIZE :     // Get erase block size in unit of sector (DWORD)
*(DWORD*)buff = 32;
res = RES_OK;
  }
  
return res;
}  