#ifndef _MDL_UTIL_
#define _MDL_UTIL_

#include "InventTypes.h"
#include <stdint.h>

;

	
class C_Util{
private:
   
 
public:
  uint32_t  Crc32(uint8_t *p, uint32_t size);
    

};

extern C_Util Util;
#endif 




