/********************************** NOME DO MODULO *******************************************//**
*\file     HdsDma.cpp
 
*\details    Rotina que inicia a convers�o do Ad pelo DMA
*            Salva a convers�o nas vari�vies de leitura do AD 
*
*          

* ----------------------------------------------------------------------------------------------
* \version   s.00 - Primeira vers�o documentada
* \date      23/03/2021
***********************************************************************************************/
#include "InventTypes.h"
#include "HdsMux.h"
#include "HdsDma.h"
#include "main.h"
#include "MdlSensor.h"
#include "HdsGpio.h"

//#define NUM_SAMPLES_AD 70


uint32_t ulDmaAdValues[5];   //Valores onde ser�o armazenadas as leituras 

//uint32_t ulDmaBuf[5][NUM_SAMPLES_AD];   //bUFFER DAS LEIURAS 

uint32_t ulIndexbufIn;

float fReadingAverage[5];
float fAlphaCte=0.08;
boolean bRunning=false;

/*
Rotina que dispara uma leitura do Ad, chamada pelo muxtimers
*/
void DmaStartAD(){

  HAL_ADC_Start_DMA(&hadc1,&ulDmaAdValues[0],5);
} 


/*
Rotina Configura o muxtimer para leiura do AD, a cada 1ms 
*/

void DmaStartAdReading(float fcte){
   //! usa uma cte para analogico e uma para o digital
    fAlphaCte=fcte;
 if(! bRunning){
 //!J� Inicia a convers�o dos canais do AD a casa 1ms 
    MuxTimers.LoopRun(ucMUX_SENSOR_LE_AD,1,DmaStartAD);
   bRunning=true;
   }
}

/*
Rotina para o muxtimer de leiura do AD 
*/
void DmaStopAdReading(){
 //!J� Inicia a convers�o dos canais do AD a casa 1ms 
    MuxTimers.Stop(ucMUX_SENSOR_LE_AD);

    bRunning=false;
}

/*
Retorna a m�dia das leituras 
*/
uint32_t DmaGetReading (uint8_t index   ){

//float  fvalue=0;
//
// for(uint32_t i=0; i < NUM_SAMPLES_AD; i++){
//   fvalue+= ulDmaBuf[index][i];
//  }
//
//  fvalue=fvalue/NUM_SAMPLES_AD;
//  return (uint32_t)fvalue;
//

  return (uint32_t)fReadingAverage[index];

}



/*
Chamada no final da convers�o do Dma para colocar a informa��o no buffer 
buffer de 10 amostras

*/
//void DmaEndconversion (){
//
//  //Salva  as leituras no buffer 
// for(uint32_t i=0; i<5; i++){
//   ulDmaBuf[i][ulIndexbufIn]= ulDmaAdValues[i];
//   }   
// 
// 
//
//
// //incrementa o ponteiro
//   ulIndexbufIn++;
//
//   if(ulIndexbufIn>=NUM_SAMPLES_AD)
//     ulIndexbufIn=0;
//
//  SensorDigital.ProcessAdValues();
//
//}

/*********************************************************************************************//**
 * \function    DmaEndconversion ()
 * \details     Fun��o chamada ao final pelo dma ao final da convers�o 
 *              usa a Media movel exponencial  
 *              Tempo de convers�o de 17us 
 * \author      
 * \date        04/03/2022
 ************************************************************************************************/

void DmaEndconversion (){
float fvalue;
 //Gpio.Write( Led,ePortHigh); 


  //Salva  as leituras no buffer 
 for(uint32_t i=0; i<5; i++){
  // ulDmaBuf[i][ulIndexbufIn]= ulDmaAdValues[i];
   
     fvalue= (fAlphaCte*ulDmaAdValues[i])+ ((1-fAlphaCte)*fReadingAverage[i]);
     fReadingAverage[i]=fvalue;
 }   
 
// Gpio.Write( Led,ePortLow);
}












