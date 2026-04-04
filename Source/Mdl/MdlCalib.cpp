/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlCalib.cpp
 
 *\details   Rotinas de Calibração 
 *		
 *

 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "MdlCalib.h"
#include "MdlUtil.h"
#include "HdsIFlash.h"
#include <stdio.h>
#include <string.h>

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Calib Calib;






/*********************************************************************************************//**
 * \function       Restore
 * \details   recupera a calibração da Flash

 * \author     
 * \date        20/11/2021
 ************************************************************************************************/
void C_Calib::Restore(void) {
  
  SGain *Gainflash= (SGain*)SAVE_DATA_ADDRESS;

  Gain= *Gainflash;

}




/*********************************************************************************************//**
 * \function        Restore
 * \details   Inicializa a Calibração. Se crc correto carrega o valor de calibração para os sensores 
              //Se crc inválido carrega valor default  

 * \author     
 * \date        14/09/2021
 ************************************************************************************************/
void C_Calib::Validate(boolean bRestore) {

if(!CheckCrc() || bRestore){
     
   //Temperatura
    Gain.Value[eTemperature].fReadingLow=0.286080569;
    Gain.Value[eTemperature].fReadingHigh=0.509304047;   
    Gain.Value[eTemperature].fValueHigh=51;
    Gain.Value[eTemperature].fValueLow=4;
    CalculaCte(eTemperature); 

    // pressão 
    Gain.Value[ePressure].fReadingLow=0.173260078;
    Gain.Value[ePressure].fReadingHigh=0.926739931;   
    Gain.Value[ePressure].fValueHigh=240.100006;
    Gain.Value[ePressure].fValueLow=51;
         CalculaCte(ePressure); 

    Gain.Value[eForca].fReadingLow=0.0;
    Gain.Value[eForca].fReadingHigh=1.06695974;   
    Gain.Value[eForca].fValueHigh=9.80000019;
    Gain.Value[eForca].fValueLow=0;
    CalculaCte(eForca); 


//pressao diferencial 
    Gain.Value[ePressureDiferencial].fReadingLow=0.0556043945;
    Gain.Value[ePressureDiferencial].fReadingHigh=0.734945059;   
    Gain.Value[ePressureDiferencial].fValueHigh=181;
    Gain.Value[ePressureDiferencial].fValueLow=11.6000004;
    CalculaCte(ePressureDiferencial); 

Gain.Value[eIntensidadeLuminosa].fReadingLow=0.173260078;
    Gain.Value[eIntensidadeLuminosa].fReadingHigh=0.926739931;   
    Gain.Value[eIntensidadeLuminosa].fValueHigh=240.100006;
    Gain.Value[eIntensidadeLuminosa].fValueLow=51;
     CalculaCte(eIntensidadeLuminosa); 

    //voltage 
    Gain.Value[eVoltage_menos_20_mais_20].fReadingLow=0.238534793;
    Gain.Value[eVoltage_menos_20_mais_20].fReadingHigh=0.776849806;   
    Gain.Value[eVoltage_menos_20_mais_20].fValueHigh=10.0;
    Gain.Value[eVoltage_menos_20_mais_20].fValueLow=-10.0;
    CalculaCte(eVoltage_menos_20_mais_20); 

      Gain.Value[eCurrent_menos_200_mais_200].fReadingLow=0.173260078;
    Gain.Value[eCurrent_menos_200_mais_200].fReadingHigh=0.926739931;   
    Gain.Value[eCurrent_menos_200_mais_200].fValueHigh=240.100006;
    Gain.Value[eCurrent_menos_200_mais_200].fValueLow=51;
     CalculaCte(eCurrent_menos_200_mais_200); 

  Gain.Value[eCurrent_menos_20_mais_20].fReadingLow=0.173260078;
    Gain.Value[eCurrent_menos_20_mais_20].fReadingHigh=0.926739931;   
    Gain.Value[eCurrent_menos_20_mais_20].fValueHigh=240.100006;
    Gain.Value[eCurrent_menos_20_mais_20].fValueLow=51;
     CalculaCte(eCurrent_menos_20_mais_20); 

  Gain.Value[eCampoMagnetico].fReadingLow=0.485934049;
    Gain.Value[eCampoMagnetico].fReadingHigh=0.784102559;   
    Gain.Value[eCampoMagnetico].fValueHigh=7;
    Gain.Value[eCampoMagnetico].fValueLow=0.400000006;
     CalculaCte(eCampoMagnetico); 

    Gain.Value[eFluxo].fReadingLow=0.113626368;
    Gain.Value[eFluxo].fReadingHigh=0.356996328;   
    Gain.Value[eFluxo].fValueHigh=4.5;
    Gain.Value[eFluxo].fValueLow=1.60000002;
    CalculaCte(eFluxo); 





     Save();
      
   }
}


/*********************************************************************************************//**
 * \function        Save
 * \details   Salva os dados na flash interna 

 * \author     
 * \date        14/09/2021
 ************************************************************************************************/
void C_Calib::Save(void) {
   _UpdateCrc();
  
   uint32_t ulSize=((uint32_t) & (Gain.ulCrc) - (uint32_t) &Gain);

   FlashStm32.Flash_Write_Data (SAVE_DATA_ADDRESS,(uint32_t * )&Gain, ulSize+2);  //Crc + 1 palavra

}


/*********************************************************************************************//**
 * \function      CalculaCte 
 * \details   Calcula a constantes do sensor selecionado 
                offset= leiura baixa
                alfa= inclinação= (leitura alta-offset)/100   
                100> diferença entre a temperatura baixa e temeratura alta
                
 * \author     
 * \date        20/09/2022
 * \date        19/10/2022
 ************************************************************************************************/
void C_Calib::CalculaCte(eSensorType eType) {
 
  Gain.Value[eType].foffset=Gain.Value[eType].fReadingLow;
  Gain.Value[eType].fAlfa= (Gain.Value[eType].fReadingHigh-Gain.Value[eType].fReadingLow)/(Gain.Value[eType].fValueHigh-Gain.Value[eType].fValueLow);

}


/*********************************************************************************************//**
 * \function      CalculaCtePressao 
 * \details   Calcula as constantes de pressao
                
                
 * \author     
 * \date        22/09/2022
 ************************************************************************************************/
//void C_Calib::CalculaCtePressao(void) {
//  Gain.offsetPressao=Gain.ReadingPressaoLow;
//
//  Gain.AlfaPressao=(Gain.ReadingPressaoHigh-Gain.ReadingPressaoLow)/(Gain.PressaoHigh-Gain.PressaoLow);
//
//  _UpdateCrc();
//   Save();
//}



/*********************************************************************************************//**
 * \function        CheckCrc
 * \details   Verifica se o Crc esta correto 

 * \author     
 * \date        14/09/2021
 ************************************************************************************************/
bool C_Calib::CheckCrc(void) {
    uint32_t ulSize=((uint32_t) & (Gain.ulCrc) - (uint32_t) &Gain);
             
   if(Gain.ulCrc == Util.Crc32((uint8_t*)&Gain, ulSize))
      return true;
    else
      return false;
}


/*********************************************************************************************//**
 * \function        _UpdateCrc
 * \details   Atualiza o Crc da estrutura 

 * \author     
 * \date        14/09/2021
 ************************************************************************************************/
void C_Calib::_UpdateCrc(void) {
   uint32_t size=((uint32_t) & (Gain.ulCrc) - (uint32_t) &Gain);

   Gain.ulCrc=Util.Crc32((uint8_t *) &Gain ,size);
}
