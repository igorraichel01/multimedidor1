/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlSensorAnalogico.cpp
 
 *\details   Módulo para tratamento e armazenamento das informações dos sensores analoicos 
 *           A classe trata apenas um sensor
 *		     utiliza o muxtimers para salvar a leitura do AD no tempo que foi configurado no ensaio
 *

 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "MdlSensorAnalog.h"
#include "KBD2.h"
#include <stdio.h>
#include <string.h>
#include "MdlLcd.h"
#include "HdsMux.h"
#include "Main.h"
#include "File_Handling.h"
#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "HdsDma.h"


/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_SensorAnalog AnalogS0;
C_SensorAnalog AnalogS1;
C_SensorAnalog AnalogS2;
C_SensorAnalog AnalogS3;
C_SensorAnalog AnalogS4;



//As funções abaixo são chamadas pelo muxtimers na frequecia da taxa de amostragem configuradas no ensaio
// uma pode se chamada a casa 10ms e outra a cada 300m

void StoreReadingSense0(){
  AnalogS0.AddToBuffer( DmaGetReading(0));
}

void StoreReadingSense1(){
   AnalogS1.AddToBuffer(DmaGetReading(1));
}

void StoreReadingSense2(){
   AnalogS2.AddToBuffer(DmaGetReading(2));
}

void StoreReadingSense3(){
   AnalogS3.AddToBuffer(DmaGetReading(3));
  
}

void StoreReadingSense4(){
   AnalogS4.AddToBuffer(DmaGetReading(4));
}



/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o sensor 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_SensorAnalog::Init(uint8 ucindex) {
    
    IndexMuxTimer=ucindex;
    
    bSensorEnabled=false; 

    //Zera os valores
    // for(uint8_t i=0; i<eNumValues;i++)
    //  _uiTimeValue[i]=0;

    _uiTimeLimit[eMinimumSampleTime]=100;  //tempo em ms 
    _uiTimeLimit[eMaximumExcutionTime]=10; //tempo em segundos  

    _uiTimeValue[eSampleTime] =  _uiTimeLimit[eMinimumSampleTime];  
    _uiTimeValue[eExcutionTime] =_uiTimeLimit[eMaximumExcutionTime];  
    _uiTimeValue[eRunningTime] = 0;

    _scPosicaoDigito=2;

    //! carrega o ganho conforme o sensor utilizado 
    _Gain=Calib.Gain.Value[_scSensorType];
}

/*********************************************************************************************//**
 * \function        GetValue
 * \details      Leitura do valor da distancia 

 * \author     
 * \date        09/02/2022
 ************************************************************************************************/
uint16_t C_SensorAnalog::GetValue(eSensorTime eValue) {
    return _uiTimeValue[eValue];
}


/*********************************************************************************************//**
 * \function        SetTestTime
 * \details     Configura o valor do tempo de teste, usado no modo indicador 

 * \author     
 * \date        07/05/2022
 ************************************************************************************************/
void C_SensorAnalog::SetTestTime(uint16_t uiValue) {
    _uiTimeValue[eExcutionTime]= uiValue;
}


/*********************************************************************************************//**
 * \function        SetSampleTime
 * \details     Configura o valor do tempo de amostrageme usado no modo indicador 

 * \author     
 * \date        09/05/2022
 ************************************************************************************************/
void C_SensorAnalog::SetSampleTime(uint16_t uiValue) {
    _uiTimeValue[eSampleTime]= uiValue;
}



/*********************************************************************************************//**
 * \function        UpdateReading
 * \details      incrementa/Decrementa a Leitura 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_SensorAnalog::UpdateValue(uint8_t tecla, eSensorTime eValue) {

    int16_t iValue[4];       //0 unidade/ 1 dezena / 2 centena / 3 milhar

    // 7825

    iValue[3] = _uiTimeValue[eValue] / 1000;  //7
    iValue[2] = _uiTimeValue[eValue] % 1000; //825
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
        Lcd.SetCursorPosition(8 - _scPosicaoDigito, LCD_LINHA_2);

        break;

    case TECLA_ESQ:
        _scPosicaoDigito++;
        if (_scPosicaoDigito > 3)
            _scPosicaoDigito = 0;

        //posiciona o cursor
        Lcd.SetCursorPosition(8 - _scPosicaoDigito, LCD_LINHA_2);

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

    _uiTimeValue[eValue] = iValue[3] * 1000 + iValue[2] * 100 + iValue[1] * 10
            + iValue[0];

     if(eValue==eMinimumSampleTime){   
         if(_uiTimeValue[eValue] <_uiTimeLimit[eValue]){
            _uiTimeValue[eValue]=_uiTimeLimit[eValue];
            }

        //Calcula o tempo máximo do ensaio 
        _uiTimeLimit[eExcutionTime]= uint16_t ((_uiTimeValue[eValue]*NUM_SAMPLES)/1000);

     }
     else if(eValue==eExcutionTime){   
         if(_uiTimeValue[eValue] >_uiTimeLimit[eValue]){
            _uiTimeValue[eValue]=_uiTimeLimit[eValue];
            }
     } 
     else{
       }

}

/*********************************************************************************************//**
 * \function        UpdateSensor
 * \details      Aualiza o sensor que sera usado  

 * \author     
 * \date        10/02/2022
 ************************************************************************************************/
void C_SensorAnalog::UpdateSensor(uint8_t tecla) {
    
    //! aqui ja sinaliza que o Ad vai ser usado
    bSensorEnabled=true;

    switch (tecla) {

    case DESCE:
        _scSensorType--;
        if (_scSensorType < 0)
            _scSensorType = eNumSensor - 1;

        break;

    case SOBE:
        _scSensorType++;
        if (_scSensorType >= eNumSensor)
            _scSensorType = 0;

        break;

    default:
        break;
    }

}

/*********************************************************************************************//**
 * \function        GetSensor
 * \details      Retorna o sensor configurado   

 * \author     
 * \date        10/02/2022
 ************************************************************************************************/
uint16_t C_SensorAnalog::GetSensor() {
    return (uint16_t) _scSensorType;
}


/*********************************************************************************************//**
 * \function        SetSensor
 * \details      configura sensor para ajuste

 * \author     
 * \date        13/09/2022
 ************************************************************************************************/
void C_SensorAnalog::SetSensor(eSensorType Sensor) {
    _scSensorType=Sensor;
     bSensorEnabled=true;
     _scPosicaoDigito=20;   //A rotina ajusta esse valor o blink
}



/*********************************************************************************************//**
 * \function        IsRunnig
 * \details      indica se o teste ainda esta em execução, usado para sinalizar que totos os sensores finalizaram

 * \author     
 * \date        10/02/2022
 ************************************************************************************************/
bool C_SensorAnalog::IsRunnig() {

   
    if (_uiTimeValue[eRunningTime])
        return true;
    else
        return false;

}


/*********************************************************************************************//**
 * \function        bSensorEnabled
 * \details      Indica se o sensor esta habilitado. Usado para mostrar os valores 

 * \author     
 * \date        09/05/2022
 ************************************************************************************************/
bool C_SensorAnalog::IsEnabled() {

    return bSensorEnabled;

}


/*********************************************************************************************//**
 * \function        Disabled
 * \details      Desabilita o sensor e para a conversão

 * \author     
 * \date        28/08/2022
 ************************************************************************************************/
void C_SensorAnalog::Disabled() {
    bSensorEnabled=false;
    //!Para aquisição de dados
    MuxTimers.Stop(IndexMuxTimer); 

}

/*********************************************************************************************//**
 * \function        AddToBuffer
 * \details      Insere uma amostra do Ad no buffer 
 *               A leitura do ad é em 32 bits, sendo que os 16 menos significativos é que interessam 
 * \author     
 * \date        10/02/2022
 ************************************************************************************************/
void C_SensorAnalog::AddToBuffer(uint32_t ulsample) {

 //  if((uiBufIndex +1)<NUM_SAMPLES){
 //    _ulSamples[uiBufIndex++]=ulsample;
 //   }
 
  //! se já atiniu o número de amostras, não salva mais no buffer 
  if( uiBufIndex>= _uiNumSamples)
        return;

   
   //printf("Valor Ad%u   leitura=%u   Salvo= %u  index %u\n", (IndexMuxTimer- ucMUX_SENSOR_ANALOG_0),ulsample, _uiSamples[uiBufIndex-1],uiBufIndex-1 );
  
   
 _uiSamples[uiBufIndex++]=(uint16_t) ulsample;

 printf("Valor Ad%u   leitura=%u   Salvo= %u  index %u  numMax %u\n", (IndexMuxTimer- ucMUX_SENSOR_ANALOG_0),ulsample, _uiSamples[uiBufIndex-1],uiBufIndex-1,_uiNumSamples );


  //! Salva a ultima leitura para mostrar no display
  _uiLastSample= (uint16_t) ulsample; 
      
   if(uiBufIndex>= NUM_SAMPLES)
        uiBufIndex=0;

 
}


/*********************************************************************************************//**
 * \function        Start
 * \details      inicia o teste 
                 Apaga o arquivo caso ele exista    
                 Inicia um timer de leiura com o empo de amostragem 

 * \author     
 * \date        14/02/2022
 ************************************************************************************************/
void C_SensorAnalog::Start(void) {

   uint8_t filename[20];

  // sprintf( (char *)&filename,"DadosAD%u.CSV",IndexMuxTimer- ucMUX_SENSOR_ANALOG_0);  

  // Remove_File((char *)&filename);   //apaga o arquivo caso ele exista 


    if(!bSensorEnabled)
        return;

   //! carrega o ganho conforme o sensor utilizado 
   _Gain=Calib.Gain.Value[_scSensorType];    

    _eTestState = eTestStart;

    //! Dispara o muxtimers para leiura do AD  
   switch (IndexMuxTimer){

        case ucMUX_SENSOR_ANALOG_0:
         MuxTimers.LoopRun(IndexMuxTimer,_uiTimeValue[eSampleTime],StoreReadingSense0);
        break;
        case ucMUX_SENSOR_ANALOG_1:
         MuxTimers.LoopRun(IndexMuxTimer,_uiTimeValue[eSampleTime],StoreReadingSense1);
        break;
        case ucMUX_SENSOR_ANALOG_2:
         MuxTimers.LoopRun(IndexMuxTimer,_uiTimeValue[eSampleTime],StoreReadingSense2);
        break;
        case ucMUX_SENSOR_ANALOG_3:
         MuxTimers.LoopRun(IndexMuxTimer,_uiTimeValue[eSampleTime],StoreReadingSense3);
        break;
        case ucMUX_SENSOR_ANALOG_4:
         MuxTimers.LoopRun(IndexMuxTimer,_uiTimeValue[eSampleTime],StoreReadingSense4);
        break;
    }

    //! Aponta para o inicio do buffer 
     uiBufIndex=0;
   
   
    //!Avanca um estado para iniciar
    Run();
}

/*********************************************************************************************//**
 * \function        Run
 * \details      Maquina de estados de execução do teste do sensor
                 executa durante o tempo configurado e a cada segundo decrementa o tempo

 * \author     
 * \date        14/02/2022
 ************************************************************************************************/
void C_SensorAnalog::Run() {

    switch (_eTestState) {

    case eTestIdle:

        break;

    case eTestStart:

        //!se o tempo de ensaio esta zerado, não inicia
        if (_uiTimeValue[eExcutionTime] == 0) {
            _eTestState = eTestIdle;
            break;
        }

        //tempo de ensaio, coloca +1 para poder adiquirir todas as amostras 
        _uiTimeValue[eRunningTime] = _uiTimeValue[eExcutionTime]+1;

        _eTestState = eTesteRun;


         //!calcula o número de amostras pelo tempo de teste e tempo de amostragem
          float fsamples;
          fsamples= (1000.0f/_uiTimeValue[eSampleTime])*_uiTimeValue[eExcutionTime] ;

          _uiNumSamples=  (uint16_t)fsamples ;

        //printf("uiTimeValue[eRunningTime] %d\n",_uiTimeValue[eRunningTime] );        

        break;

    case eTesteRun:
        
         

        if (--_uiTimeValue[eRunningTime] == 0) {
            _eTestState = eTestDone;

            //!Para aquisição de dados
             MuxTimers.Stop(IndexMuxTimer); 
        }
        
        //printf("uiTimeValue[eRunningTime] %d\n",_uiTimeValue[eRunningTime] );      
        break;

    case eTestDone:

        break;
    }
}



/*********************************************************************************************//**
 * \function     ConvertTemp
 * \details      Converte a temperatura em um valor em graus celcius 
 *               termopar entrega 10mv/°c  o módulo dá um offset de 1,14v ( para temperauras negatvias) e um ganho de 2,75 vezes
 *               A entrada do Ad tem uma é vin*12(47+12) = 0,2024vin
 *               Vref Ad = 3V3
                 Ad de 12bits 4096 steps   

                para achar o offset e o ganho do sensor, retirar o AD595AQ e colocar um curto na saida para o gnd
                e medir a tensao depois do offset e a tensão de saída.
 

20/09/2022     Calcula a temperatura a partir dos valores de ajuste 
                temperatua= (tensao milivolts-offset)/alfa + templow (temperatura de ajuste)
20/11/2022    temperatura maxima que pode ser medida 150 gras com folga
              temperatura minima -0 graus    = 1,14/2,75  410mv  que ara chegar a zero precisa de - 40graus.
 *              
 * \author     
 * \date        04/07/2022
 ************************************************************************************************/
float C_SensorAnalog::ConvertTemp(uint16_t uiSample){

float fVmilivolts=float(3.3/4095)*float(uiSample);
//float ftemperatura=((fVmilivolts-_Gain.offsetTemperatura)/_Gain.AlfaTemperatura)+_Gain.TemperaturaLow;
float ftemperatura=((fVmilivolts-_Gain.foffset)/_Gain.fAlfa)+_Gain.fValueLow;

   return ftemperatura;
    

}


/*********************************************************************************************//**
 * \function     ConvertPressureKpa
 * \details      Converte a pressão em Kpa  sensor cl0112B.01
 *               pressão minima 20Kpa  máxima 250Kpa
 *               Vout = VCC x (P x 0.004 – 0.04) ± Error
 *               vin*12(47+12) = 0,2024vin
 
                 P=(fAdReading/5 + 0.04) / 0,004
 *               
                 Ad de 12bits 4096 steps    
 *              
 * \author     
 * \date         05/07/2022
 ************************************************************************************************/
float C_SensorAnalog::ConvertPressureKpa(uint16_t uiSample){


float fVmilivolts=float(3.3/4095)*float(uiSample);
//float fpressao=((fVmilivolts-_Gain.offsetPressao)/_Gain.AlfaPressao)+_Gain.PressaoLow;
float fpressao=((fVmilivolts-_Gain.foffset)/_Gain.fAlfa)+_Gain.fValueLow;

   return fpressao;

}


/*********************************************************************************************//**
 * \function     SaveTest
 * \details      Salva o teste no pen drive 
 *               verifica se o pendrive esta inserido
 *               Cria um arquivo com o nome dos dados 
 *               Verifica o tipo de sensor para fazer a conversão dos dados 
 *               grava um bloco de dados e verifica se chegou ao final 
 * \author     
 * \date        09/03/2022
 ************************************************************************************************/
#define BUF_USB_SIZE  5000

bool C_SensorAnalog::SaveTest() {
    uint8_t filename[20];
    uint8_t Line[100];
    uint16_t uiLineSize=0;
    float fvalue=0;
    uint16_t uibufIndex=0;

    FRESULT  Result;

    uint8_t ucBufUsb[BUF_USB_SIZE];


    //! Na primeira vez incrementa o salvamento
    if (_uiNEnsaio == 0)
        _uiNEnsaio++;


    //Limpar o buffer
    memset((char *)&ucBufUsb, 0, BUF_USB_SIZE);

    sprintf( (char *)&filename,"DadosAD%u_%05u.CSV",IndexMuxTimer- ucMUX_SENSOR_ANALOG_0,_uiNEnsaio);

    Remove_File((char *)&filename);   //apaga o arquivo caso ele exista


    //!Se o sensor não estava habilitado nesse teste não salva os dados
    if(!bSensorEnabled)
        return false;


    //Remove_File((char *)&filename);   //apaga o arquivo caso ele exista
    Create_File((char *)&filename);

    for(uint16_t index=0; index<uiBufIndex; index++){

        fvalue=ConvertPressureKpa(_uiSamples[index]);

        switch (_scSensorType){
        
        case ePressure:
            sprintf( (char *)&Line,"%u;%.2f;kPa\n",index,fvalue);
            break;

        case eTemperature:
            sprintf( (char *)&Line,"%u;%.2f;°c\n",index,fvalue);
            break;

        case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;N\n",index,fvalue);
            break;

        case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;mmH2O\n",index,fvalue);
            break;

        case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;Lux\n",index,fvalue);
            break;

        case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;V\n",index,fvalue);
            break;

        case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;mA\n",index,fvalue);
            break;

        case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;mA\n",index,fvalue);
            break;

        case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
            sprintf( (char *)&Line,"%u;%.2f;G\n",index,fvalue);
            break;

        case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
            sprintf( (char *)&Line,"%u;%.2f;L/min\n",index,fvalue);
            break;

        case  eNumSensor:
            break;

            //limitador de sensor na lista
        }
        
        //Analisa o tamanho da string
        uiLineSize=strlen((char *)&Line);
        
        if((uibufIndex + uiLineSize) < BUF_USB_SIZE){
            uibufIndex+=uiLineSize;

            //concatena a string
            strcat((char *)&ucBufUsb,(char *)&Line);
        }
        else{
            //não tem espaço, grava o que tinha antes
            Result= Update_File ((char *)&filename, (char *)&ucBufUsb);

            if(Result!= FR_OK)
                return false;

            //Zera o contador
            uibufIndex=0;

            //Limpar o buffer
            memset((char *)&ucBufUsb, 0, BUF_USB_SIZE);

            //! adiciona a linha que não coube
            uibufIndex+=uiLineSize;

            //concatena a string
            strcat((char *)&ucBufUsb,(char *)&Line);

        }
    }

    //Se saiu com dados no buffer faz a gravação
    if(uibufIndex){
        Result= Update_File ((char *)&filename, (char *)&ucBufUsb);
    }

    if(Result!= FR_OK)
        return false;
    else {
        _uiNEnsaio++;
        return true;
    }
}




/*********************************************************************************************//**
 * \function     GetLastValue
 * \details      Retorna o ultimo valor de leitura desse sensor 
 
 * \author     
 * \date        06/05/2022
 ************************************************************************************************/
void C_SensorAnalog::GetLastValue( uint8_t *ucPtrBuf) {

    float fvalue=0;

    fvalue=ConvertPressureKpa( _uiLastSample);


    switch (_scSensorType){

    case ePressure:
        snprintf( (char *)&ucPtrBuf[3],12,"%2.2fkPa",fvalue);
        break;

    case eTemperature:
        fvalue=ConvertTemp(_uiLastSample);
        snprintf( (char *)&ucPtrBuf[3],12,"%2.1f°c",fvalue);
        break;

    case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fN",fvalue);
        break;

    case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fmmH2O  ",fvalue);
        break;

    case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fLux",fvalue);
        break;

    case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fV",fvalue);
        break;

    case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fmA",fvalue);
        break;

    case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fmA",fvalue);
        break;

    case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fG",fvalue);
        break;

    case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
        snprintf( (char *)&ucPtrBuf[3],12,"%.2fL/min",fvalue);
        break;

    case  eNumSensor:
        break;
  }
    return;
}  


/*********************************************************************************************//**
 * \function     GetLastReading
 * \details      Retorna o ultimo valor de leitura em ponto flutuante 
 
 * \author     
 * \date        13/09/2022
 ************************************************************************************************/
float C_SensorAnalog::GetLastReading() {

    float fvalue= ConvertPressureKpa( _uiLastSample);
//    switch (_scSensorType){
//
//    case ePressure:
//        fvalue=ConvertPressureKpa( _uiLastSample);
//        break;
//
//    case eTemperature:
//        fvalue=ConvertTemp(_uiLastSample);
//        break;
//    case  eNumSensor:
//
//        break;        
//
//    }

    
    return fvalue;
} 


/*********************************************************************************************//**
 * \function     GetLastReadingVolts
 * \details      Retorna o ultimo valor de leitura em tensão
 
 * \author     
 * \date        20/09/2022
 ************************************************************************************************/
float C_SensorAnalog::GetLastReadingVolts() {
    return float( 3.3/4095)*float(_uiLastSample);
} 


/*********************************************************************************************//**
 * \function        UpdateReading
 * \details      incrementa/Decrementa a Leitura 

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
#define POS_CURSOR_CALIB_MAGNETICO 14
#define POS_CURSOR_CALIB_20mA   13
#define POS_CURSOR_CALIB_TEMP   14

void C_SensorAnalog::UpdateCalibValue(uint8_t tecla, eCalibIndex eIndex ) {
    
    int16_t iValue= iCalib[eIndex];
    uint8_t ucMaxPosition;
    uint16_t uiPosicao;

  switch(_scSensorType){

    case eTemperature:
    case ePressure:
    case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
    case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)   
    case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
       ucMaxPosition=3;
       uiPosicao=POS_CURSOR_CALIB_TEMP;

        break;
   
    case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
    case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
    case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
    case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
    case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)  
        ucMaxPosition=2;
        uiPosicao=POS_CURSOR_CALIB_MAGNETICO; 
        break;

     default:
         ucMaxPosition=3;
        break;
    }
 


    if(_scPosicaoDigito>ucMaxPosition){
        _scPosicaoDigito=ucMaxPosition-1;
        Lcd.SetCursorPosition(uiPosicao - _scPosicaoDigito-1, LCD_LINHA_2);
    }
    

    switch (tecla) {
    
    case TECLA_DIR:
        _scPosicaoDigito--;

        if (_scPosicaoDigito < 0)
            _scPosicaoDigito = ucMaxPosition;
        
        //posiciona o cursor
        if(_scPosicaoDigito==0 )
            Lcd.SetCursorPosition(uiPosicao - _scPosicaoDigito, LCD_LINHA_2); 
        else
            Lcd.SetCursorPosition(uiPosicao - _scPosicaoDigito-1, LCD_LINHA_2);

        break;

    case TECLA_ESQ:
        _scPosicaoDigito++;
        if (_scPosicaoDigito > ucMaxPosition)
            _scPosicaoDigito = 0;

        //posiciona o cursor
        if(_scPosicaoDigito==0 )
            Lcd.SetCursorPosition(uiPosicao - _scPosicaoDigito, LCD_LINHA_2); 
        else
            Lcd.SetCursorPosition(uiPosicao - _scPosicaoDigito-1, LCD_LINHA_2);

        break;

    case DESCE:
        switch(_scPosicaoDigito){
        case 0:
            iValue--;
            break;

        case 1:
            iValue-=10;

            break;
        case 2:
            iValue-=100;

            break;
        case 3:
            iValue-=1000;
            break;


        }

        break;

        case SOBE:
            switch(_scPosicaoDigito){
            case 0:
                iValue++;
                break;

            case 1:
                iValue+=10;
                break;

            case 2:
                iValue+=100;
                break;

            case 3:
                iValue+=1000;
                break;
            }

            break;

            default:
                break;
    }

    iCalib[eIndex] =iValue;


    //! Limita o valor máximo do ajuste

    switch(_scSensorType){

    case eTemperature:
        if(iCalib[eIndex] > 1500)
            iCalib[eIndex]=1500;
        else if(iCalib[eIndex] < -500)
            iCalib[eIndex]=-500;
        break;

    case ePressure:
        if(iCalib[eIndex] > 2500)
            iCalib[eIndex]=2500;  
        
        else if(iCalib[eIndex] < 0)
            iCalib[eIndex]=0;  
        break;

    case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
        if(iCalib[eIndex] > 100)
            iCalib[eIndex]=100;
        else if(iCalib[eIndex] < 0)
            iCalib[eIndex]=0;
        break;
    
    case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
        if(iCalib[eIndex] > 2500)
            iCalib[eIndex]=2500;
        else if(iCalib[eIndex] < 0)
            iCalib[eIndex]=0;
        break;
        break;

    case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)

        break;

    case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
        if(iCalib[eIndex] > 200)
            iCalib[eIndex]=200;
        else if(iCalib[eIndex] < -200)
            iCalib[eIndex]=-200;
        break;

    case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
        if(iCalib[eIndex] > 2000)
            iCalib[eIndex]=2000;
        else if(iCalib[eIndex] < -2000)
            iCalib[eIndex]=-2000;
        break;

    case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
        if(iCalib[eIndex] > 200)
            iCalib[eIndex]=200;
        else if(iCalib[eIndex] < -200)
            iCalib[eIndex]=-200;
        break;

    case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
        if(iCalib[eIndex] > 100)
            iCalib[eIndex]=100;
        else if(iCalib[eIndex] < -100)
            iCalib[eIndex]=-100;
        break;

    case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
        if(iCalib[eIndex] > 60)
            iCalib[eIndex]=60;
        else if(iCalib[eIndex] <3)
            iCalib[eIndex]=3;
        break;

    case  eNumSensor:
        break;

        
    }



}

/*********************************************************************************************//**
 * \function        GetValue
 * \details       

 * \author     
 * \date        09/02/2022
 ************************************************************************************************/
int16_t C_SensorAnalog::GetCalibValue(eCalibIndex eValue) {
    return iCalib[eValue];
}



/*********************************************************************************************//**
 * \function        SetCalibValue
 * \details       
 * \author     
 * \date        09/02/2022
 ************************************************************************************************/
void C_SensorAnalog::SetCalibValue(eCalibIndex eValue, uint16_t uiValue) {
    iCalib[eValue]=uiValue;
}






