#ifndef __HDS_IFLASH_H__
#define __HDS_IFLASH_H__


#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


#define SAVE_DATA_ADDRESS  0x0800C000


class C_IFlash {
private:


public:

   //! Inicialização do módulo
   void Init();
   
   uint32_t  Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);
  
   
};

//! Declara como extern para ser usada por outros módulos 
extern C_IFlash FlashStm32;

#endif



