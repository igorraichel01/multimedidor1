/********************************** NOME DO MODULO *******************************************//**
 *\file      Application.cpp
 *\details

 Codigo de aplicacao

 *\brief     Codigo de aplicacao, interface com usuario, hardware 
 * 
 * ----------------------------------------------------------------------------------------------
 * \version   1.00 - Primeira versão documentada
 * \date      16/10/2016
 * ----------------------------------------------------------------------------------------------
 * \version   1.01 - Primeira versão liberada para certificação
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



Alterações
22 /09 /2022  alterado a media das leituras de aritimética para exponencial com contatnes diferentes para digital e analógico
              Corrigido o processo de ajuste da temperatura, permite faixas intermediárias.
22 /09 /2022
vx.4         incluido ajuste de pressão e correção do cursor no inicio do ajuste

vx.5  incluído salvamento dos sensores digitais
      corrigido alguns travametnos do programa
      corrigido a indicação do teste dos sensores  



 restaurar calibração de fabrica no menu cal ( ultima posição) restaura de todos ao mesmo tempo
ocorreu de não aparecer o menu cal apos selecionar o modo analogico 
corrigir funcoes f7 e f8 
função f3 nao as vezes não pega as 10 passadas ( regua em queda livre)




sensor                      Calib       salv dados calib        arquivo pendrive
FORÇA                       ok           ok                      ok
Pressão dif                 ok           ok                      ok
Luminosidade                                                     ok
Tensão                       ok           ok                     ok
magnetico                   ok           ok                   
Fluxo                        ok           ok                   

luminosidade o valor vai até 5000. não conseguimos realizar o ajuste.

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
#include "hdsLcd.h"
#include "Hdsdisplay.h"
#include "HdsTeclado.h"
#include "MdlSensorAnalog.h"
#include "MdlEnsaio.h"
#include "main.h"
#include "fatfs.h"
#include "usb_host.h"
#include "HdsIFlash.h"
#include "MdlSensor.h"
#include "main.h"
#include "MdlCalib.h"



//! Declara a classe que controla a aplicação
TApplicationLL App;


/*********************************************************************************************//**
 * \brief Init
 * \param  nenhum
 * \details
 *  Dispara o inicio das temporizaçoes do software, faz algumas inicializações
 *************************************************************************************************/
void TApplicationLL::Init(void)
{
   Gpio.Init();
	
  //! Inicializa temporizacoes em software (Muxtimers)
   TimeEvents.Start();
	
	Teclado.Init();
	
	Lcd.Init();
	
	Ensaio.Init();

   _bTestPowerUp=true;  //Sinaliza borda de descida do botão 


   FlashStm32.Init();

   //!Recupera calibração da flash 
   Calib.Restore();

   //! Verifica se tem valores válidos para a calibração
   Calib.Validate(false); 
 
	 
}

/*********************************************************************************************//**
 * \brief   Stopf
 * \details Interrompe a aplicação, chamada após a detecção de uma queda de energia
 *************************************************************************************************/
void TApplicationLL::Stop(void)
{
 
}
#include "hdsLcd.h"
/*********************************************************************************************//**
 * \brief   Run
 * \details Laço eterno de execucao das tarefas do medidor com eventos em 
 *          escalas de 5ms, 10ms, 100ms e 1 seg de tempo.
 *          A execução é continua para os niveis de tensão adequados
 *************************************************************************************************/
void TApplicationLL::Run(void)
{

  //! Inicia o laço de execução
  while (1)
  {

    //Monitora a entrada USB
     MX_USB_HOST_Process();  


    //! Inicia ações conforme temporizacao
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
 * \details Funcoes de execução conforme evento de 10ms associado
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
 * \details Funcoes de execução conforme evento de 1 segundo associado
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


