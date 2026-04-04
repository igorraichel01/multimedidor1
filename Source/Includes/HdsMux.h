#ifndef __HDSMUXH
#define __HDSMUXH

#include <stdint.h>


const uint8_t ucNUM_MUXTIMERS = 12; ///< Numero máximo de temporizações em software
const uint8_t ucMUX_DEBUG   = 0;  ///<  timer geral para teste de alguma rotina 
const uint8_t ucMUX_TIMERS_5MS_INTERRUPTION =1;   //< para base de tempo de 5ms
const uint8_t ucMUX_LCD_BLOCK_MODE =2;      //< Timer para sair do modo bloqueio do Lcd
const uint8_t ucMUX_RESET_uC =3;           //< contador para reset do microcontrolador  
const uint8_t ucMUX_SENSOR_ANALOG_0 =4;
const uint8_t ucMUX_SENSOR_ANALOG_1 =5;
const uint8_t ucMUX_SENSOR_ANALOG_2 =6;
const uint8_t ucMUX_SENSOR_ANALOG_3 =7;
const uint8_t ucMUX_SENSOR_ANALOG_4 =8;
const uint8_t ucMUX_SENSOR_LE_AD   =9;


//! Ponteiros para funções de callBack
typedef void (*MuxFuncPointer)(void);

//! Estrutura de gerenciamento dos timers em software
typedef struct
{
  bool bEnabled, ///< Status de ativação
      bAutoRestart; ///< Configuração de reinicio automático
  uint16_t uiValue, ///< Tempo configurado em milisegundos
      uiReloadValue; ///< Tempo de recarga em milisegundos
  MuxFuncPointer pFunction; ///< Ponteiro para a função que será chamada ao expirar o timer
} TMuxTimerFields;

class TMuxTimers
{
private:
  //! Contador de 1ms do msTimeTicks
  volatile uint32_t _ulMsTimeTicks;
  
  //Variável para sinalizar um intervalo de tempo 
  uint32_t _ulMsDelay;
  uint32_t _ulMsTimeTicksNow;

  TMuxTimerFields _MuxTimers[ucNUM_MUXTIMERS];

public:
  //! Delay em ms     
  void Delayms(uint32_t  uldelay);
  //! Recupera contador de milisegundos da classe
  uint32_t GetMsTicks(void);
  //! Inicializa variáveis da classe e configura interrupção do timer para 1ms
  void Init(void);
  //! Método que deve ser chamado periodicamente pelo timer externo
  void OnTimerInterruption(void);
  //! Para a execução do timer
  void Stop(uint8_t ucIndex);  
  //! Inicializa um modulo de execução única
  void SingleRun(uint8_t ucIndex, uint16_t uiValue, MuxFuncPointer Function);
  //! Inicializa um modulo de execução repetitiva
  void LoopRun(uint8_t ucIndex, uint16_t uiValue, MuxFuncPointer Function);

  //! Configura intevalo de tempo para ser sinalizado 
  void SetMsDelay(uint32_t uldelay);

  //! Verifica se passou o tempo do delay   
  bool CheckMsDelay();


};

//! Exporta a classe para uso externo ao modulo
extern TMuxTimers MuxTimers;

#endif
