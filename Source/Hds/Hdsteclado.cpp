/******************************************************************************
 *                                                                             *
 *   Programa......: TECLADO.C                                                *
 *   Versao........: 1.00                                                      *
 *   Data..........: 27/09/2012                                                *
 *   Atualizacao...: xx/xx/xxxx                                                *
 *   Projeto.......:                                                           *
 *   Programador...: Laércio Oliveira                                          *
 *   Compilador....:                                                           *
 *   Descricao.....: Trata Teclado                                             *
 *   Atualizado  ..: 01 03 2022                                                *
 *******************************************************************************/

#include "InventTypes.h"
#include "HdsTeclado.h"
#include "HdsGpio.h"

//! Declara a classe que controla e le o teclado 
TTeclado Teclado;

unsigned char DebounceTeclado[NUMLINHAS][NUMCOLUNAS];

uint8 P1; //FIXME  ACERTAR A PORTA CORRETA
uint8 ucTeclaPressionada = 0xFF;
uint16 ucTempoBuzzer = 0;

/*****************************************************************************
 ** Function name:	Init
 **
 ** Descriptions: Inicializa o hw do teclado 
 **
 ** parameters:  none
 ** Returned value:	tecla pressionada
 **
 * \author     
 * \date         08/01/2022
 ************************************************************************************************/
void TTeclado::Init() {

    Gpio.GpioCfg(TEC_COLUNA_1, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(TEC_COLUNA_2, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
 
    Gpio.GpioCfg(TEC_LINHA_1, PULL_UP, eGPIOInput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(TEC_LINHA_2, NONE_RESISTOR, eGPIOInput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(TEC_LINHA_3, PULL_UP, eGPIOInput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(TEC_LINHA_4, PULL_UP, eGPIOInput, PORT_PUSH_PULL, PORT_LOW_SPEED);

}

/*****************************************************************************
 ** Function name:	void TecladoGetTecla(void)
 **
 ** Descriptions: Retorna a ultima tecla pressionada que ainda esta valida
 **
 ** parameters:  none
 ** Returned value:	tecla pressionada
 **
 *****************************************************************************/
uint8 TTeclado::GetTecla(void) {
    uint8 ucKey = ucTeclaPressionada;
    ucTeclaPressionada = KEY_NONE_PRESSED;
    return ucKey;
}

/*****************************************************************************
 ** Function name:	void ResetTecla(void)
 **
 ** Descriptions: indica que essa tecla ja foi processda pela aplicação
 **
 ** parameters:  none
 ** Returned value:none
 **
 *****************************************************************************/
void TTeclado::ResetTecla(void) {
    ucTeclaPressionada = KEY_NONE_PRESSED;
}

/*
 * Faz a varredura do teclado, deve ser chamado de uma interrupção
 *
 * chamada a cada 1ms
 *
 */
void TTeclado::TeclaReading(void) {
    static uint8 ColunaAtual;
    static uint16 LinhasAcionadas = 0;
    static uint8 LinhaIndex = 0;

    // Aponta para a próxima coluna
    if (++ColunaAtual > NUMCOLUNAS - 1)
        ColunaAtual = 0;

    _AcionaColuna(ColunaAtual);

    // varre os bits de LinhasAcionadas
    for (LinhaIndex = 0; LinhaIndex < NUMLINHAS; LinhaIndex++) {

        switch (LinhaIndex) {
        case 0:
            LinhasAcionadas = LE_LINHA_1()
            ;
            break;
        case 1:
            LinhasAcionadas = LE_LINHA_2()
            ;
            break;
        case 2:
            LinhasAcionadas = LE_LINHA_3()

            ;
            break;
        case 3:
            LinhasAcionadas = LE_LINHA_4()
            ;
            break;
        }

        if (LinhasAcionadas == 0) { // se tecla está pressionada

            // incrementa contador de debounce, com controle de estouro

            if (DebounceTeclado[LinhaIndex][ColunaAtual] < TEMPO_DEBOUNCE)
                DebounceTeclado[LinhaIndex][ColunaAtual] += 1;
            else {
                if (DebounceTeclado[LinhaIndex][ColunaAtual] == TEMPO_DEBOUNCE) {
//@@				OutPut.Pulse(BUZZER, TEMPO_BUZZER_TECLADO);
                    DebounceTeclado[LinhaIndex][ColunaAtual] += 1;  //incrementa para nao tocar o beep varias vezes

                    //! Para simular os sensores pelo teclado
                    AnalisaTeclas();
                }
            }

        } else
            // tecla não está pressionada
            DebounceTeclado[LinhaIndex][ColunaAtual] = 0;
    }

    _DesligaColunas();

}

/*********************************************************************************************//**
 * \fn         _AcionaColuna
 * \brief      Aciona a coluna selecionada com nível 0
 * \details    
 * \author     
 * \date       03/11/2013
 ************************************************************************************************/
void TTeclado::_AcionaColuna(unsigned char ColunaLogica) {
    uint16 temp;

    if (ColunaLogica == 0) {
        COLUNA_1_LOW(); //!< coloca COL1 como saída e escreve ZERO
    }

    else if (ColunaLogica == 1) {
        COLUNA_2_LOW(); //!< coloca COL2 como saída e escreve ZERO
    }

    //delay
    for (temp = 0; temp < 1000; temp++) {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

}

/*********************************************************************************************//**
 * \fn         DesligaColunas
 * \brief      Coloca nivel Alto nas saidas das colunas 
 * \details    
 * \author     
 * \date       03/11/2013
 ************************************************************************************************/
void TTeclado::_DesligaColunas(void) {
    COLUNA_1_HIGH();
    COLUNA_2_HIGH();
}

/*****************************************************************************
 ** Function name:	void AnalisaTeclas(void)
 **
 ** Descriptions:Analisa se tem alguma tecla pressionada
 ** 	se sim envia para o menu processar a tecla e limpa  para uma proxima leitura

 **
 **Algumas teclas precisam ser sinalizadas quando foram pressionadas
 **  tecla 1 e 2 n teste da saidas
 **
 **
 ** parameters:
 ** Returned value:	None
 **
 *****************************************************************************/
void TTeclado::AnalisaTeclas(void) {
 //   extern char portab;
 //   extern void int_sensorS0();
 //   extern void int_sensores();
 //   extern int sensor0;
 //   extern int sensor1;
 //   extern int sensor2;
 //   extern int sensor3;
 //   extern int sensor4;

//    if (KEY_DATA_F1_DESL == PRESSIONADA) {
//        KEY_DATA_F1_DESL = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_DATA_F1_DESL_PRESSED;
//
//        portab = sensor1;
//        int_sensores();
//        ucTeclaPressionada = KEY_NONE_PRESSED;
//
//    }
//    if (KEY_DATA_F2_DESL == PRESSIONADA) {
//        KEY_DATA_F2_DESL = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_DATA_F2_DESL_PRESSED;
//
//        portab = sensor2;
//        int_sensores();
//        ucTeclaPressionada = KEY_NONE_PRESSED;
//
//    }
//    if (KEY_DATA_F3_DESL == PRESSIONADA) {
//        KEY_DATA_F3_DESL = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_DATA_F3_DESL_PRESSED;
//
//        portab = sensor3;
//        int_sensores();
//        ucTeclaPressionada = KEY_NONE_PRESSED;
//
//    }
//    if (KEY_DATA_F4_DESL == PRESSIONADA) {
//        KEY_DATA_F4_DESL = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_DATA_F4_DESL_PRESSED;
//
//        portab = sensor4;
//        int_sensores();
//        ucTeclaPressionada = KEY_NONE_PRESSED;
//
//    }
//    if (KEY_ENTER == PRESSIONADA) {
//        KEY_ENTER = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_ENTER_PRESSED;
//    }
//    if (KEY_NUM9 == PRESSIONADA) {
//        KEY_NUM9 = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_NUM9_PRESSED;
//
//        portab = sensor0;
//        int_sensorS0();
//        ucTeclaPressionada = KEY_NONE_PRESSED;
//
//    }
//    if (KEY_NUM6 == PRESSIONADA) {
//        KEY_NUM6 = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_NUM6_PRESSED;
//    }
//    if (KEY_NUM3 == PRESSIONADA) {
//        KEY_NUM3 = AGUARDANOVOPRESS;
//        ucTeclaPressionada = KEY_NUM3_PRESSED;
//    }
    if (KEY_NUM0== PRESSIONADA)
    {
        KEY_NUM0 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM0_PRESSED;
    }
    if (KEY_NUM8== PRESSIONADA)
    {
        KEY_NUM8 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM8_PRESSED;
    }
    if (KEY_NUM5== PRESSIONADA)
    {
        KEY_NUM5 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM5_PRESSED;
    }

    if (KEY_NUM2== PRESSIONADA)
    {
        KEY_NUM2 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM2_PRESSED;
    }

    if (KEY_ESC== PRESSIONADA)
    {
        KEY_ESC = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_ESC_PRESSED;
    }
    if (KEY_NUM7== PRESSIONADA)
    {
        KEY_NUM7 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM7_PRESSED;
    }
    if (KEY_NUM4== PRESSIONADA)
    {
        KEY_NUM4 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM4_PRESSED;
    }

    if (KEY_NUM1== PRESSIONADA)
    {
        KEY_NUM1 = AGUARDANOVOPRESS;
        ucTeclaPressionada = KEY_NUM1_PRESSED;
    }

}

