#ifndef _MDL_CALIB_
#define _MDL_CALIB_

#include "InventTypes.h"
#include <stdint.h>

/*
Calibração da temperatura
em 0 graus temos o valor de offset 
em 100 graus temos a inclinação da reta ( valor de graus/milivolts
Vmilivolts= alfa*temperatura+offset

temperaura=(Vmilivolts-offset)/alfa

*/



typedef enum {
    ePressure,
    eTemperature,
    eForca,//CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
    ePressureDiferencial,//CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
    eIntensidadeLuminosa,//CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
    eVoltage_menos_20_mais_20,//CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
    eCurrent_menos_200_mais_200,//CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
    eCurrent_menos_20_mais_20,//CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
    eCampoMagnetico,//CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
    eFluxo,//CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
    eNumSensor    //Quantidade de sensores na lista
 } eSensorType;



typedef struct{
float fReadingLow;    //!leitura em mv do ajuste baixo
float fReadingHigh;   //!leitura em mv do ajuste Alto 
float fValueLow;      //!Grandeza valor baixo 
float fValueHigh;     //!Grandeza valor Alto
float foffset;
float fAlfa;

}SensorGain;



typedef struct{
//float ReadingTemperaturaLow;    //!leitura em mv do ajuste baixo
//float ReadingTemperaturaHigh;   //!leitura em mv do ajuste Alto 
//float TemperaturaLow;           //!Temperatura baixa de calibração
//float TemperaturaHigh;          //!Temperatura Alta de calibração
//float offsetTemperatura;
//float AlfaTemperatura;
//
//
//float ReadingPressaoLow;    //!leitura em mv do ajuste baixo
//float ReadingPressaoHigh;   //!leitura em mv do ajuste Alto 
//float PressaoLow;           //!Temperatura baixa de calibração
//float PressaoHigh;          //!Temperatura Alta de calibração
//float offsetPressao;
//float AlfaPressao;

SensorGain Value[eNumSensor];

uint32_t ulCrc;
}SGain;

	
class C_Calib{
private:
   void _UpdateCrc(void);
   
 
public:
    SGain Gain;
    void Restore(void); 
    void Validate(boolean bRestore); 
    void Save(void) ;
    bool CheckCrc(void); 
    //void CalculaCteTemperatura(void);
    void CalculaCte(eSensorType eType);
    //void CalculaCtePressao(void); 

};

extern C_Calib Calib;
#endif 
