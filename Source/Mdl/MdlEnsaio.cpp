/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlEnsaio.cpp
 
 *\details   Módulo do fluxo inicial do firmware, 
 *           Mostra tela inicial
 *           Seleciona o idioma e tipo de teste (analogico ou digital)
 *
 *
 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "main.h"
#include "MdlEnsaio.h"
#include "Modo0.h"
#include "HdsTeclado.h"
#include "HdsMux.h"
#include "MdlMSG.h"
#include "MdlSensor.h"
#include "MdlEnsaioAnalogico.h"
#include "KBD2.h"
#include "MdlLcd.h"
#include "HdsDma.h"
#include "usb_host.h"


extern void startTimer(void);
extern void stopTimer(void);

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Ensaio Ensaio;


/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o módulo 

 * \author     
 * \date         08/01/2022
 ************************************************************************************************/
void C_Ensaio::Init(void) {

   EnsaioAnalogico.Init();

   //! Inicializa os sensores digitais 
  // SensorDigital.Init();

   //_eState = ENSAIO_RUN_ANALOG;//ENSAIO_START;

   _eState = ENSAIO_START;

  
}

/*********************************************************************************************//**
 * \function        Run
 * \details   Avança os estados da maquina de estados do ensaio do sensor  
 chamada a cada 100ms
 * \author     
 * \date         08/01/2022
 ************************************************************************************************/
void C_Ensaio::Run(void) {
  //  bool bBit;

    switch (_eState) {
    case ENSAIO_START:
        telaInicial_1();
        _uiTimedelay = 0;

        _eState = ENSAIO_WAIT_TELA_INICIAL;
        break;

    case ENSAIO_WAIT_TELA_INICIAL:
        if (_uiTimedelay++ > TEMPO_TELA) {
            _eState = ENSAIO_WAIT_IDIOMA;
            //!Mosgra tela de seleção de idioma
            tela990();
        }
        break;

    case ENSAIO_WAIT_IDIOMA:
        tecla_valida = Teclado.GetTecla();

        if (selecEstado990(tecla_valida)) {
            //Escolheu o idioma
            telaInicial_2(); //** CRONOMETRO **"
            _eState = ENSAIO_WAIT_TELA_INICIAL_2;
            _uiTimedelay = 0;
        }
        break;

    case ENSAIO_WAIT_TELA_INICIAL_2:
        if (_uiTimedelay++ > TEMPO_TELA) {
            _eState = ENSAIO_TIPO;
             MX_USB_HOST_Init();
        }
        break;

    case ENSAIO_TIPO:
        tecla_valida = Teclado.GetTecla();
        //Decide se é analoico ou digital
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_TIPO_SENSOR[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR__MAIOR[0]);

        //!Analisa a tecla
        if (tecla_valida == L_FUNC) {
            _eState = ENSAIO_RUN_ANALOG;

             MX_ADC1_Init();
          
            EnsaioAnalogico.Init();

        } else if (tecla_valida == R_FUNC) {
            // tela0(); 		// ESCOLHA A FUNCAO
            _eState = ENSAIO_RUN_DIGITAL;
        
            //! Desabilita o AD se estiver rodando 
             HAL_ADC_DeInit(&hadc1);
            

            //!configura Interrupções
            MX_GPIO_InterruptInit(); 
        
            tecla_valida = M_FUNC; //para entrar direto na tela de seleção dos sensores
            EstadoModo0(flagEstado);
            //Inicia leitura do AD 
            //DmaStartAdReading( CTE_ALPHA_DIGITAL);
        }
 
        else {

        }

        break;

    case ENSAIO_RUN_ANALOG:
        
       if (EnsaioAnalogico.Run() == eAnalogExit){
            _eState = ENSAIO_TIPO;
           }

         //if (tecla_valida == RESET) {
         //  _eState= ENSAIO_TIPO;
       // }
        break;

    case ENSAIO_RUN_DIGITAL:
        //! 	Le a tecla para o proximo estado
        tecla_valida = Teclado.GetTecla();

        //if(tecla_valida!= KEY_NONE_PRESSED){

        if (tecla_valida == RESET) {
             Modo = 0;
            Func=0;
            flag_funcao_5 = 0;
            flagTeclado = 0;
            flagEstado = 0;
            stopTimer();
            //modo0_zera_valores();
           _eState= ENSAIO_TIPO;
            DmaStopAdReading();
         
          if (Lcd.GetCursorState()) 
                Lcd.SetCursorOFF();
       
        }

        if (Modo == 0) {
            EstadoModo0(flagEstado);
        } else if (Modo == 1) {
             EstadoModo1(flagEstado);
        } else if (Modo == 2) {
             EstadoModo2(flagEstado);
        }

        if (flagEstado == 0) {
            stopTimer();
        }
        tecla_valida = KEY_NONE_PRESSED;

        break;
    case ENSAIO_DONE:
        break;
    }
}

