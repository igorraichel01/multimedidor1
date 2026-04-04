#ifndef _MDL_SAVE_DIGITAL_
#define _MDL_SAVE_DIGITAL_

#include "InventTypes.h"
#include <stdint.h>



	
class C_SaveDigital{
private:
    //! para indicar se ja acionou ou não 
  

public:
 	 bool SaveFunc1(uint8_t  Nsensores,bool bVelocity);
     bool SaveFunc2(bool bVelocity ,int16 iFunc );
     bool SaveFunc3_10(int16 iFunc);
     bool SaveFunc4_6(int16 iFunc);
     bool SaveFunc7_8(int16 iFunc);
  
};

extern C_SaveDigital SaveDigital;

#endif 
