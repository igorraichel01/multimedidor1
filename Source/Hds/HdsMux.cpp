/********************************** NOME DO MODULO *******************************************//**
*\file     HdsMux.cpp
 
*\details    Módulo que controla temporizações por software.\n
*             Com este módulo é possivel gerar eventos de ocorrência única ou recorrentes.\n
*             As temporizações são geradas múltiplas de um timer de 1 milisegundo.
*          

* ----------------------------------------------------------------------------------------------
* \version   s.00 - Primeira versão documentada
* \date      23/03/2021
***********************************************************************************************/
#include "InventTypes.h"
#include "HdsMux.h"
#include "HdsGpio.h"
#include "MdlSensor.h"
#include "main.h"
#include "MdlSensorAnalog.h"

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
TMuxTimers MuxTimers;


extern "C" void DoNothing(void)
{
  return;
}

/*********************************************************************************************//**
 * \fn         Init
 * \details    Inicializa os temporizadores.
 * \author     
 * \date        23/03/2021
 ************************************************************************************************/
void TMuxTimers::Init(void)
{
  //! Inicializa a estrutura da classe
  for (uint8_t i = 0; i < ucNUM_MUXTIMERS; i++)
  {
    _MuxTimers[i].bEnabled = false;
    _MuxTimers[i].uiValue = 0;
    _MuxTimers[i].uiReloadValue = 0;
    _MuxTimers[i].pFunction = DoNothing;
  }

 // Inicializa o Timer 11
	
	RCC ->APB2ENR |= RCC_APB2ENR_TIM11EN;  //! habilita o clock do Timer 6
	TIM11 ->CR1 = TIM_CR1_CEN;  						//! Habilita o contador
	TIM11 ->CR2 = 0x0000; 									//! control register 2
	TIM11->PSC = 4;  										//! timer Prescaler
	TIM11->ARR= 16850;    									//! Auto reload
	TIM11->DIER |= TIM_DIER_UIE;  					//! Habilita interrupção
	TIM11->EGR = TIM_EGR_UG;       				//! Reinicializa o timer e gera uma atualização dos registros
	
	NVIC_EnableIRQ (TIM1_TRG_COM_TIM11_IRQn );  //! Habilita a interrupção do timer
    NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn , 0);   //! define a prioridade  0 é a mais alta
	
}




/*********************************************************************************************//**
 * \fn         Delay
 * \details    executa um delay em ms  
 *             uldelay recebe o valor do delay desejado 
 * \author     
 * \date       19/11/2021
 ************************************************************************************************/
void TMuxTimers::Delayms(uint32_t  uldelay)
{
   volatile uint32_t ulNow = _ulMsTimeTicks;
   
   while(true){
     if((_ulMsTimeTicks - ulNow) >=uldelay){
        break;
     }         
   }       
     
}


/*********************************************************************************************//**
 * \fn         SetMsDelay
 * \details    Configura o intervalo de tempo para ser sinalziado 
 * \author     
 * \date        27/05/2022
 * \return     uint32_t: contador de milisegundos
 ************************************************************************************************/
void TMuxTimers::SetMsDelay(uint32_t uldelay)
{
  _ulMsDelay=uldelay;

  //contagem de tempo atual  
  _ulMsTimeTicksNow=_ulMsTimeTicks;

}


/*********************************************************************************************//**
 * \fn         CheckMsDelay
 * \details    Verifica se passou o tempo 
 * \author     
 * \date        27/05/2022
 * \return     true se passou o tempo 
 ************************************************************************************************/
bool TMuxTimers::CheckMsDelay()
{
    if(_ulMsTimeTicks>( _ulMsTimeTicksNow+_ulMsDelay))
        return true;
    else 
        return false; 
}


/*********************************************************************************************//**
 * \fn         GetMsTicks
 * \brief      Retorna o valor do contador de 1 milisegundo.
 * \details    Retorna o valor do contador de 1 milisegundo.
 * \author     
 * \date        23/03/2021
 * \return     uint32_t: contador de milisegundos
 ************************************************************************************************/
uint32_t TMuxTimers::GetMsTicks(void)
{
  return (_ulMsTimeTicks);
}

/*********************************************************************************************//**
 * \fn         OnTimerInterruption
 * \details     Método que deve será chamado periodicamente pelo timer de temporização.
                Verifica as variáveis da classe disparando as temporizações configuradas.
 * \author    
 * \date        23/03/2021
 ************************************************************************************************/
void TMuxTimers::OnTimerInterruption(void)
{
  //! Verifica as temporizações configuradas na classe
  //! Atualiza os contadores e verifica se é hora de chamar a função de callBack
  for (uint8_t i = 0; i < ucNUM_MUXTIMERS; i++)
  {
    //! Verifica se a temporização está habilitada
    if (_MuxTimers[i].bEnabled)
    {
      //! Decrementa o contador e testa se é hora de chamar a função de callBack
      if (--_MuxTimers[i].uiValue == 0)
      {
        //! Chama a função de callBack passada como parâmetro
        _MuxTimers[i].pFunction();

        //! Verifica se é temporização de evento recorrente
        if (_MuxTimers[i].bAutoRestart == 1)
        {
          //! Se for, atualiza valores e reinicializa
          _MuxTimers[i].uiValue = _MuxTimers[i].uiReloadValue;
          _MuxTimers[i].bEnabled = true;
        }
        else
        {
          //! Se for temporização de evento único, desativa temporização
          _MuxTimers[i].bEnabled = false;
        }
      }
    }
  }
	
	//! Incrementa contador de 1ms
	_ulMsTimeTicks++;
}


/*********************************************************************************************//**
 * \fn         Stop
 * \details    para a execução do timer 
 * \author     
 * \date       23/03/2021
 * \param      index: indice do array muxtimers a ser utilizado

 ************************************************************************************************/
void TMuxTimers::Stop(uint8_t ucIndex)
{
  if ((ucIndex < ucNUM_MUXTIMERS))
  {
    _MuxTimers[ucIndex].bEnabled = false;
  }
}



/*********************************************************************************************//**
 * \fn         SingleRun
 * \details    Configura uma temporização para gerar um evento único em um tempo específico.
 * \author     
 * \date       23/03/2021
 * \param      index: indice do array muxtimers a ser utilizado
 * \param      uiValue: tempo em milissegundos a ser empregado
 * \param      Function: ponteiro para a função que será chamada após o tempo programado
 ************************************************************************************************/
void TMuxTimers::SingleRun(uint8_t ucIndex, uint16_t uiValue, MuxFuncPointer Function)
{
  if ((ucIndex < ucNUM_MUXTIMERS) && (uiValue > 0))
  {
    _MuxTimers[ucIndex].uiValue = uiValue;
    _MuxTimers[ucIndex].bAutoRestart = 0;
    _MuxTimers[ucIndex].pFunction = (MuxFuncPointer) Function;
    _MuxTimers[ucIndex].bEnabled = true;
  }
}

/*********************************************************************************************//**
 * \fn         LoopRun
 * \details    Configura uma temporização para gerar um evento recorrente em um tempo específico.
 * \author     
 * \date       23/03/2021
 * \param      index: indice do array muxtimers a ser utilizado
 * \param      uiValue: tempo em milissegundos a ser empregado
 * \param      Function: ponteiro para a função que será chamada após o tempo programado
 ************************************************************************************************/
void TMuxTimers::LoopRun(uint8_t ucIndex, uint16_t uiValue, MuxFuncPointer Function)
{
  if ((ucIndex < ucNUM_MUXTIMERS) && (uiValue > 0))
  {
    _MuxTimers[ucIndex].uiReloadValue = _MuxTimers[ucIndex].uiValue = uiValue;
    _MuxTimers[ucIndex].bAutoRestart = 1;
    _MuxTimers[ucIndex].pFunction = (MuxFuncPointer) Function;
    _MuxTimers[ucIndex].bEnabled = true;
  }
}

/*********************************************************************************************//**
 * \fn         TIM6_IRQHandler
 * \brief      Rotina que trata a interrupcao do timer de temporização.
 * \details    Este método chama a funcao de processamento dentro classe.
 * \author     
 * \date       23/03/2021
 ************************************************************************************************/
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	//! Verifica se a interrupção gerada no TIM1 é de atualização do contador
  if ((TIM11->SR & TIM_SR_UIF )!= 0){
   
  

		//! chama os timers
    MuxTimers.OnTimerInterruption();
    //! Limpa flag do timer
    TIM11 ->SR &= (~(TIM_SR_UIF ));
   
    //HAL_ADC_Start_DMA(&hadc1,&SensorDigital.ulAdValues[0],5);

  }
}

