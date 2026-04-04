#ifndef _MDL_ENSAIO_DIGITAL_
#define _MDL_ENSAIO_DIGITAL_

#include "InventTypes.h"
#include <stdint.h>

typedef enum{
	DIG_START,
	DIG_WAIT_TELA_INICIAL,
	DIG_WAIT_IDIOMA,
	DIG_WAIT_TELA_INICIAL_2,
	DIG_RUN,
	DIG_DONE
	
	
}eDigitalState;
 
	
class C_Digital{
private:
   eDigitalState _eState;
   uint16 _uiTimedelay;
   
   
public:
 	  void Init();

    //Avanca os estados da maquina de estados 
    void Run();
  
 
};

extern C_Digital EnsaioDigital;
#endif 
