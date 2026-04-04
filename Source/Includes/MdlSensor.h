#ifndef _MDL_SENSOR_
#define _MDL_SENSOR_

#include "InventTypes.h"
#include <stdint.h>


enum{
FUNC_1=1,
FUNC_2,
FUNC_3,
FUNC_4,
FUNC_5,
FUNC_6,
FUNC_7,
FUNC_8,
FUNC_9,
FUNC_10,
FUNC_11,
FUNC_12
};



typedef enum{
	eS0S1,
	eS0S2,
	eS0S3,
	eS0S4,
	eLargura,
    eMassa,
	emaxSensor
}eSensorsDistance;


typedef enum{
	eS0,
	eS1,
	eS2,
	eS3,
	eS4,
}eSensor;

//!Coloca todas as variáveis do teste dentro de uma estrutura 
typedef struct{
 uint16_t uiNEnsaio[11];  //! Número do ensaio a ser executado 
 uint32_t tempos[11];
 uint32_t tempos2[11];
 uint32_t S1tempos[11];
 uint32_t S1tempos2[11];
 uint32_t S0vtempos[11];
 uint32_t S0vtempos2[11];
 float fvelocidade[11];
 float ffrequencia[11];
 float fTempoFinal[11];
 float fTempoFinal_S0[11];
 float fTempoFinal_S1[11]; 
 float energia ;
 float tempo;
 float tempo2;
 float fAcel;

 long massa ;

}sDigital;

 
#define LCD_NUM_COLUNAS  16
	
class C_Sensor{
private:
    uint16_t _uiValue[emaxSensor];    //Valor para das grandezas 
    uint8_t  _uiNumInterval;          //! Número de intervalos 1 a 10 

		
    int8_t  _scPosicaoDigito;  //Posição do digito para a entrada de dados
    
  

public:
   bool blevel[5];            //! para indicar se ja acionou ou não 

   sDigital Result;  //valores dos ensaios 
    
 	 
  //! Inicialização das variaveis do módulo 
  void Init();
 
  //! Leitura do valor da distancia 
  uint16_t GetValue(eSensorsDistance eIndex);  
  //!Atualiza a distancia   up/down
  void  UpdateReading(uint8_t tecla,eSensorsDistance eIndex ); 

 
   void  IncNumInterval(uint8_t tecla);
   uint8_t GetNumInterval();  
  
  
  //Nivel do sensor 
  uint8_t GetLevel(uint16_t eIndex );
 
  //!Calcula a função 1 
  void CalcFunc1(void);

  //!Calcula a função 2 
  void CalcFunc2(void);

  //!Calcula a função 3 
  //void CalcFunc3(void);

  //!Calcula a função 3 4 6 7 8
  void CalcFunc_3467810();
  
  //!Calcula a função 4 
   void CalcFunc5_12(void);
  
  //!Incrementa o número do experimento 
  void IncExperimento(uint16_t uiFunc);

};

extern C_Sensor SensorDigital;

#endif 
