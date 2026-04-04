/********************************** NOME DO MODULO *******************************************//**
 *\file      Application.cpp
 *\details

 Codigo de aplicacao

 *\brief     Codigo de aplicacao, interface com usuario, hardware 
 * 
 * ----------------------------------------------------------------------------------------------
 * \version   1.00 - Primeira vers�o documentada
 * \date      16/10/2016
 * ----------------------------------------------------------------------------------------------
 * \version   1.01 - Primeira vers�o liberada para certifica��o
 * \date      16/10/2016
 * ----------------------------------------------------------------------------------------------
 
 chip usb
 https://github.com/djuseeq/Ch376msc/tree/master/src
  
 
 black pill
 https://innovatorsguru.com/stm32-black-pill/
 
 
 https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2.html
 
 video 
 https://www.youtube.com/watch?v=_bfROydrssA
 https://controllerstech.com/stm32-usb-host-msc/
 
 
 
 hdsmux usa timer 11 para gerar int de 1ms
 Mdlsensor usa timer 10 para gerar int de 50us
 

F12 OK
F11 OK  Sensores ficaram invertidos 
F10 OK  VER  REPETIR FUNCTION
F9  OK   VER  REPETIR FUNCTION 
F8 - esta diferente do modoelo atual
F7 - esta diferente do modoelo atual
F6  OK   VER  REPETIR FUNCTION  
F5  OK   VER  REPETIR FUNCTION   t freq  
F4  OK   VER  REPETIR FUNCTION   t freq     
F3  OK   VER  REPETIR FUNCTION
F2  OK   VER  REPETIR FUNCTION
 

quando usar o cube
alterar main.c para cpp
alterar usb_hos.c  para cpp
altear stm32f4xx_i.c para cpp



Altera��es
22 /09 /2022  alterado a media das leituras de aritim�tica para exponencial com contatnes diferentes para digital e anal�gico
              Corrigido o processo de ajuste da temperatura, permite faixas intermedi�rias.
22 /09 /2022
vx.4         incluido ajuste de press�o e corre��o do cursor no inicio do ajuste

vx.5  inclu�do salvamento dos sensores digitais
      corrigido alguns travametnos do programa
      corrigido a indica��o do teste dos sensores  



 restaurar calibra��o de fabrica no menu cal ( ultima posi��o) restaura de todos ao mesmo tempo
ocorreu de n�o aparecer o menu cal apos selecionar o modo analogico 
corrigir funcoes f7 e f8 
fun��o f3 nao as vezes n�o pega as 10 passadas ( regua em queda livre)




sensor                      Calib       salv dados calib        arquivo pendrive
FOR�A                       ok           ok                      ok
Press�o dif                 ok           ok                      ok
Luminosidade                                                     ok
Tens�o                       ok           ok                     ok
magnetico                   ok           ok                   
Fluxo                        ok           ok                   

luminosidade o valor vai at� 5000. n�o conseguimos realizar o ajuste.

 ************************************************************************************************/

/*************************************************************************************************
 Modulos incluidos
 *************************************************************************************************/
#include "stm32f4xx_hal.h"
#include "InventTypes.h"
#include "Application.h"
#include "MdlLcd.h"
#include "MdlTimeEvents.h"
#include "HdsGpio.h"
#include <string.h>
#include "HdsLCD.h"
#include "HdsDisplay.h"
#include "HdsTeclado.h"
#include "MdlSensorAnalog.h"
#include "MdlEnsaio.h"
#include "main.h"
#include "fatfs.h"
#include "usb_host.h"
#include "HdsIFlash.h"
#include "MdlSensor.h"
#include "Main.h"
#include "MdlCalib.h"



//! Declara a classe que controla a aplica��o
TApplicationLL App;

extern "C" {
  void App_Init(void) { App.Init(); }
  void App_Run(void)  { App.Run();  }
}


/*********************************************************************************************//**
 * \brief Init
 * \param  nenhum
 * \details
 *  Dispara o inicio das temporiza�oes do software, faz algumas inicializa��es
 *************************************************************************************************/
void TApplicationLL::Init(void)
{
   Gpio.Init();
	
  //! Inicializa temporizacoes em software (Muxtimers)
   TimeEvents.Start();
	
	Teclado.Init();
	
	Lcd.Init();
	
	Ensaio.Init();

   _bTestPowerUp=true;  //Sinaliza borda de descida do bot�o 


   FlashStm32.Init();

   //!Recupera calibra��o da flash 
   Calib.Restore();

   //! Verifica se tem valores v�lidos para a calibra��o
   Calib.Validate(false); 
 
	 
}

/*********************************************************************************************//**
 * \brief   Stopf
 * \details Interrompe a aplica��o, chamada ap�s a detec��o de uma queda de energia
 *************************************************************************************************/
void TApplicationLL::Stop(void)
{
 
}
#include "HdsLCD.h"
/*********************************************************************************************//**
 * \brief   Run
 * \details La�o eterno de execucao das tarefas do medidor com eventos em 
 *          escalas de 5ms, 10ms, 100ms e 1 seg de tempo.
 *          A execu��o � continua para os niveis de tens�o adequados
 *************************************************************************************************/
void TApplicationLL::Run(void)
{

  //! Inicia o la�o de execu��o
  while (1)
  {

    //Monitora a entrada USB
     MX_USB_HOST_Process();  


    //! Inicia a��es conforme temporizacao
    //! Eventos a cada 5ms
    if (TimeEvents.Event5ms())
    {
      _Run5msInterfaceEvents();
        
    }

    //! Eventoa a cada 10ms
    if (TimeEvents.Event10ms())
    {
      _Run10msInterfaceEvents();
			
         
        //  Gpio.Toggle(Led);

					
    }

    //! Eventos a cada 100ms
    if (TimeEvents.Event100ms())
    {
      _Run100msInterfaceEvents();
  
    } 

    //! Eventos a cada 1 segundo
    if (TimeEvents.Event1s())
    {
      _Run1sInterfaceEvents();
       		
    }

	}	



}



/*********************************************************************************************//**
 * \brief   _Run5msInterfaceEevents
 * \details Funcoes de execucao conforme evento de 5ms associado
 *************************************************************************************************/
void TApplicationLL::_Run5msInterfaceEvents(void)
{
 //! Leitura do teclado
  Teclado.TeclaReading();
	
	
	
}

/*********************************************************************************************//**
 * \brief   _Run10msInterfaceEevents
 * \details Funcoes de execu��o conforme evento de 10ms associado
 *************************************************************************************************/
void TApplicationLL::_Run10msInterfaceEvents(void)
{
static uint32_t ulcountTurnOff=0;  

//monitora o pino para desligar
    if(!Gpio.Read(BtLiga)){
       
      if((++ulcountTurnOff >10) & !_bTestPowerUp ){
        
            Gpio.Write(PowerON,ePortLow);
    
            //!espera o pino ir para zero    
            while(!Gpio.Read(BtLiga));
        }
      }
      else{
      ulcountTurnOff=0;
      _bTestPowerUp=false;
      }
    

}




/*********************************************************************************************//**
 * \brief   _Run100msInterfaceEevents
 * \details Funcoes de execucao conforme evento de 100ms associado
 *************************************************************************************************/
void TApplicationLL::_Run100msInterfaceEvents(void)
{
   //! Analise das teclas do teclado
   Teclado.AnalisaTeclas();
	
   Ensaio.Run();

   Lcd.Update();

	 //EnsaioDigital.Run();
	
	// EnsaioAnalogico.Run();
}



/*********************************************************************************************//**
 * \brief   _Run1sInterfaceEevents
 * \details Funcoes de execu��o conforme evento de 1 segundo associado
 *************************************************************************************************/
void TApplicationLL::_Run1sInterfaceEvents(void)
{
 //executa maquinas de estado dos sensores analogicos 
	 AnalogS0.Run();
	 AnalogS1.Run();
	 AnalogS2.Run();
	 AnalogS3.Run();
	 AnalogS4.Run();
     
	
}


