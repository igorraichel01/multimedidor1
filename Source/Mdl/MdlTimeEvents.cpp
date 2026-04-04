/********************************** NOME DO MODULO *******************************************//**
 *\file      MdlTimeEvents.cpp
 
 *\details   Gera a sinalização dos eventos de ms ( 5, 10, 100...)ms
 *
 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      23/03/2021
 ***********************************************************************************************/

/*************************************************************************************************
 Modulos incluidos
 *************************************************************************************************/
#include "MdlTimeEvents.h"
#include "HdsMux.h"

/*************************************************************************************************
 Prototipos de funcoes locais
 *************************************************************************************************/
void _MdlTime5Ms(void);

/*************************************************************************************************
 Diretivas de pre-processador
 *************************************************************************************************/

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
const uint8_t ucCST5MS = 5;
TTimeEvents TimeEvents;

/*************************************************************************************************
 Inicio do codigo
 *************************************************************************************************/

/*
 * \brief _MdlTime5Ms
 * \details  Chamada a cada evento de 5ms 
 */
void _MdlTime5Ms(void) {
    // Informa a classe de monitoramento
    TimeEvents.Interruption5ms();
}

/*
 * \brief Start
 * \details  Inicia classe
 */
void TTimeEvents::Start(void) {
    _uc100msCounter = 0;
    _uc1sCounter = 0;
    _uc10msCounter = 0;
    _bEvent5ms = false;
    _bEvent10ms = false;
    _bEvent100ms = false;
    _bEvent1s = false;

    // Inicializa o timer...
    MuxTimers.Init();

    // Ativa interrupcao de eventos
    MuxTimers.LoopRun(ucMUX_TIMERS_5MS_INTERRUPTION, ucCST5MS, _MdlTime5Ms);
}

/*
 * \brief   Interruption5ms
 * \details Deve ser chamada a cada 5ms por interrupcao 
 */
void TTimeEvents::Interruption5ms(void) {
    _bEvent5ms = true;

    // Incrementa contador para avaliar evento de 10ms
    if (++_uc10msCounter >= 2) {
        _bEvent10ms = true;
        _uc10msCounter = 0;
    }

    // Incrementa contador para avaliar evento de 100ms
    if (++_uc100msCounter >= 20) {
        _bEvent100ms = true;
        _uc100msCounter = 0;
    }

    // Incrementa contador para avaliar evento de 1s
    if (++_uc1sCounter >= 200) {
        _bEvent1s = true;
        _uc1sCounter = 0;
    }

}

/*
 * \brief   Event5ms
 * \details Retorna status de evento de 5ms, leitura atomica
 * \return  evento ocorrendo?
 */
bool TTimeEvents::Event5ms(void) {
    bool bStatus = _bEvent5ms;

    _bEvent5ms = 0;

    return (bStatus);
}

/*
 * \brief   Event10ms
 * \details Retorna status de evento de 10ms, leitura atomica
 * \return  evento ocorrendo?
 */
bool TTimeEvents::Event10ms(void) {
    bool bStatus = _bEvent10ms;

    _bEvent10ms = 0;

    return (bStatus);
}

/*
 * \brief   Event100ms
 * \details Retorna status de evento de 100ms, leitura atomica
 * \return  evento ocorrendo?
 */
bool TTimeEvents::Event100ms(void) {
    bool bStatus = _bEvent100ms;

    _bEvent100ms = 0;

    return (bStatus);
}

/*
 * \brief   Event1s
 * \details Retorna status de evento de 1s, leitura atomica
 * \return  evento ocorrendo?
 */
bool TTimeEvents::Event1s(void) {
    bool bStatus = _bEvent1s;

    _bEvent1s = 0;

    return (bStatus);
}
