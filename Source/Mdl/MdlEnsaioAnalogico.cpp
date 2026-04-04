/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlLcd.cpp
 
 *\details   Módulo para controle das telas do LCD
 *		
 *

 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "MdlEnsaioanalogico.h"
#include "File_Handling.h"
#include "lcd.h"
#include "MdlLcd.h"
#include "Modo0.h"
#include "HdsTeclado.h"
#include "Mdlmsg.h"
#include "MdlSensorAnalog.h"
#include <stdio.h>
#include <string.h>
#include "HdsMux.h"
#include "KBD2.h"
#include "HdsDma.h"
#include "MdlCalib.h"


/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Analogico EnsaioAnalogico;

/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o módulo 

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
void C_Analogico::Init(void) {

    _eState = eAnalogSelOperationMode;
    //inicializa sensores
    AnalogS0.Init(ucMUX_SENSOR_ANALOG_0);
    AnalogS1.Init(ucMUX_SENSOR_ANALOG_1);
    AnalogS2.Init(ucMUX_SENSOR_ANALOG_2);
    AnalogS3.Init(ucMUX_SENSOR_ANALOG_3);
    AnalogS4.Init(ucMUX_SENSOR_ANALOG_4);

    bModoIndicador=false;
   
    //! Inicia a conversão do AD
   // DmaStartAdReading(CTE_ALPHA_ANALOGICO);
}

/*********************************************************************************************//**
 * \function        Start
 * \details   Para iniciar novamente 

 * \author     
 * \date         18/02/2022
 ************************************************************************************************/
//void C_Analogico::Start(void) {

//    _eState = eAnalogSelSensorS0;

//}

/*********************************************************************************************//**
 * \function        Run
 * \details   Avança os estados da maquina de estados do ensaio do sensor  
 chamada a cada 100ms
 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
#define POS_CURSOR_MS  6

                                        //pressao   temperatura 
const uint8 CursorPosition[eNumSensor]={14      ,       14};

uint16_t C_Analogico::Run(void) {
    uint8_t ucTecla;
    uint16_t eType;
   

    //  IDIOMA = 1;

    //!Le a tecla para o proximo estado
    ucTecla = Teclado.GetTecla();

    //Se pressionou o reset aborta a execução
    if (ucTecla == RESET) {
        _eState =  eAnalogStopTest;
        
    }

    switch (_eState) {

    case eAnalogSelOperationMode:

        Lcd.Write(LCD_LINHA_1, (char*) &MSG_INDICADOR_L1[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_INDICADOR_L2[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);

        break;

    case eAnalogIndicatorMode:
        //Seta a flag de modo indicador       
        bModoIndicador = true;
        _eState = eAnalogSelSensorS0;
        break;
        
    case eAnalogSelSensorS0:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_SEL_SENSOR[IDIOMA - 1][0]);
        //Exibe uma lista com o tipo de sensor tecla UP/Down altera
        //Busca da classe o sensor configurado
        //Verifica se alterou
        //Atualiza a tela
        //Troca de estado se foi tela ok
        AnalogS0.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS0.GetSensor());
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeSampleSensorS0:        //!Tempo de Amosragem
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS0.SetSampleTime(1000);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }
            Lcd.Write(LCD_LINHA_1,(char*) &MSG_S0_TEMPO_AMOSTRA[IDIOMA - 1][0]);
            AnalogS0.UpdateValue(ucTecla, eSampleTime);
            _ShowTime(AnalogS0.GetValue(eSampleTime), eSampleTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeTestS0:        //!Tempo de teste
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS0.SetTestTime(9999);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }

            Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_TEMPO_TESTE[IDIOMA - 1][0]);
            AnalogS0.UpdateValue(ucTecla, eExcutionTime);
            _ShowTime(AnalogS0.GetValue(eExcutionTime), eExcutionTime);
        }

        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogNextSensorS0:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_PROXIMO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

        /******************** SENSOR S1   ***********************/
    case eAnalogSelSensorS1:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S1_SEL_SENSOR[IDIOMA - 1][0]);
        //Exibe uma lista com o tipo de sensor tecla UP/Down altera
        //Busca da classe o sensor configurado
        //Verifica se alterou
        //Atualiza a tela
        //Troca de estado se foi tela ok
        AnalogS1.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS1.GetSensor());
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeSampleSensorS1:        //!Tempo de Amosragem
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS1.SetSampleTime(1000);
            ucTecla = R_FUNC;
        }
        else {

            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }
            Lcd.Write(LCD_LINHA_1,
                    (char*) &MSG_S0_TEMPO_AMOSTRA[IDIOMA - 1][0]);
            AnalogS1.UpdateValue(ucTecla, eSampleTime);
            _ShowTime(AnalogS1.GetValue(eSampleTime), eSampleTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeTestS1:        //!Tempo de teste
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS1.SetTestTime(9999);
            ucTecla = R_FUNC;
        }
        else {

            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }

            Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_TEMPO_TESTE[IDIOMA - 1][0]);
            AnalogS1.UpdateValue(ucTecla, eExcutionTime);
            _ShowTime(AnalogS1.GetValue(eExcutionTime), eExcutionTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogNextSensorS1:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_PROXIMO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

        /******************** SENSOR S2   ***********************/
    case eAnalogSelSensorS2:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S2_SEL_SENSOR[IDIOMA - 1][0]);
        //Exibe uma lista com o tipo de sensor tecla UP/Down altera
        //Busca da classe o sensor configurado
        //Verifica se alterou
        //Atualiza a tela
        //Troca de estado se foi tela ok
        AnalogS2.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS2.GetSensor());
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeSampleSensorS2:        //!Tempo de Amostragem
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS2.SetSampleTime(1000);
            ucTecla = R_FUNC;
        }
        else {

            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }
            Lcd.Write(LCD_LINHA_1,
                    (char*) &MSG_S0_TEMPO_AMOSTRA[IDIOMA - 1][0]);
            AnalogS2.UpdateValue(ucTecla, eSampleTime);
            _ShowTime(AnalogS2.GetValue(eSampleTime), eSampleTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeTestS2:        //!Tempo de teste
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS2.SetTestTime(9999);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }

            Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_TEMPO_TESTE[IDIOMA - 1][0]);
            AnalogS2.UpdateValue(ucTecla, eExcutionTime);
            _ShowTime(AnalogS2.GetValue(eExcutionTime), eExcutionTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogNextSensorS2:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_PROXIMO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

        /******************** SENSOR S3   ***********************/
    case eAnalogSelSensorS3:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S3_SEL_SENSOR[IDIOMA - 1][0]);
        //Exibe uma lista com o tipo de sensor tecla UP/Down altera
        //Busca da classe o sensor configurado
        //Verifica se alterou
        //Atualiza a tela
        //Troca de estado se foi tela ok
        AnalogS3.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS3.GetSensor());
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeSampleSensorS3:        //!Tempo de Amosragem
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS3.SetSampleTime(1000);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }
            Lcd.Write(LCD_LINHA_1,
                    (char*) &MSG_S0_TEMPO_AMOSTRA[IDIOMA - 1][0]);
             AnalogS3.UpdateValue(ucTecla, eSampleTime);
            _ShowTime(AnalogS3.GetValue(eSampleTime), eSampleTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeTestS3:        //!Tempo de teste
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS3.SetTestTime(9999);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }

            Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_TEMPO_TESTE[IDIOMA - 1][0]);
            AnalogS3.UpdateValue(ucTecla, eExcutionTime);
            _ShowTime(AnalogS3.GetValue(eExcutionTime), eExcutionTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogNextSensorS3:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_PROXIMO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

        /******************** SENSOR S4   ***********************/
    case eAnalogSelSensorS4:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S4_SEL_SENSOR[IDIOMA - 1][0]);
        //Exibe uma lista com o tipo de sensor tecla UP/Down altera
        //Busca da classe o sensor configurado
        //Verifica se alterou
        //Atualiza a tela
        //Troca de estado se foi tela ok
        AnalogS4.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS4.GetSensor());
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeSampleSensorS4:        //!Tempo de Amostragem
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS4.SetSampleTime(1000);
            ucTecla = R_FUNC;
        }
        else {

            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }
            Lcd.Write(LCD_LINHA_1,
                    (char*) &MSG_S0_TEMPO_AMOSTRA[IDIOMA - 1][0]);
            AnalogS4.UpdateValue(ucTecla, eSampleTime);
            _ShowTime(AnalogS4.GetValue(eSampleTime), eSampleTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogTimeTestS4:        //!Tempo de teste
        //se modo indicador ativo, atribui tempo máximo e vai para o próximo passo
        if (bModoIndicador) {
            AnalogS4.SetTestTime(9999);
            ucTecla = R_FUNC;
        }
        else {
            if (!Lcd.GetCursorState()) {
                Lcd.SetCursorOn();
                Lcd.SetCursorPosition(POS_CURSOR_MS, LCD_LINHA_2);
            }

            Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_TEMPO_TESTE[IDIOMA - 1][0]);
            AnalogS4.UpdateValue(ucTecla, eExcutionTime);
            _ShowTime(AnalogS4.GetValue(eExcutionTime), eExcutionTime);
        }
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogNextSensorS4:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_PROXIMO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

        /******************** EXECUÇÃO E OUTROS TRATAMENTOS    ***********************/

    case eAnalogStartTest:
        //!desliga o cursor
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }

        //Inicio do tese
        Lcd.Write(LCD_LINHA_1, (char*) &MSG100_1[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_OK[0]);
        _eState = _CheckNextState(_eState, ucTecla);
        DmaStartAdReading(CTE_ALPHA_ANALOGICO);
        if (_eState == eAnalogShowTestWaitPause) {
            //Escolheu iniciar o teste
           
            AnalogS0.Start();
            AnalogS1.Start();
            AnalogS2.Start();
            AnalogS3.Start();
            AnalogS4.Start();

            //!Para mostrar o andamento do teste
            eTestState = eShowS0;

        }
        break;

        //! Fica nesse estado até pressionar o pause ou finalizar o teste
    case eAnalogShowTestWaitPause:
        //Se não for apenas para indicar os valores 
        if(!bModoIndicador){
            _eState=eAnalogShowTestCancela;
            break;
        }


        //Mostra os valores do teste na linha 1
        _ShowTestLine1();

        //!mensagem linha 2
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_PAUSE[IDIOMA - 1][0]);

        _UpdateShowLine1(ucTecla);

        //!se a tecla foi o pause deve ir para o proximo estado
        if (ucTecla == M_FUNC) {
            //parar a aquisição de dados
            DmaStopAdReading();
            //! Analisa proximo estado
            _eState = _CheckNextState(_eState, ucTecla);
        }

        //Se concluiu  o teste
        if ((AnalogS0.IsRunnig() || AnalogS1.IsRunnig() || AnalogS2.IsRunnig()
                || AnalogS3.IsRunnig() || AnalogS4.IsRunnig()) == 0) {
            _eState = eAnalogShowTestconcluded;
            DmaStopAdReading();
        }

        break;

    case eAnalogShowTestVerVoltarParar:
        //Mostra os valores do teste na linha 1
        _ShowTestLine1();

        //!mensagem linha 2
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_VER_VOLTAR_PARAR[IDIOMA - 1][0]);

        //! Analisa proximo estado
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogShowTestCancela:
        //Mostra os valores do teste na linha 1
        _ShowTestLine1();

        //!mensagem linha 2
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_CANCELA[IDIOMA - 1][0]);

        _UpdateShowLine1(ucTecla);

        //!se a tecla foi o pause deve ir para o proximo estado
        if (ucTecla == M_FUNC) {
            //parar a aquisição de dados
            DmaStopAdReading();
            //! Analisa proximo estado
            _eState = _CheckNextState(_eState, ucTecla);
        }

        //Se concluiu  o teste
        if ((AnalogS0.IsRunnig() || AnalogS1.IsRunnig() || AnalogS2.IsRunnig()
                || AnalogS3.IsRunnig() || AnalogS4.IsRunnig()) == 0) {
            _eState = eAnalogShowTestconcluded;
            DmaStopAdReading();
        }
        break;

    case eAnalogShowTestVoltar:
        //Mostra os valores do teste na linha 1
        _ShowTestLine1();

        //!mensagem linha 2 
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_VOLTAR[IDIOMA - 1][0]);

        _UpdateShowLine1(ucTecla);

        //! Analisa proximo estado
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogShowTestconcluded:
        //Mostra os valores do teste na linha 1
        _ShowTestLine1();

        //!mensagem linha 2
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_CONCLUIDO[IDIOMA - 1][0]);

        _UpdateShowLine1(ucTecla);

        _eState = _CheckNextState(_eState, ucTecla);
        break;
        
    case eAnalogStopTest:
        //!Deve parar a leitura dos sensores 
        AnalogS0.Disabled();
        AnalogS1.Disabled();
        AnalogS2.Disabled();
        AnalogS3.Disabled();
        AnalogS4.Disabled();
        Lcd.SetCursorOFF();
        _eState = eAnalogExit;    
        break;

    case eAnalogStartTestAgain:
        //Inicia as conversõs novamente   
        DmaStartAdReading(CTE_ALPHA_ANALOGICO);
        
        //Salta direto para o estado de monitorar novametne 
        _eState = eAnalogShowTestWaitPause;
        break;


        /******************** SALVA INFORMAÇÕES NO PEN DRIVE   ***********************/
    case eAnalogSaveTestQuestion:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_SALVA_RESULTADO[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__NAO__SIM[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

       case eAnalogCheckPenDrive:
        if(!GetPendriveState()){
          _eState = eAnalogInsertPenDrive; 
          }
         else{
           _eState = eAnalogSaveTest;
            }

          break;  

    case eAnalogInsertPenDrive:
        if(!GetPendriveState()){
          //Escreve mensagem   
           Lcd.Write(LCD_LINHA_1, (char*) &MSG_NO_PENDRIVEUSB[IDIOMA - 1][0]);
           Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR[IDIOMA - 1]);

           //!Não permite salvar com a tecla da direita.
           if(ucTecla==R_FUNC)
                ucTecla=0;

          _eState = _CheckNextState(_eState, ucTecla); 
          }
         else{
           _eState = _CheckNextState(_eState, R_FUNC);
            }

        break;
  
//    case eAnalogAskSavePenDrive:
 //        Lcd.Write(LCD_LINHA_1, (char*) &MSG_SAVE_AT_PENDRIVEUSB[IDIOMA - 1][0]);
 //        Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR_________OK[IDIOMA - 1]);
 //        _eState = _CheckNextState(_eState, ucTecla); 

//       break;

    case eAnalogSaveTest:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_SALVANDO_DADOS_USB[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__LIMPA_LINHA_2);
        _ShowUsb(true);
        _eState = eAnalogSavingTest;
        MuxTimers.SetMsDelay(500);  
        break;

    case eAnalogSavingTest:
        if(MuxTimers.CheckMsDelay()){

            if(_ShowUsb(false)>=6){ //6 para rodar um passo a mais para mostrar a mensagem do ultimo sensor
                _eState = eAnalogRepeatExit;
            }
        }
        break;
        
    case eAnalogRepeatExit:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_REPETIR_SAIR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR__MAIOR[0]);
        _eState = _CheckNextState(_eState, ucTecla);
        break;

    case eAnalogExit:
        //Sinaliza para o estado acima que saiu da sequencia 
        break;

        /******************** AJUSTE DOS SENSORES ***********************/
    case eAnalogCalibSelSensor:
       //!desliga o cursor se estiver ligado 
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }

        Lcd.Write(LCD_LINHA_1, (char*) &MSG_S0_SEL_SENSOR[IDIOMA - 1][0]);
        AnalogS0.UpdateSensor(ucTecla);
        _ShowSensor(AnalogS0.GetSensor());

        //Faz uma mudança na tecla para poder retornar ao ajuse de fabrica 
         if(ucTecla==TECLA_DIR  || ucTecla==TECLA_ESQ) {
             //! simula a tecla do meio
           _eState = _CheckNextState(_eState, M_FUNC);  
            }
            else
          _eState = _CheckNextState(_eState, ucTecla);  
        
        break;

   case eAnalogCalibSelectReturnDefault:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_CALIB_RETURN_DEFALULT[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_CALIB_RETURN_DEFALULT_2[IDIOMA - 1][0]);
        
        _eState = _CheckNextState(_eState, ucTecla);  
           
         if( _eState == eAnalogCalibSelSensor){
            //Confirmou a calib default
              Calib.Validate(true);
            }

        break;

   

    case eAnalogCalibInsiraSensorLow:
       //!desliga o cursor se estiver ligado 
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        } 

        //_ShowSensorCalib(AnalogS0.GetSensor());
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_CALIB_SENSOR[AnalogS0.GetSensor()][IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG_CALIB_INSIRA_S0[IDIOMA - 1][0]);
        _eState = _CheckNextState(_eState, ucTecla);  
        AnalogS0.SetSensor((eSensorType)AnalogS0.GetSensor());
        AnalogS0.SetTestTime(9999);
        AnalogS0.SetCalibValue(eCalibValueLow , (uint16_t) AnalogS0.GetLastReading()*10);
        DmaStartAdReading(CTE_ALPHA_ANALOGICO);
        AnalogS0.Start();
        break;
        
    case eAnalogCalibSensorLow:
       eType=AnalogS0.GetSensor(); 
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(CursorPosition[eType], LCD_LINHA_2);
        }
       //!Escreve menor valor no display 
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_CALIB_MENOR_VALUE[AnalogS0.GetSensor()][IDIOMA - 1][0]);
        
                
        AnalogS0.UpdateCalibValue(ucTecla, eCalibValueLow);

       //!mostra os valores da calibração no display
        _ShowCalib(eType, eCalibValueLow);        

        Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
        //!Salva o offset da medida 
        Calib.Gain.Value[eType].fReadingLow=AnalogS0.GetLastReadingVolts();

   //     Calib.Gain.ReadingTemperaturaLow=AnalogS0.GetLastReadingVolts();
         Calib.Gain.Value[eType].fValueLow= (float)AnalogS0.GetCalibValue(eCalibValueLow)/10;   

       //  Calib.Gain.TemperaturaLow=(float)AnalogS0.GetCalibValue(eCalibTempLow)/10;   
      
        _eState = _CheckNextState(_eState, ucTecla);
        break;

     case eAnalogCalibSensorHigh:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_CALIB_MAIOR_VALUE[AnalogS0.GetSensor()][IDIOMA - 1][0]);

        AnalogS0.UpdateCalibValue(ucTecla, eCalibValueHigh);
         
        eType=AnalogS0.GetSensor();

         //!mostra os valores da calibração no display
        _ShowCalib(eType, eCalibValueHigh);        

        Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
        
        //  inclinação (YH-YL)/(XH-XL) => (Leitura do AD - offset) /100
        // Calib.Gain.ReadingTemperaturaHigh= AnalogS0.GetLastReadingVolts();
        Calib.Gain.Value[eType].fReadingHigh=AnalogS0.GetLastReadingVolts();

        // Calib.Gain.TemperaturaHigh=(float)AnalogS0.GetCalibValue(eCalibTempHigh)/10;   
        Calib.Gain.Value[eType].fValueHigh=(float)AnalogS0.GetCalibValue(eCalibValueHigh)/10;   

        _eState = _CheckNextState(_eState, ucTecla);
        
        if(_eState==eAnalogCalibSelSensor){
        //Finalizou o ajuste
          Calib.CalculaCte((eSensorType) eType);
          Calib.Save();
        }

        break; 

     }
    return _eState;
}


/*********************************************************************************************//**
 * \function        _ShowSensorCalib
 * \details   Mostra no display o tipo de sensor que sera ajustado 

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
//void C_Analogico::_ShowSensorCalib(uint16_t uiIndex) {
//    Lcd.Write(LCD_LINHA_1, (char*) &MSG_CALIB_SENSOR[uiIndex][IDIOMA - 1][0]);
//    Lcd.Write(LCD_LINHA_2, (char*) &MSG_CALIB_INSIRA_S0[IDIOMA - 1][0]);
//    
//}

/*********************************************************************************************//**
 * \function        _ShowSensor
 * \details   Mostra no display o tipo de sensor 

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
void C_Analogico::_ShowSensor(uint16_t uiIndex) {
    //mostra na linha 2
    Lcd.Write(LCD_LINHA_2, (char*) &MSG_MODELO_SENSOR[uiIndex][IDIOMA - 1][0]);
}


/*********************************************************************************************//**
 * \function        _ShowUsb
 * \details   Mostra no display informaçoes da usb

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
uint32_t C_Analogico::_ShowUsb( bool init) {

    static uint32_t index;

    if(init){
        index=0;
        return index;
    }


    switch (index){
    case 0:
        if (!AnalogS0.IsEnabled()){
            break;
        }
        MuxTimers.SetMsDelay(500);
        if(AnalogS0.SaveTest())
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S0_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S0_NOK[IDIOMA - 1][0]);

        break;
    case 1:
        if (!AnalogS1.IsEnabled()){
            break;
        }
        MuxTimers.SetMsDelay(500);
        if(AnalogS1.SaveTest())
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S1_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S1_NOK[IDIOMA - 1][0]);
        break;
    case 2:
        if (!AnalogS2.IsEnabled()){
            break;
        }
        MuxTimers.SetMsDelay(500);
        if(AnalogS2.SaveTest())
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S2_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S2_NOK[IDIOMA - 1][0]);
        break;
    case 3:
        if (!AnalogS3.IsEnabled()){
            break;
        }
        MuxTimers.SetMsDelay(500);
        if(AnalogS3.SaveTest())
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S3_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S3_NOK[IDIOMA - 1][0]);
        break;
    case 4:
        if (!AnalogS4.IsEnabled()){
            break;
        }
        MuxTimers.SetMsDelay(500);
        if(AnalogS4.SaveTest())
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S4_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_S4_NOK[IDIOMA - 1][0]);
        break;
    default:

        break;

    }
    index++;
    return index;
}


/*********************************************************************************************//**
 * \function        _ShowTime
 * \details   Mostra no display o tempo do teste 

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
void C_Analogico::_ShowTime(uint16_t uiValue, uint16_t uiType) {

    

    if (uiType == eSampleTime)
        sprintf((char*) &_buflcd, "     %04u ms  OK", uiValue);
    else
        sprintf((char*) &_buflcd, "     %04u s   OK", uiValue);

    Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);

}

/*********************************************************************************************//**
 * \function        _ShowTest
 * \details   Mostra no display o resultado do teste em andamento, 
 *            verifica se existe um teste em andamento e segue executando
 * \author     
 * \date         11/02/2022
 ************************************************************************************************/
uint16_t C_Analogico::_ShowTest() {
    static uint8_t ucCont = 0;
    bBits bSensor;
    bool bFound = false;

    //!Atualiza o estado dos testes
    bSensor.ucValue = 0;
    bSensor.S0 = AnalogS0.IsRunnig();
    bSensor.S1 = AnalogS1.IsRunnig();
    bSensor.S2 = AnalogS2.IsRunnig();
    bSensor.S3 = AnalogS3.IsRunnig();
    bSensor.S4 = AnalogS4.IsRunnig();

    //monta a primeira linha
    sprintf((char*) &_buflcd, "Exec  S0S1S2S3S4");

    //Apaga o sensor que nao esta em teste
    if (!bSensor.S0) {
        _buflcd[6] = _buflcd[7] = ' ';
    }
    if (!bSensor.S1) {
        _buflcd[8] = _buflcd[9] = ' ';
    }
    if (!bSensor.S2) {
        _buflcd[10] = _buflcd[11] = ' ';
    }
    if (!bSensor.S3) {
        _buflcd[12] = _buflcd[13] = ' ';
    }
    if (!bSensor.S4) {
        _buflcd[14] = _buflcd[15] = ' ';
    }

    //!Escreve no display
    Lcd.Write(LCD_LINHA_1, (char*) &_buflcd);

    //!Vai ciclando a tecla	a cadas x segundos
    if (++ucCont > 10) {
        ucCont = 0;

        eTestState++;
        if (eTestState >= eShowDone)
            eTestState = eShowS0;

    }
    
    do {
        //!Se já finalizou todos os testes:
        if (bSensor.ucValue == 0)
            eTestState = eShowDone;

        switch (eTestState) {

        case eShowTestIdle:
            break;

        case eShowS0:
            if (!bSensor.S0) {
                eTestState = eShowS1;
                continue;
            }
            sprintf((char*) &_buflcd, "S0=     %04u s  ",AnalogS0.GetValue(eRunningTime));
            Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
            bFound = true;
            break;

        case eShowS1:
            if (!bSensor.S1) {
                eTestState = eShowS2;
                continue;
            }
            sprintf((char*) &_buflcd, "S1=     %04u s  ",AnalogS1.GetValue(eRunningTime));
            Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
            bFound = true;
            break;

        case eShowS2:
            if (!bSensor.S2) {
                eTestState = eShowS3;
                continue;
            }
            sprintf((char*) &_buflcd, "S2=     %04u s  ",AnalogS2.GetValue(eRunningTime));
            Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
            bFound = true;
            break;

        case eShowS3:
            if (!bSensor.S3) {
                eTestState = eShowS4;
                continue;
            }

            sprintf((char*) &_buflcd, "S3=     %04u s  ",AnalogS3.GetValue(eRunningTime));
            Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
            bFound = true;
            break;

        case eShowS4:
            if (!bSensor.S4) {
                eTestState = eShowS0;
                continue;
            }

            sprintf((char*) &_buflcd, "S4=     %04u s  ",AnalogS4.GetValue(eRunningTime));
            Lcd.Write(LCD_LINHA_2, (char*) &_buflcd);
            bFound = true;
            break;

        case eShowDone:
            bFound = true;
            break;

        }
    } while (!bFound);

    return (eTestState);
}


/*********************************************************************************************//**
 * \function        _UpdateShowLine1
 * \details   atualiza o sensor que quer mostrar na linha 1 
 * \author     
 * \date         06/05/2022
 ************************************************************************************************/
void  C_Analogico::_UpdateShowLine1(uint8_t ucTecla) {
    bBits bSensor;
    bool bcontinue = true;

    //!Verifica qual sensor esta configurado 
    bSensor.ucValue = 0;
    bSensor.S0 = AnalogS0.IsEnabled();
    bSensor.S1 = AnalogS1.IsEnabled();
    bSensor.S2 = AnalogS2.IsEnabled();
    bSensor.S3 = AnalogS3.IsEnabled();
    bSensor.S4 = AnalogS4.IsEnabled();

    switch (ucTecla) {
    case L_FUNC:
        do {
            if (--_scShowSensorNumber < 0) {
                _scShowSensorNumber = 4;
            }
            
            //verifica se o sensor esta habilitado
            if ((bSensor.ucValue &(1 << _scShowSensorNumber)) > 0 ) {
                //Sensor habilitado mostra a informação
                bcontinue = false;
            }

        } while (bcontinue);
        
        break;

    case M_FUNC:


        break;

    case R_FUNC:
        do {
            if (++_scShowSensorNumber > 4) {
                _scShowSensorNumber = 0;
            }

            //verifica se o sensor esta habilitado
            if ((bSensor.ucValue & (1 << _scShowSensorNumber)) > 0) {
                //Sensor habilitado mostra a informação
                bcontinue = false;
            }

        } while (bcontinue);
        
        break;
        
    default:
        break;
    }
}

/*********************************************************************************************//**
 * \function   _ShowTestLine1
 * \details   Mostra o valor do sensor na linha 1 
 *            S0=XXXXX.XXXX
 * \author     
 * \date         06/05/2022
 ************************************************************************************************/
void C_Analogico::_ShowTestLine1() {

     //inicia a monagem da tela 
    switch (_scShowSensorNumber) {
    case 0:
        sprintf((char*) &_buflcd, "S0= ");
        AnalogS0.GetLastValue((uint8_t *)&_buflcd);
        break;
    case 1:
        sprintf((char*) &_buflcd, "S1= ");
        AnalogS1.GetLastValue((uint8_t *)&_buflcd);
        break;
    case 2:
        sprintf((char*) &_buflcd, "S2= ");
        AnalogS2.GetLastValue((uint8_t *)&_buflcd); 
        break;
    case 3:
        sprintf((char*) &_buflcd, "S3= ");
        AnalogS3.GetLastValue((uint8_t *)&_buflcd);
        break;
    case 4:
        sprintf((char*) &_buflcd, "S4= ");
        AnalogS4.GetLastValue((uint8_t *)&_buflcd);
        break;
    default:

        break;

    }
    //Valor em string
    //  snprintf( (char *)&_buflcd[3],11,"%2.4f",fValue);

    _buflcd[16]=0;

    //!Escreve no display
    Lcd.Write(LCD_LINHA_1, (char*) &_buflcd);
}

/*********************************************************************************************//**
 * \function        _CheckNextState
 * \details   Analisa a tecla recebida e retorna no novo estado casao seja uma das 3 teclas de função 

 * \author     
 * \date         10/02/2022
 ************************************************************************************************/
uint16 C_Analogico::_CheckNextState(int16 estado, int _teclado) {
    uint16 uiRet = 0;
    uint16_t uiIndex;

    //!procura o estado na lista de estados
    for (uint8_t i = 0; i < eAnalogLastState; i++) {
        if (estado == _EstadosAnalogico[i][0]) {
            uiIndex = i;
            break;
        }
    }
    switch (_teclado) {
    case L_FUNC:
        //lcd_limpa();
        uiRet = (_EstadosAnalogico[uiIndex][1]);
        break;

    case M_FUNC:
        uiRet = (_EstadosAnalogico[uiIndex][2]);
        //lcd_limpa();
        break;

    case R_FUNC:
        uiRet = (_EstadosAnalogico[uiIndex][3]);
        //	lcd_limpa();
        break;

    default:
        uiRet = (_EstadosAnalogico[uiIndex][0]);  //continua no mesmo estado
    }
    return uiRet;

}


/*********************************************************************************************//**
 * \function        _ShowCalib
 * \details   Mostra valor da leitura da calibração

 * \author     
 * \date         07/02/2022
 ************************************************************************************************/
void C_Analogico::_ShowCalib(uint16_t eType, eCalibIndex CalibHighLow) {

    switch(eType){
         
        case eTemperature:
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),3, '°',(uint8_t*)&_buflcd);
           break;
        
        case ePressure: 
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),3, 'k',(uint8_t*)&_buflcd);
            break;


        case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
          fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),2, 'N',(uint8_t*)&_buflcd);
            break;

      
        case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
          fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),3, 'm',(uint8_t*)&_buflcd);
         break;

        case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
         fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),3, 'L',(uint8_t*)&_buflcd);  
           break;

        case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
          fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),2, 'V',(uint8_t*)&_buflcd); 
       break;

        case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
          fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),3, 'm',(uint8_t*)&_buflcd); 

       break;
       
        case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
         fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),2, 'm',(uint8_t*)&_buflcd); 

            break;

        case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
              fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),2, 'G',(uint8_t*)&_buflcd); 
            break;

        case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
         fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(CalibHighLow),2, 'L',(uint8_t*)&_buflcd); 

            break;

        case  eNumSensor:
            break;
         }

        _buflcd[16]=0;
     
       
}

/*******************************//**
 * \brief fomatLine
 * \param  nenhum
 * \details
 *  Formata os valores na linha 
 
 grandezas de 3 digitos
 "-xxx.x OK-xxx.yU"
 " xxx.x OK-xxx.yU" 
 "-xxx.x OK xxx.yU"
 " xxx.x OK xxx.yU"
 
 grandezas de 2 digitos
 "-xx.xU OK -xx.yU"
 " xx.xU OK -xx.yU" 
 "-xx.xU OK  xx.yU"
 " xx.xU OK  xx.yU"
 *********************************/
void C_Analogico::fomatLine(int16_t firstValue, int16_t SecondValue, uint8_t Numdigitos, uint8_t ucUnidade,  uint8_t *pbufLcd){
	int16_t uiInteiro;
	int16_t uiDecimal;
	uint8_t  ucBuf[7];  //maior numero inteiro -32767 a 32768
	uint8_t  ucBuf2[7];  //maior numero inteiro -32767 a 32768
		
   memset((char *)pbufLcd, 0x20, BUFFER_LCD_SIZE);

   pbufLcd[7]='O';
   pbufLcd[8]='K'; 

	if(firstValue<0){
		uiInteiro=-firstValue/10;
		uiDecimal= -(firstValue%10);
		pbufLcd[0]='-';
	 }
	 else{
 		uiInteiro=firstValue/10;
		uiDecimal= firstValue%10;
	 }
	
	 //passa os valores para string
	  sprintf((char *)&ucBuf, "%03d", uiInteiro);
	  sprintf((char *)&ucBuf2, "%1d", uiDecimal); 
	  
   //coloca no Lcd	 
	 if(Numdigitos==3){
	  pbufLcd[1]=ucBuf[0];
	  pbufLcd[2]=ucBuf[1];
	  pbufLcd[3]=ucBuf[2];
		pbufLcd[4]='.';
	  pbufLcd[5]=ucBuf2[0]; 
	 }
	  else{
		pbufLcd[1]=ucBuf[0];
	  pbufLcd[2]=ucBuf[1];
	  pbufLcd[3]='.';
	  pbufLcd[4]=ucBuf2[0]; 
    pbufLcd[5]=ucUnidade; 			
		}
	 
	  //repete para o segundo valor
	if(SecondValue<0){
		uiInteiro= -SecondValue/10;
		uiDecimal= -SecondValue%10;
		
		if(Numdigitos==3)
				pbufLcd[9]='-';
		   else
		    pbufLcd[10]='-';
	 }
	 else{
 		uiInteiro=SecondValue/10;
		uiDecimal= SecondValue%10;
	 }

	 //passa os valores para string
	  sprintf((char *)&ucBuf, "%03d", uiInteiro);
	  sprintf((char *)&ucBuf2, "%1d", uiDecimal); 
	  
   //coloca no Lcd	 
	 if(Numdigitos==3){
	  pbufLcd[10]=ucBuf[0];
	  pbufLcd[11]=ucBuf[1];
	  pbufLcd[12]=ucBuf[2];
		pbufLcd[13]='.';
	  pbufLcd[14]=ucBuf2[0]; 
		pbufLcd[15]=ucUnidade; 
	 }
	  else{
		pbufLcd[11]=ucBuf[1];
	  pbufLcd[12]=ucBuf[2];
	  pbufLcd[13]='.';
	  pbufLcd[14]=ucBuf2[0]; 
    pbufLcd[15]=ucUnidade; 			
		}
}



/*

    switch(eType){
         
        case eTemperature:
         
        //     if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
        //        sprintf((char*) &_buflcd, "-%02d.%01d° OK %02d.%01d°",-1*(int16_t)AnalogS0.GetLastReading(),-1*((int16_t)AnalogS0.GetLastReading()%10),AnalogS0.GetCalibValue(eCalibValueLow)/10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
        //     else
        //        sprintf((char*) &_buflcd, "%03d.%01d° OK %03d.%01d°",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
           
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),3, '°',(uint8_t*)&_buflcd);

            break;
        
        case ePressure: 
         // sprintf((char*) &_buflcd, "%03d.%01dK OK %03d.%01dK",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),3, 'k',(uint8_t*)&_buflcd);
            break;


        case eForca: //CL011	Sensor de força 0 a 10 (N), cabo (miniDIN)
         //  sprintf((char*) &_buflcd, "%02d.%01dN  OK  %02d.%01dN",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),2, 'N',(uint8_t*)&_buflcd);
            break;

      
        case ePressureDiferencial://CL012C	Sensor pressão diferencial 0 a 250 (mmH2O), cabo (miniDIN-miniDIN)
        //sprintf((char*) &_buflcd, "%03d.%01dm OK %03d.%01dm",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
         fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),3, 'm',(uint8_t*)&_buflcd);
         break;

        case eIntensidadeLuminosa://CL014A	Sensor intensidade luminosa 0 a 5000 lux e cabo (miniDIN-miniDIN)
           //sprintf((char*) &_buflcd, "%03d.%01dL OK %03d.%01dL",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
           fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),3, 'L',(uint8_t*)&_buflcd);  
           break;

        case eVoltage_menos_20_mais_20://CL019B	Sensor de tensão -20 a +20 (V) e cabo (miniDIN-miniDIN)
         //    if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
         //       sprintf((char*) &_buflcd, "%03d.%01dV OK %02d.%01dV",(uint16_t)AnalogS0.GetLastReading(),((uint16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
         //    else
         //       sprintf((char*) &_buflcd, "%03d.%01dV OK %03d.%01dV",(uint16_t)AnalogS0.GetLastReading(),((uint16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
 
       //    if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
       //         sprintf((char*) &_buflcd, "-%02d.%01dV OK -%02d.%01dV",-1*((int16_t)AnalogS0.GetLastReading()),-1*((int16_t)AnalogS0.GetLastReading()%10),-1*AnalogS0.GetCalibValue(eCalibValueLow)/10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
       //      else
       //         sprintf((char*) &_buflcd, "%02d.%01dV  OK  %02d.%01dV",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
 
             fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),2, 'V',(uint8_t*)&_buflcd); 
       break;

        case eCurrent_menos_200_mais_200://CL020B	Sensor de corrente -200 a +200 (mA) e cabo (miniDIN-miniDIN)
      //   if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
      //          sprintf((char*) &_buflcd, "-%03d.%01 OK-%03d.%01dm",-1*((int16_t)AnalogS0.GetLastReading()),-1*((int16_t)AnalogS0.GetLastReading()%10),-1*AnalogS0.GetCalibValue(eCalibValueLow)/10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
      //       else                        
      //          sprintf((char*) &_buflcd, "%03d.%01dm OK %03d.%01dm",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
        
          fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),3, 'm',(uint8_t*)&_buflcd); 

       break;
       
        case eCurrent_menos_20_mais_20://CL020C	Sensor de corrente -20 a +20 (mA) e cabo (miniDIN-miniDIN)
      //     if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
      //          sprintf((char*) &_buflcd, "%02d.%01dmA OK% 02d.%01dmA",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
      //       else
      //          sprintf((char*) &_buflcd, "%02d.%01dmA OK %02d.%01dmA",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
 
        //      if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
        //        sprintf((char*) &_buflcd, "-%02d.%01dm OK-%02d.%01dmA",-1*(uint16_t)AnalogS0.GetLastReading(),-1*((uint16_t)AnalogS0.GetLastReading())%10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)/10),-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
        //     else
        //        sprintf((char*) &_buflcd, "%02d.%01dmA OK %02d.%01dmA",(uint16_t)AnalogS0.GetLastReading(),((uint16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
 
         fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),2, 'm',(uint8_t*)&_buflcd); 

            break;

        case eCampoMagnetico://CL021	Sensor de campo magnético -10 a +10 (G) e cabo de ligação (miniDIN-miniDIN)
          //   if(AnalogS0.GetCalibValue(eCalibValueLow)<0)
          //      sprintf((char*) &_buflcd, "-%02d.%01dG OK -%02d.%01dG",-1*(int16_t)AnalogS0.GetLastReading(),-1*((int16_t)AnalogS0.GetLastReading())%10,-1*(AnalogS0.GetCalibValue(eCalibValueLow)/10),-1*(AnalogS0.GetCalibValue(eCalibValueLow)%10));
          //   else
          //      sprintf((char*) &_buflcd, "%02d.%01dG  OK  %02d.%01dG",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
              fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),2, 'G',(uint8_t*)&_buflcd); 


            break;

        case eFluxo://CL058	Sensor de fluxo para água 0,3 a 6 (L/min)
            //sprintf((char*) &_buflcd, "%02d.%01dL  OK  %02d.%01dL",(int16_t)AnalogS0.GetLastReading(),((int16_t)AnalogS0.GetLastReading())%10,AnalogS0.GetCalibValue(eCalibValueLow)/10,AnalogS0.GetCalibValue(eCalibValueLow)%10);
              fomatLine((int16_t)AnalogS0.GetLastReading(),AnalogS0.GetCalibValue(eCalibValueLow),2, 'L',(uint8_t*)&_buflcd); 

            break;

        case  eNumSensor:
            break;

        
         }

        _buflcd[16]=0;

*/
