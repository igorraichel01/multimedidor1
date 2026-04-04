/********************************** HdsIFlash *******************************************//**
 *\file     	HdsIFlash.c
 
 *\details   	Rotinas para escrita na flash interna do processador 
 *              Acessa as ultimas paginas do banco
 *              um único banco de flash com 255 paginas de 2kbytes
 *
 * ----------------------------------------------------------------------------------------------
 * \version   	s.00 - Primeira versão documentada
 * \date      	17/05/2021
 ***********************************************************************************************/

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash_ex.h"

#include "HdsIFlash.h"



const uint8_t  Reserved[0x4000] __attribute__((at(SAVE_DATA_ADDRESS))) ={0xFF};

C_IFlash FlashStm32;

/*********************************************************************************************//**
 * \fn         Init
 * \details    Inicializa a configuração da flash 
				
 * \author     
 * \date        18/08/2021
 ************************************************************************************************/
void C_IFlash::Init(void)
 {
 
   Flash_Write_Data (SAVE_DATA_ADDRESS,(uint32_t *)&"teste 12",2);  
 }


/*********************************************************************************************//**
 * \fn         Flash_Write_Data 
 * \details    
			   


Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes

>> usa o setor 3 para salvar os dados 



 * \author     
 * \date        18/08/2021
 ************************************************************************************************/
//uint32_t C_IFlash:: Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords)
uint32_t C_IFlash:: Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;
	int sofar=0;

	  /* Unlock the Flash to enable the flash control register access *************/
	   HAL_FLASH_Unlock();

	   /* Erase the user Flash area*/

	   /* Fill EraseInit structure*/

        EraseInitStruct. TypeErase = FLASH_TYPEERASE_SECTORS;;      /*!< Mass erase or sector Erase.
                                                                    This parameter can be a value of @ref FLASHEx_Type_Erase */

        EraseInitStruct.Banks = FLASH_BANK_1;       /*!< Select banks to erase when Mass erase is enabled.
                                        This parameter must be a value of @ref FLASHEx_Banks */

        EraseInitStruct.Sector = FLASH_SECTOR_3;      /*!< Initial FLASH sector to erase when Mass erase is disabled
                             This parameter must be a value of @ref FLASHEx_Sectors */

        EraseInitStruct.NbSectors =1 ;   /*!< Number of sectors to be erased.
                                    This parameter must be a value between 1 and (max number of sectors - value of Initial sector)*/

        EraseInitStruct.VoltageRange=FLASH_VOLTAGE_RANGE_3;/*!< The device voltage range which defines the erase parallelism
                             This parameter must be a value of @ref FLASHEx_Voltage_Range */

	   if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	   {
	     /*Error occurred while page erase.*/
		  return HAL_FLASH_GetError ();
	   }

	   /* Program the user Flash area word by word*/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartPageAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartPageAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	   /* Lock the Flash to disable the flash control register access (recommended
	      to protect the FLASH memory against possible unwanted operation) *********/
	   HAL_FLASH_Lock();

	   return 0;
}



