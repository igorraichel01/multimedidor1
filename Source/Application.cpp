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

/*=================================================================================
 PROGRAMA BASICO - Liga o multimedidor e escreve "Ola" no display
 
 Fluxo:
   1. Gpio.Init()        -> Habilita clocks, configura pinos, PA3=HIGH (mantem ligado)
   2. TimeEvents.Start() -> Inicia temporizacoes de 5ms/10ms/100ms/1s
   3. Lcd.Init()          -> Inicializa o hardware do LCD 16x2
   4. Lcd.Write(linha, texto) -> Escreve "Ola" no buffer do LCD
   5. Loop principal       -> Lcd.Update() a cada 100ms envia buffer para o display
 
 Pinos importantes:
   PA3 (PowerON)  - Mantem a placa ligada (latch de energia)
   PA2 (BtLiga)   - Botao liga/desliga
   PA8  (LcdEnable), PA9 (LcdRw), PA10 (LcdRs) - Controle do LCD
   PB12..PB15 (LcdD4..D7) - Dados do LCD (modo 4 bits)
   PA6 (LcdOn)    - Habilita o LCD
=================================================================================*/



//! Declara a classe que controla a aplica��o
TApplicationLL App;


/*********************************************************************************************//**
 * \brief Init
 * \param  nenhum
 * \details
 *  Dispara o inicio das temporiza�oes do software, faz algumas inicializa��es
 *************************************************************************************************/
void TApplicationLL::Init(void)
{
   //! 1. Inicializa GPIO - habilita clocks e configura pinos
   //!    Isso tambem seta PA3 (PowerON) = HIGH, mantendo a placa ligada
   Gpio.Init();
	
   //! 2. Inicializa temporizacoes em software (gera eventos de 5ms, 10ms, 100ms, 1s)
   TimeEvents.Start();
	
   //! 3. Inicializa o teclado (necessario para detectar o botao de desligar)
   Teclado.Init();

   //! 4. Inicializa o hardware do LCD (configura pinos, envia sequencia de init do HD44780)
   Lcd.Init();

   //! 5. Escreve "Ola!" no display - linha 0 (superior) e linha 1 (inferior)
   Lcd.Write(0, (char*) "     Ola!       ");
   Lcd.Write(1, (char*) " Multimedidor   ");

   //! Sinaliza borda de powerup (para ignorar o primeiro press do botao)
   _bTestPowerUp = true;
}

/*********************************************************************************************//**
 * \brief   Stopf
 * \details Interrompe a aplica��o, chamada ap�s a detec��o de uma queda de energia
 *************************************************************************************************/
void TApplicationLL::Stop(void)
{
 
}

/*********************************************************************************************//**
 * \brief   Run
 * \details Laco principal - apenas atualiza o LCD a cada 100ms e monitora o botao de desligar
 *************************************************************************************************/
void TApplicationLL::Run(void)
{

  //! Inicia o laco de execucao
  while (1)
  {

    //! Eventos a cada 10ms - monitora botao de desligar
    if (TimeEvents.Event10ms())
    {
      _Run10msInterfaceEvents();
    }

    //! Eventos a cada 100ms - atualiza o LCD
    if (TimeEvents.Event100ms())
    {
      _Run100msInterfaceEvents();
    } 

	}	

}



/*********************************************************************************************//**
 * \brief   _Run5msInterfaceEvents
 * \details Nao utilizado neste programa basico
 *************************************************************************************************/
void TApplicationLL::_Run5msInterfaceEvents(void)
{
   // Nao utilizado no programa basico
}

/*********************************************************************************************//**
 * \brief   _Run10msInterfaceEvents
 * \details Monitora o botao liga/desliga para permitir desligar o equipamento
 *************************************************************************************************/
void TApplicationLL::_Run10msInterfaceEvents(void)
{
static uint32_t ulcountTurnOff=0;  

//monitora o pino PA2 (BtLiga) para desligar
    if(!Gpio.Read(BtLiga)){
       
      if((++ulcountTurnOff >10) & !_bTestPowerUp ){
        
            Gpio.Write(PowerON,ePortLow);  // Desliga a placa (PA3 = LOW)
    
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
 * \brief   _Run100msInterfaceEvents
 * \details Atualiza o display LCD a cada 100ms (envia o buffer para o hardware)
 *************************************************************************************************/
void TApplicationLL::_Run100msInterfaceEvents(void)
{
   //! Envia o conteudo do buffer do LCD para o display fisico
   Lcd.Update();
}



/*********************************************************************************************//**
 * \brief   _Run1sInterfaceEvents
 * \details Nao utilizado neste programa basico
 *************************************************************************************************/
void TApplicationLL::_Run1sInterfaceEvents(void)
{
   // Nao utilizado no programa basico
}
