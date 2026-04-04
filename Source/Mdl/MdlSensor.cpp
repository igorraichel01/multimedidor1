/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlSensor.cpp
 
 *\details   Módulo para tratamento e armazenamento das informações dos sensores digitais 
 *           Informações de tempo, distancia, Massa	
 *		
 *
 *           Quando o ensaio é digital, as conversões são chamadas pela interrupção do timer 
             A conversão do Ad dura 10us a int do timer é 50us   




//Sensor de temperatua 



 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "main.h"
#include "MdlSensor.h"
#include "KBD2.h"
#include <stdio.h>
#include <string.h>
#include "MdlLcd.h"
#include "HdsDma.h"


/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Sensor SensorDigital;
extern void clock1_isr();

/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o sensor 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_Sensor::Init(void) {
    uint8_t i;
    _uiNumInterval = 1;
    _scPosicaoDigito = 2;

    //posiciona cursor
    Lcd.SetCursorOFF();


   
    for (i=0; i<11; i++){
      SensorDigital.Result.fTempoFinal[i]= 0;
      SensorDigital.Result.fvelocidade[i] = 0;
      SensorDigital.Result.ffrequencia[i] = 0;
      SensorDigital.Result.fTempoFinal_S0[i] = 0;
      SensorDigital.Result.fTempoFinal_S1[i] = 0;  
    }

  //! Zera as distancia  
     for (i = 0; i < emaxSensor; i++){
        _uiValue[i] = 0;
        }   
  
     
   for (i = 0; i <= eS4; i++){
        blevel[i]=true;
     } 


//	 Lcd.SetCursorPosition( 7-_scPosicaoDigito,LCD_LINHA_2);

//Inicializa o timer para contagem de tempo timer de 50us

    RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;  //! habilita o clock do Timer 6
    TIM10->CR1 = TIM_CR1_CEN;  						//! Habilita o contador
    TIM10->CR2 = 0x0000; 								//! control register 2
    TIM10->PSC = 01;  										//! timer Prescaler
    TIM10->ARR = 2100 - 1;    									//! Auto reload
    TIM10->DIER |= TIM_DIER_UIE;  					//! Habilita interrupção
    TIM10->EGR = TIM_EGR_UG; //! Reinicializa o timer e gera uma atualização dos registros

    NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn);  //! Habilita a interrupção do timer
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0); //! define a prioridade  0 é a mais alta
}


/*********************************************************************************************//**
 * \function        GetLevel
 * \details      Leitura do nivel do sensor 

 * \author     
 * \date        19/08/2022
 ************************************************************************************************/
uint8_t C_Sensor::GetLevel(uint16_t eIndex ) {
   bool bRet= false;
   switch  (eIndex){
        case eS0:
        bRet=Gpio.Read (Sensor0);
        break;
        case eS1:
            bRet=Gpio.Read (Sensor1);
        break;
        case eS2:
            bRet=Gpio.Read (Sensor2);
        break;
        case eS3:
             bRet=Gpio.Read (Sensor3);
        break;
        case eS4:
            bRet=Gpio.Read (Sensor4);
        break;
        default:
        break;
    }
 return bRet;
}



/*********************************************************************************************//**
 * \function        GetValue
 * \details      Leitura do valor da distancia 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
uint16_t C_Sensor::GetValue(eSensorsDistance eIndex) {
    return _uiValue[eIndex];
}

/*********************************************************************************************//**
 * \function        UpdateReading
 * \details      incrementa/Decrementa a Leitura 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_Sensor::UpdateReading(uint8_t tecla, eSensorsDistance eIndex) {

    int16_t iValue[4];       //0 unidade/ 1 dezena / 2 centena / 3 milhar

    // 7825

    iValue[3] = _uiValue[eIndex] / 1000;  //7
    iValue[2] = _uiValue[eIndex] % 1000; //825
    iValue[1] = iValue[2] % 100;    //25
    iValue[0] = iValue[1] % 10;    //5
    iValue[2] = iValue[2] / 100;   //8
    iValue[1] = iValue[1] / 10;    //2

    switch (tecla) {

    case TECLA_DIR:
        _scPosicaoDigito--;

        if (_scPosicaoDigito < 0)
            _scPosicaoDigito = 3;

        //posiciona o cursor
        if((_scPosicaoDigito==3) && (eIndex==eMassa))
            Lcd.SetCursorPosition(7 - _scPosicaoDigito-1, LCD_LINHA_2);
           else
            Lcd.SetCursorPosition(7 - _scPosicaoDigito, LCD_LINHA_2);

        break;

    case TECLA_ESQ:
        _scPosicaoDigito++;
        if (_scPosicaoDigito > 3)
            _scPosicaoDigito = 0;

        //posiciona o cursor
        if((_scPosicaoDigito==3) && (eIndex==eMassa))
            Lcd.SetCursorPosition(7 - _scPosicaoDigito-1, LCD_LINHA_2);
           else
        Lcd.SetCursorPosition(7 - _scPosicaoDigito, LCD_LINHA_2);

        break;

    case DESCE:
        iValue[_scPosicaoDigito]--;
        if (iValue[_scPosicaoDigito] < 0)
            iValue[_scPosicaoDigito] = 9;

        break;

    case SOBE:
        iValue[_scPosicaoDigito]++;
        if (iValue[_scPosicaoDigito] > 9)
            iValue[_scPosicaoDigito] = 0;

        break;

    default:
        break;
    }

    _uiValue[eIndex] = iValue[3] * 1000 + iValue[2] * 100 + iValue[1] * 10
            + iValue[0];

}





/*********************************************************************************************//**
 * \function        IncNumInterval
 * \details      Numero intervalos

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_Sensor::IncNumInterval(uint8_t tecla) {

    int16_t iValue[2];       //0 unidade/ 1 dezena 

    iValue[0] = _uiNumInterval % 10;    //
    iValue[1] = _uiNumInterval / 10;    //

    if (_scPosicaoDigito > 1)
        _scPosicaoDigito = 0;


    switch (tecla) {

    case TECLA_DIR:
        _scPosicaoDigito--;

        if (_scPosicaoDigito < 0)
            _scPosicaoDigito = 1;

        //posiciona o cursor
         Lcd.SetCursorPosition(7 - _scPosicaoDigito, LCD_LINHA_2);

        break;

    case TECLA_ESQ:
        _scPosicaoDigito++;
        if (_scPosicaoDigito > 1)
            _scPosicaoDigito = 0;

        //posiciona o cursor
        Lcd.SetCursorPosition(7 - _scPosicaoDigito, LCD_LINHA_2);

        break;

    case DESCE:
        iValue[_scPosicaoDigito]--;
        if (iValue[_scPosicaoDigito] < 0){
            iValue[_scPosicaoDigito] = 9;
            
            }

        break;

    case SOBE:
        iValue[_scPosicaoDigito]++;
        if (iValue[_scPosicaoDigito] > 9){
            iValue[_scPosicaoDigito] = 0;
            
           } 

        break;

    default:
        break;
    }

    _uiNumInterval = iValue[1] * 10 + iValue[0];

     if (_uiNumInterval > 10)
            _uiNumInterval = 10;
        else if(_uiNumInterval ==0)
            _uiNumInterval = 1;
        else{}
}




/*********************************************************************************************//**
 * \function        GetNumInterval
 * \details      Retorna o Numero de intevalos programados 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
uint8_t C_Sensor::GetNumInterval() {
    return _uiNumInterval;
}




/*********************************************************************************************//**
 * \function     CalcFunc1
 * \details      calcula o resultado da Funcão 1 
 *               pode ser 2 ou 5 sensores, calcula velocidade entre o sensor 0 e outros sensores e entre outros sensores 
                 indice 0= 0->1
 *                       1= 0->2
 *                       2= 0->3
 *                       3= 0->4
 *                       4= 1->2
 *                       5= 2->3
 *                       6= 3->4
 

primeira linha tempos     0->1,0->2,0->3,0->4,1->2,2->3,3->4
Segunda linha velocidade  0->1,0->2,0->3,0->4,1->2,2->3,3->4

 
 * \author     
 * \date        28/09/2022
 ************************************************************************************************/
void C_Sensor:: CalcFunc1(void){
   uint8_t i;
   // de 0 a 3
    for (i=0; i<=3; i++){
      SensorDigital.Result.fTempoFinal[i]= (((float) SensorDigital.Result.tempos2[i] * 100) + ((float) SensorDigital.Result.tempos[i] / 100))/1000;
      SensorDigital.Result.fvelocidade[i] = ((float) SensorDigital.GetValue((eSensorsDistance) i)/1000) / SensorDigital.Result.fTempoFinal[i];  //! distancia em mm precisa ser em m/s
    }
   //calcula tempo e velocidade entre S1 e S2 
    SensorDigital.Result.fTempoFinal[4]= SensorDigital.Result.fTempoFinal[1]-SensorDigital.Result.fTempoFinal[0];
    SensorDigital.Result.fvelocidade[4] = (((float) (SensorDigital.GetValue(eS0S2)- SensorDigital.GetValue(eS0S1)))/1000) /SensorDigital.Result.fTempoFinal[4];  //! distancia em mm precisa ser em m/s

   //calcula tempo e velocidade entre S2 e S3 
    SensorDigital.Result.fTempoFinal[5]= SensorDigital.Result.fTempoFinal[2]-SensorDigital.Result.fTempoFinal[1];
    SensorDigital.Result.fvelocidade[5] = ((float) (SensorDigital.GetValue(eS0S3)- SensorDigital.GetValue(eS0S2))/1000) /SensorDigital.Result.fTempoFinal[5];  //! distancia em mm precisa ser em m/s

    //calcula tempo e velocidade entre S3 e S4  
    SensorDigital.Result.fTempoFinal[6]= SensorDigital.Result.fTempoFinal[3]-SensorDigital.Result.fTempoFinal[2];
    SensorDigital.Result.fvelocidade[6] = ((float) (SensorDigital.GetValue(eS0S4)- SensorDigital.GetValue(eS0S3))/1000) /SensorDigital.Result.fTempoFinal[6];  //! distancia em mm precisa ser em m/s

}

/*********************************************************************************************//**
 * \function     CalcFunc2
 * \details      calcula o resultado da Funcão 1 

 
 * \author     
 * \date        28/09/2022
 ************************************************************************************************/
void C_Sensor:: CalcFunc2(void){
  SensorDigital.Result.fTempoFinal[0]= (((float) SensorDigital.Result.tempos2[0] * 100) + ((float) SensorDigital.Result.tempos[0] / 100))/1000;
  SensorDigital.Result.fvelocidade[0] = ((float) SensorDigital.GetValue(eLargura)/1000) / SensorDigital.Result.fTempoFinal[0];  //! distancia em mm precisa ser em m/s
}

     
/*********************************************************************************************//**
 * \function     CalcFunc3
 * \details      calcula o resultado da Funcão 3   eda função 6 
                 São 10 tempo de passagem 
 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
//void C_Sensor:: CalcFunc3(void){
//   uint8_t i;
//     
//    for (i=0; i<11; i++){
//     SensorDigital.Result.fTempoFinal[i]= (((float) SensorDigital.Result.tempos2[i] * 100) + ((float) SensorDigital.Result.tempos[i] / 100))/1000;
//     //Salva a frequencia no campo velocidade usada na funcao 6 
//     SensorDigital.Result.fvelocidade[i]=1/SensorDigital.Result.fTempoFinal[i];
//    }
//}

/*********************************************************************************************//**
 * \function     CalcFunc4
 * \details      calcula o resultado da Funcão 3,4, 6, 7,  8, e 10  
                 São 10 tempo de passagem 
 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
void C_Sensor:: CalcFunc_3467810(void){
   uint8_t i;
     
    for (i=0; i<11; i++){
     
     //func 3, 4, 6, 7 e 8
     SensorDigital.Result.fTempoFinal[i]= (((float) SensorDigital.Result.tempos2[i] * 100) + ((float) SensorDigital.Result.tempos[i] / 100))/1000;
  
     //func 3, 4
     SensorDigital.Result.ffrequencia[i]=1/SensorDigital.Result.fTempoFinal[i];
     
     //Func 7 func 8 
     SensorDigital.Result.fTempoFinal_S1[i]= (((float) SensorDigital.Result.S1tempos2[i] * 100) + ((float) SensorDigital.Result.S1tempos[i] / 100))/1000;

     //func 8
     SensorDigital.Result.fTempoFinal_S0[i]= (((float) SensorDigital.Result.S0vtempos2[i] * 100) + ((float) SensorDigital.Result.S0vtempos[i] / 100))/1000;
    

    }
}


/*********************************************************************************************//**
 * \function     CalcFunc1
 * \details      calcula o resultado da Funcão 1 
                salva tempo, velocidade, aceleração e velocidade final


 
 * \author     
 * \date        28/09/2022
 ************************************************************************************************/
void C_Sensor:: CalcFunc5_12(void){
  
  SensorDigital.Result.fTempoFinal[0]= (((float) SensorDigital.Result.tempos2[0] * 100) + ((float) SensorDigital.Result.tempos[0] / 100))/1000;
  SensorDigital.Result.fvelocidade[0] = ((float) SensorDigital.GetValue(eLargura)/1000) / SensorDigital.Result.fTempoFinal[0];  //! distancia em mm precisa ser em m/s
  SensorDigital.Result.fAcel=SensorDigital.Result.fvelocidade[0]/SensorDigital.Result.fTempoFinal[0];
 
  //Aceleração multiplicada por 2 ????   fw original estava assim
  SensorDigital.Result.fAcel*=2;  
  
  //!Resultado para a função 12
  SensorDigital.Result.energia = (float) SensorDigital.Result.massa * SensorDigital.Result.fvelocidade[0] * SensorDigital.Result.fvelocidade[0] / 2;
  SensorDigital.Result.energia=SensorDigital.Result.energia/1000;
}

  


/*********************************************************************************************//**
 * \function     IncExperimento
 * \details      calcula o resultado da Funcão 1 

 
 * \author     
 * \date        28/09/2022
 ************************************************************************************************/
void C_Sensor:: IncExperimento(uint16_t uiFunc){
    if(uiFunc>FUNC_12)
       return;

Result.uiNEnsaio[uiFunc-1]++;

}








/*********************************************************************************************//**
 * \function    HAL_GPIO_EXTI_Callback
 * \details     Função chamada a cada interrupção dos pinos digitais 
 * 
 * \author      
 * \date        14/11/2022
 ************************************************************************************************/
 extern char portab;
 extern void int_sensorS0(bool bBorda);
 extern void int_sensores();
 extern int sensor0;
 extern int sensor1;
 extern int sensor2;
 extern int sensor3;
 extern int sensor4;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

switch (GPIO_Pin){

  case Sensor0_Pin:
     portab = sensor0;
     
     //analisa se borda de descida ou borda de subida
      if(Gpio.Read (Sensor0)){
        //De 0 para 1  borda de subida
           int_sensorS0(1);
         SensorDigital.blevel[eS0]=true;  
        }
        else{

         int_sensorS0(0);
         SensorDigital.blevel[eS0]=false;   
        }


    break;
  case Sensor1_Pin:
     portab = sensor1;

      if(Gpio.Read (Sensor1)){
        SensorDigital.blevel[eS1]=true;  
        }
        else{
        SensorDigital.blevel[eS1]=false;   
        }

     int_sensores(); 

    break;

    case Sensor2_Pin:
     portab = sensor2;
     if(Gpio.Read (Sensor2)){
        SensorDigital.blevel[eS2]=true;  
        }
        else{
        SensorDigital.blevel[eS2]=false;   
        }
      int_sensores(); 

    break;

    case Sensor3_Pin:
     portab = sensor3;
    if(Gpio.Read (Sensor3)){
        SensorDigital.blevel[eS3]=true;  
        }
        else{
        SensorDigital.blevel[eS3]=false;   
        }


      int_sensores(); 

    break;

    case Sensor4_Pin:
     portab = sensor4;
     if(Gpio.Read (Sensor4)){
        SensorDigital.blevel[eS4]=true;  
        }
        else{
        SensorDigital.blevel[eS4]=false;   
        }
     int_sensores(); 
     break;

 }



/*
uint32_t ulLeitura;

    if(!_bEnableSensors)
        return;

  if(DmaGetReading(0)>=NIVEL_BAIXO ){
 
      if(blevel[eS0]==false){
      Gpio.Write( Led,ePortHigh); 
      portab = sensor0;
      int_sensorS0(1); 
      blevel[eS0]=true;  
      }
    }
    else{
     if(blevel[eS0]==true){
      Gpio.Write( Led,ePortLow);   
      portab = sensor0;
      int_sensorS0(0); 
      blevel[eS0]=false; 
     }
     
   }
  

 if( DmaGetReading(1)<=NIVEL_BAIXO){
     if(blevel[eS1]==true){ 
      portab = sensor1;
      int_sensores(); 
      blevel[eS1]=false;
      }
    } 
    else{ 
       blevel[eS1]=true; 
    }  


 if( DmaGetReading(2)<=NIVEL_BAIXO){
     if(blevel[eS2]==true){ 
      portab = sensor2;
      int_sensores(); 
      blevel[eS2]=false;
      }
    } 
    else{ 
       blevel[eS2]=true; 
    } 

  if( DmaGetReading(3)<=NIVEL_BAIXO){
     if(blevel[eS3]==true){ 
      portab = sensor3;
      int_sensores(); 
      blevel[eS3]=false;
      }
    } 
    else{ 
       blevel[eS3]=true; 
    } 

 if( DmaGetReading(4)<=NIVEL_BAIXO){
     if(blevel[eS4]==true){ 
      portab = sensor4;
      int_sensores(); 
      blevel[eS4]=false;
      }
    } 
    else{ 
       blevel[eS4]=true; 
    } 
*/ 
}





/*********************************************************************************************//**
 * \fn         TIM16_IRQHandler
 * \brief      interrupção de 50us para contagem de tempo dos temporizadores 
 * \details    
 * \author     
 * \date       20/01/2022
 ************************************************************************************************/
extern "C" void TIM1_UP_TIM10_IRQHandler(void) {

    //! Verifica se a interrupção gerada no TIM16 é de atualização do contador
    if ((TIM10->SR & TIM_SR_UIF) != 0) {

        //! chama os timers
        clock1_isr();

        //! Limpa flag do timer
        TIM10->SR &= (~(TIM_SR_UIF));
   
     //   DmaStartAD();
        

    }
}

