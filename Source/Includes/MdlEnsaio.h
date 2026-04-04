#ifndef _MDL_ENSAIO_
#define _MDL_ENSAIO_

#include "InventTypes.h"
#include <stdint.h>

#define 			TEMPO_TELA 4


typedef enum{
	ENSAIO_START,
	ENSAIO_WAIT_TELA_INICIAL,
	ENSAIO_WAIT_IDIOMA,
	ENSAIO_WAIT_TELA_INICIAL_2,
    ENSAIO_TIPO,
	ENSAIO_RUN_DIGITAL,
	ENSAIO_RUN_ANALOG,
	ENSAIO_DONE
	
	
}eState;
 
	
class C_Ensaio{
private:
   eState _eState;
   uint16 _uiTimedelay;
   
   
public:
 	  void Init();

    //Avanca os estados da maquina de estados 
    void Run();
  
 
};

extern C_Ensaio  Ensaio;
#endif 
