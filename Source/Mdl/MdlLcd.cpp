/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlLcd.cpp
 
 *\details   Módulo para controle das telas do LCD
 *		
 *

 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "MdlLcd.h"
#include "hdsLcd.h"
#include <stdio.h>
#include <string.h>

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Lcd Lcd;

/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o módulo 

 * \author     
 * \date        31/05/2021
 ************************************************************************************************/
void C_Lcd::Init(void) {

    lcdHwInit();

    // Update();

    Write(0, (char*) "MULTICRONOMETRO ");
    Write(1, (char*) "   VERSÃO 1.0   ");

}

/*********************************************************************************************//**
 * \function        Update(void) {
 uint8_t sLinha[21];

 * \details   Atualiza a tela do display 
 *\           monta toda a tela e envia para o display

 * \author     
 * \date        31/05/2021
 ************************************************************************************************/
void C_Lcd::Update(void) {

//	LCD_ClearScreen();
    LCD_WriteSmartString(0, 0, (char*) &_screen[0][0]);
    LCD_WriteSmartString(0, 1, (char*) &_screen[1][0]);

    if (_bFlagCursorON)
        LCD_WriteByte(_ucCursorPosition, LCD_COMMAND);

}

void C_Lcd::Write(uint32_t uwLine, char *pucLine) {
    memset((char*) &_screen[uwLine][0], 0x20, sizeof(_screen[0]));

    for (int c = 0; c < LCD_NUM_COLUNAS; c++) {
        if (pucLine[c] == '\0')
            break;
        _screen[uwLine][c] = pucLine[c];
    }

    //finaliza a ultima sring
    _screen[uwLine][LCD_NUM_COLUNAS] = 0;

  //@  LCD_WriteSmartString(0, uwLine, (char*) &_screen[uwLine][0]);

   // if (_bFlagCursorON)
   //     LCD_WriteByte(_ucCursorPosition, LCD_COMMAND);
    
}

/*********************************************************************************************//**
 * \function        Add


 * \details   Adiciona uma string ao buffer de escrita no Lcd 
 *\           

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_Lcd::Add(char *pData) {
    uint8 ucSize = strlen(pData);
    uint8 ucEndposition = _ucPosition + ucSize;

    if (ucEndposition > LCD_NUM_COLUNAS)
        ucEndposition = LCD_NUM_COLUNAS;

    for (int c = _ucPosition; c < ucEndposition; c++) {
        _screen[_ucLine][_ucPosition] = *pData++;

        _ucPosition++;
    }

    //finaliza a ultima sring
    _screen[_ucLine][LCD_NUM_COLUNAS] = 0;

 //@   LCD_WriteSmartString(0, _ucLine, (char*) &_screen[_ucLine][0]);

    if (_bFlagCursorON)
        LCD_WriteByte(_ucCursorPosition, LCD_COMMAND);

}

/*********************************************************************************************//**
 * \function        Setxy


 * \details   Configura a posicao x y 
 *\           

 * \author     
 * \date        11/01/2022
 ************************************************************************************************/
void C_Lcd::Setxy(uint8 x, uint8 y) {
    _ucPosition = x;

    _ucLine = y;

}

/*********************************************************************************************//**
 * \function        SetCursorOFF


 * \details   Desliga o cursor  *\           

 * \author     
 * \date        14/01/2022
 ************************************************************************************************/
void C_Lcd::SetCursorOFF() {
    LCD_WriteByte( LCD_CONFIG_GRP_CURSOR_OFF, LCD_COMMAND);
    _bFlagCursorON = false;
}

/*********************************************************************************************//**
 * \function        SetCursorOn


 * \details   Liga o cursor           

 * \author     
 * \date        14/01/2022
 ************************************************************************************************/
void C_Lcd::SetCursorOn() {
    LCD_WriteByte( LCD_CONFIG_GRP_CURSOR_OFF, LCD_COMMAND);
    _bFlagCursorON = true;
}

/*********************************************************************************************//**
 * \function        GetCusorState


 * \details   Retorna o estado do cursor  true ligado,  false desligado           

 * \author     
 * \date        14/01/2022
 ************************************************************************************************/
uint8 C_Lcd::GetCursorState() {
    return _bFlagCursorON;
}

/*********************************************************************************************//**
 * \function        SetCursorPosition


 * \details   Posiciona o cursor           

 * \author     
 * \date        14/01/2022
 ************************************************************************************************/
void C_Lcd::SetCursorPosition(uint8 ucPosicao, uint8_t ucLinha) {

    _ucCursorPosition = LCD_MakePosCommand(ucPosicao, ucLinha);

    LCD_WriteByte(_ucCursorPosition, LCD_COMMAND);

}



