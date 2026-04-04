/********************************** NOME DO MODULO *******************************************//**
 *\file      HdsLcd.cpp

 Modulo de controle do Lcd

 *\brief     controle do Lcd
 *            
 * ----------------------------------------------------------------------------------------------
 * \version   1.00 - 
 * \date      04/01/22
 * ----------------------------------------------------------------------------------------------
 */

#include "HdsGpio.h"
#include "hdsLcd.h"
#include "specialchars.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define END_CHAR '\0'
#define END_LINE '\n'

#define DELAY_LCD_ENABLE  10

unsigned char lcdCurrentPosition;
static unsigned char lcdCursorPosition = LCD_NO_CURSOR;

char lcdVirtualScreen[LCD_LINE_COUNT][LCD_LINE_SIZE - 1];
static bool lcdBackLightState = false;

char *lcdVirtualCursor;

typedef struct {
    GPIO_TypeDef *ptrPort;
    uint16_t uiPin;
} sPort;

//!Sequencia dos bits
static sPort hLCDData[LCD_NUM_BITS] = {/*{LcdD0},{LcdD1},{LcdD2},{LcdD3},*/{ LcdD4 }, { LcdD5 }, { LcdD6 }, { LcdD7 } };




/*********************************************************************************************//**
 * \fn         LCD_DelayUs
 * \details    Função de delay para o LCD
               Ajustada para ter um delay de 1us a 84Mhz

 * \author     
 * \date        01/03/2021
 ************************************************************************************************/
void LCD_DelayUs(uint32_t ulValue) {

uint32_t localvalue=ulValue*5;
    do {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    } while (--localvalue > 0);
}

static void LCD_ConfigBus(EPortmode eDir) {
    for (uint8_t i = 0; i < LCD_NUM_BITS; i++)
        Gpio.GpioCfg(hLCDData[i].ptrPort, hLCDData[i].uiPin, NONE_RESISTOR, eDir, PORT_PUSH_PULL, PORT_LOW_SPEED);
}

static void LCD_SetCtrl(GPIO_TypeDef *Porta, uint16_t uiPin, EPortState eState) {
    Gpio.Write(Porta, uiPin, eState);
}

static bool LCD_GetBusy(void) {
    return Gpio.Read(hLCDData[3].ptrPort, hLCDData[3].uiPin);
}

static void LCD_SetData(uint8_t byte) {

    for (uint8_t i = 0; i < LCD_NUM_BITS; i++)
        Gpio.Write(hLCDData[i].ptrPort, hLCDData[i].uiPin, byte & (1 << i) ? ePortHigh : ePortLow);

    LCD_SetCtrl(LcdEnable, ePortHigh);

    /* Min 80ns */
    LCD_DelayUs(DELAY_LCD_ENABLE);

    LCD_SetCtrl(LcdEnable, ePortLow);
    /* Min 10ns */

}

/******************************************************  ***********************
 *   lcdHwInit
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  Inicia o HardWare do LCD
 *
 *   Inicializa os pinos para utizar o LCD
 *
 *
 *
 * @return  None
 *
 *****************************************************************************/
void lcdHwInit(void) {
    //configura pinos de Dados
    LCD_ConfigBus(eGPIOOutput);

    //Pinos de controle
    Gpio.GpioCfg(LcdRs, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdRw, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdEnable, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdOn, NONE_RESISTOR, eGPIOOutput, PORT_OPEN_DRAIN, PORT_LOW_SPEED);

    //! Liga o display 
//    LCD_SetCtrl(LcdOn, ePortHigh);
//    LCD_DelayUs(50000);

    LCD_SetCtrl(LcdOn, ePortLow);
    LCD_DelayUs(50000);

    LCD_SetCtrl(LcdRs, ePortLow);
    LCD_SetCtrl(LcdRw, ePortLow);

    LCD_DelayUs(LCD_DELAY);
    LCD_SetCtrl(LcdEnable, ePortLow);
    LCD_DelayUs(LCD_DELAY);

    //!Para configurar a interface
    LCD_WriteByte( LCD_CONFIG_GRP_FUNCTIONS, LCD_COMMAND);
    LCD_WriteByte( LCD_CONFIG_GRP_FUNCTIONS, LCD_COMMAND);
    LCD_WriteByte( LCD_CONFIG_GRP_FUNCTIONS, LCD_COMMAND);

    LCD_WriteByte( LCD_CONFIG_GRP_DISPLAY, LCD_COMMAND);
    LCD_WriteByte( LCD_CONFIG_GRP_CURSOR, LCD_COMMAND);

    LCD_ClearScreen();

  

    return;
}

/*****************************************************************************
 *   lcdWriteCmd
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve um byte no LCD
 *
 *    Escreve o byte input no lcd no barramento de comandos se COMMAND e no barramento de dados se !COMMAND
 *
 *
 * @param[input]   byte a ser escrito
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_WriteByte(unsigned char input, bool command) {
    LCD_ConfigBus(eGPIOOutput);
    /* Max slew rate time 20ns */

    LCD_SetCtrl(LcdRw, ePortLow);
    if (command == true) {
        LCD_SetCtrl(LcdRs, ePortLow);
        lcdCurrentPosition = input; // record input if it's a command
    } else {
        LCD_SetCtrl(LcdRs, ePortHigh);
        lcdCurrentPosition++; // increment current position if it's data
    }

    //! 4 bits mais significativos 
    LCD_SetData(input >> 4);

    /* Data cycle min 500ns */
    LCD_DelayUs(10);   //&***

    //! 4 bits menos significativos
    LCD_SetData(input);

    /* Data cycle min 500ns */
    // LCD_DelayUs( 10 );
    LCD_HoldWhileBusy();

}

/*****************************************************************************
 *   LCD_MakePosCommand
 *****************************************************************************/
/*!
 * @ingroup nome
 *
 * @brief  descrição breve
 *
 *
 * @param[n]   descrição do parâmetro n
 *
 * @return  valor de retorno
 *
 *****************************************************************************/
unsigned char LCD_MakePosCommand(unsigned short usPos, unsigned short usLine) {
    unsigned char ret = 0;

    lcdVirtualCursor = &lcdVirtualScreen[usLine][usPos];
    if (usLine == 0) {
        ret += LCD_LINE_1;
    } else if (usLine == 1) {
        ret += LCD_LINE_2;
    } else if (usLine == 2) {
        ret += LCD_LINE_3;
    } else if (usLine == 3) {
        ret += LCD_LINE_4;
    } else {
        ret = LCD_LINE_1;
    }

    ret += usPos;

    return ret;

}

/*****************************************************************************
 *   LCD_WriteString
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve uma string (char *) no LCD
 *
 *    Põe todos os caracteres de pcDisplay na tela até tamanho ucSize
 *
 *
 * @param[usPos]   posição inicial
 * @param[usLine]   linha
 * @param[ucSize]   Tamanho da string
 * @param[pcDisplay]   Vetor de caracteres a ser mostrado
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_WriteString(unsigned short usPos, unsigned short usLine, unsigned char ucSize, const char *pcDisplay) {
    unsigned char i;
    unsigned char ucPosCmd;

    ucPosCmd = LCD_MakePosCommand(usPos, usLine);

    LCD_WriteByte(ucPosCmd, LCD_COMMAND);

    for (i = 0; i < ucSize; i++) {
        LCD_WriteByte(LCD_OperateChar(*pcDisplay++), LCD_CHAR);
    }
}

/*****************************************************************************
 *   LCD_WriteSmartString
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve uma "smart" string (char * terminado com '\0') no LCD
 *
 *    Põe todos os caracteres de pcDisplay na tela até encontrar um '\0' (fim de string)
 *
 *
 * @param[usPos]   posição inicial
 * @param[usLine]   linha
 * @param[pcDisplay]   Vetor de caracteres a ser mostrado
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_WriteSmartString(unsigned short usPos, unsigned short usLine, const char *pcDisplay) {

    unsigned char ucPosCmd;

    ucPosCmd = LCD_MakePosCommand(usPos, usLine);

    LCD_WriteByte(ucPosCmd, LCD_COMMAND);
    while (*pcDisplay != END_CHAR) {
        LCD_WriteByte(LCD_OperateChar(*pcDisplay++), LCD_CHAR);
    }

}

void LCD_WriteRawString(unsigned short usPos, unsigned short usLine, const char *pcDisplay) {
    unsigned char ucPosCmd;

    ucPosCmd = LCD_MakePosCommand(usPos, usLine);

    LCD_WriteByte(ucPosCmd, LCD_COMMAND);
    while (*pcDisplay != END_CHAR) {
        LCD_WriteByte(*pcDisplay++, LCD_CHAR);
    }
}

void LCD_WriteDumbString(unsigned short usPos, unsigned short usLine, const char *pcDisplay, unsigned int sz) {
    unsigned char ucPosCmd;

    ucPosCmd = LCD_MakePosCommand(usPos, usLine);

    LCD_WriteByte(ucPosCmd, LCD_COMMAND);
    while (sz--) {
        char put = *pcDisplay == END_CHAR ? ' ' : *pcDisplay;
        LCD_WriteByte(LCD_OperateChar(put), LCD_CHAR);
        pcDisplay++;
    }
}

/*****************************************************************************
 *   LCD_WriteWordBreakString
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve uma string a partir das posições usPos e usLine com word break e retorna o ponto de parada do LCD
 *
 *
 *
 * @param[usPos]   posição inicial
 * @param[usLine]   linha virtual de início
 * @param[string]   Vetor de caracteres a ser mostrado
 *
 * @return  se existem mais linhas abaixo para serem exibidas
 *
 *****************************************************************************/
bool LCD_WriteWordBreakString(unsigned short usPos, unsigned short usLine, const char *string) {
    unsigned short startLine = usLine;
    unsigned short controlLine = 0;   //usLcdLine;
    usLine = 0;
    while (*string != END_CHAR && controlLine < LCD_LINE_COUNT) {
        const char *ptr = string;
        unsigned short counter = 0;
        while (*ptr != ' ' && *ptr != END_CHAR && *ptr != END_LINE) // looking for spaces or line breaks
        {
            counter++;
            ptr++;
        }

        if (usPos + counter >= LCD_LINE_SIZE) // too long -1
        {
            // do not change screen pointer, increment line
            usLine++;
            usPos = 0; // first position
            if (usLine > startLine) {
                controlLine++;
            }
        }

        else {
            if (*ptr != END_LINE) {
                if (*ptr != END_CHAR) {
                    if (usPos + counter < (LCD_LINE_SIZE - 1)) {
                        counter++; // include space
                    }
                }
//                else
//                {
//                    ptr--; // let string see this is over.
//                }
            }

            if (usLine >= startLine) {

                LCD_WriteString(usPos, controlLine, counter, string); // write it and move ahead

            }

            if (*ptr == ' ' && (usPos + counter == LCD_LINE_SIZE)) {
                counter++;
            }

            if (*ptr == END_LINE)  // force line end
            {
                //increment line
                usLine++;
                usPos = 0; // first position
                if (usLine > startLine) {
                    controlLine++;
                }

            } else if (*ptr == END_CHAR) {
                break;
            } else {
                usPos += counter;
                if (usPos == (LCD_LINE_SIZE - 1)) {
                    //increment line
                    usLine++;
                    usPos = 0; // first position
                    if (usLine > startLine) {
                        controlLine++;
                    }
                }
            }

            string = ++ptr;

        }
    }

    return (controlLine >= LCD_LINE_COUNT);

}

/*****************************************************************************
 *   LCD_ClearCGRAM
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  limpa todos os espaços CGRAM
 *
 *    Limpa todos os espaços CGRAM. Utilizado quando for escrita uma tela do zero.
 *
 *
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_ClearCGRAM(void) {
#if HAS_LCD_DISPLAY
    unsigned int i;

    for (i = 0; i < lcdSpecialCharCount; i++) {
        lcdSpecialChars[i].CGRamAddr = CGRAM_NO_ADDR;
        lcdSpecialChars[i].usedFlag = SPECIAL_CHAR_UNUSED;
    }
    lcdCGRamCount = 0;
    for (i = 0; i < CGRAM_SIZE; i++) {
        lcdUsedSpecialChars[i] = NULL;
    }
#endif
}

/*****************************************************************************
 *   LCD_ClearUnusedCGRAM
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  limpa os espaços não usados da CGRAM
 *
 *    Limpa os espaços não usados da CGRAM. Utilizado apenas quando for atualizar os valores da tela. (lcdPutMaskedScreen)
 *
 *
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_ClearUnusedCGRAM(void) {
#if HAS_LCD_DISPLAY
    unsigned int i;
    int usedChar = lcdCGRamCount;

    for (i = (lcdCGRamCount - 1); (i >= usedChar && lcdCGRamCount > 0); i--, lcdCGRamCount--) {
        lcdUsedSpecialChars[i]->CGRamAddr = CGRAM_NO_ADDR;
        lcdUsedSpecialChars[i]->usedFlag = SPECIAL_CHAR_UNUSED;
        lcdUsedSpecialChars[i] = NULL;
    }
#endif
}

/*****************************************************************************
 *   LCD_ClearScreen
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  limpa a tela
 *
 *    limpa o lcd ( Atenção: extremamente lento (~1.5ms) )
 *
 *
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_ClearScreen(void) {
//	unsigned int i;
// upon cleaning screen, reset all special chars priorities if cgram is full
    memset(lcdVirtualScreen, ' ', LCD_LINE_COUNT * (LCD_LINE_SIZE - 1));

    LCD_ClearCGRAM();

    LCD_WriteByte( LCD_CONFIG_CLEAR, LCD_COMMAND);

    LCD_DelayUs(2000);   //! todo resolver esse delay &***

    LCD_HoldWhileBusy();
}

/**
 @ingroup lcd
 @brief  Aguarda pino de busy do LCD ou timeout
 @return  None
 */
void LCD_HoldWhileBusy(void) {
    static int timeout = 0;

    LCD_SetCtrl(LcdRs, ePortLow);
    LCD_SetCtrl(LcdRw, ePortHigh);

    LCD_ConfigBus(eGPIOInput);
    /* Min 40ns */
    LCD_DelayUs(10);
    do {
        LCD_SetCtrl(LcdEnable, ePortHigh);
        LCD_DelayUs(10);

        if (LCD_GetBusy() == ePortHigh)
            break;

        LCD_SetCtrl(LcdEnable, ePortLow);
        /* Min 230ns */

        //LCD_DelayUs( 1 );
    } while ((++timeout <= 100));  //timeout 1ms

    /* Verificado em debug que os picos de timeout ficam em torno de 100. Desta
     * forma, fazemos 5*pico para garantir casos de LCDs mais lentos.
     * No pior dos casos o LCD não mostra algum caracter, melhor do que travar. */
    timeout = 0;
}


bool LCD_IsBackLightOn(void) {
    return lcdBackLightState;
}

/*****************************************************************************
 *   LCD_BackLightOn
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  liga ou desliga o Backlight do LCD
 *
 * @param[input]  TRUE/false Ligado/Desligado.
 *
 * @return  NONE
 *
 *****************************************************************************/
void LCD_BackLightOn( bool val) {
    lcdBackLightState = val;
}

void LCD_CheckChars(void) {
#if HAS_LCD_DISPLAY
    unsigned int i, j;
    for (i = 0; i < lcdSpecialCharCount; i++) {
        for (j = i + 1; j < lcdSpecialCharCount; j++) {
            if (lcdSpecialChars[i].ascii == lcdSpecialChars[j].ascii) {
#ifdef DEBUG
                while( 1 ); /* cgram is BAD BAD BAD */
            #endif
            }
        }
    }
#endif
}

/*****************************************************************************
 *   LCD_WriteCGRam
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve caracteres especiais na CGRAM
 *
 * @param[usPos]  posição X inicial no LCD
 * @param[usLine]  linha inicial no LCD*
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_WriteCGRam(unsigned short usPos, const char *deff) {
    unsigned short i;
    unsigned char previousPosition = lcdCurrentPosition; // record cursor position

    LCD_WriteByte(usPos * CHAR_HEIGHT + CGRAM_START_ADDR, LCD_COMMAND);
    for (i = 0; i < CHAR_HEIGHT; i++) {
        LCD_WriteByte(*deff++, LCD_CHAR); //data write to CGRAM
    }

    LCD_WriteByte(previousPosition, LCD_COMMAND); // put back cursor in old position
}

/*****************************************************************************
 *   LCD_OperateChar
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  opera caractere de entrada e retorna a transformação para código CGRAm se necessário
 *
 * @param[input]  caractere a ser operado
 *
 * @return  caractere transformado em endereço reconhecido pela CGRAm
 *
 *****************************************************************************/
char LCD_OperateChar(char input) {

    unsigned int i;
    char ret = input;
#if HAS_LCD_DISPLAY
    // Copia o caractere para o buffer virtual
    *lcdVirtualCursor++ = input;
    if (!( /* eliminar caracteres mais usados da verificação para performance! */
    // INT_BETWEEN(input , 'a' , 'z') ||
    //INT_BETWEEN( input, 'A', 'Z' ) ||
    //INT_BETWEEN( input, '0', '9' ) ||
    input == '.' || input == '-' || input == ' ')) {

        for (i = 0; i < lcdSpecialCharCount; i++) {
            if (input == lcdSpecialChars[i].ascii) // is special char
                    {
                if (lcdSpecialChars[i].CGRamAddr == CGRAM_NO_ADDR) // not present in CGRAM choose good placement
                {
                    if (lcdCGRamCount != CGRAM_SIZE) // cgram not full yet
                    {
                        lcdSpecialChars[i].CGRamAddr = lcdCGRamCount; // record position
                        LCD_WriteCGRam(lcdCGRamCount, lcdSpecialChars[i].draw); // put in cgram
                        lcdUsedSpecialChars[lcdCGRamCount] = &lcdSpecialChars[i];
                        lcdCGRamCount++; // increase used count
                    } else // CGRam is full, find unused char
                    {
                        unsigned int j;
                        for (j = 0; j < lcdSpecialCharCount; j++) {
                            if (lcdSpecialChars[j].CGRamAddr != CGRAM_NO_ADDR && lcdSpecialChars[j].usedFlag == SPECIAL_CHAR_UNUSED) {
                                LCD_WriteCGRam(lcdSpecialChars[j].CGRamAddr, lcdSpecialChars[i].draw); // put in cgram
                                lcdSpecialChars[i].CGRamAddr = lcdSpecialChars[j].CGRamAddr; // assume address
                                lcdSpecialChars[j].CGRamAddr = CGRAM_NO_ADDR; // record old char as unused
                                lcdUsedSpecialChars[lcdCGRamCount] = &lcdSpecialChars[i];
                                break; // quit looking
                            }
                        }
                    }
                }

                ret = lcdSpecialChars[i].CGRamAddr;
                lcdSpecialChars[i].usedFlag = SPECIAL_CHAR_USED; // used char

                //lcdUsedSpecialChars[ lcdCGRamCount ] =  & lcdSpecialChars[ i ];
                break;
            }
        }
    }
#endif    
    return ret;

}

/*****************************************************************************
 *   LCD_CalcAbsolutePosition
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  Calcula a posição absoluta do cursor dada sua posição na DDRAM
 *
 *
 * @param[value]  Posição na DDRAM
 *
 * @return  Posição absoluta
 *
 *****************************************************************************/
int LCD_CalcAbsolutePosition(int value) {
    int ret;

    if ((value >= LCD_LINE_1) && (value < (LCD_LINE_1 + (LCD_LINE_SIZE - 1)))) {
        ret = (0 * (LCD_LINE_SIZE - 1)) + value - LCD_LINE_1;
    } else if ((value >= LCD_LINE_2) && (value < (LCD_LINE_2 + (LCD_LINE_SIZE - 1)))) {
        ret = (1 * (LCD_LINE_SIZE - 1)) + value - LCD_LINE_2;
    } else if ((value >= LCD_LINE_3) && (value < (LCD_LINE_3 + (LCD_LINE_SIZE - 1)))) {
        ret = (2 * (LCD_LINE_SIZE - 1)) + value - LCD_LINE_3;
    } else if ((value >= LCD_LINE_4)) {
        ret = (3 * (LCD_LINE_SIZE - 1)) + value - LCD_LINE_4;
    }

    return ret;
}

/*****************************************************************************
 *   LCD_ClearCursor
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  Apaga o cursor
 *
 *    escreve os registradores para apagar o cursor
 *
 *
 *
 * @return  None
 *
 *****************************************************************************/
void LCD_ClearCursor(void) {

    LCD_SetCursorPosition( LCD_NO_CURSOR);
    LCD_WriteByte( LCD_CONFIG_GRP_CURSOR_OFF, LCD_COMMAND);
}

/*****************************************************************************
 *   LCD_PutCursor
 *****************************************************************************/
/*!
 * @ingroup lcd
 *
 * @brief  escreve os registradores para mostrar um cursor na posição desejada
 *
 *    escreve os registradores para mostrar um cursor na posição desejada
 *
 *
 * @param[usRelPos]  posição relativa ( para a esquerda ) para mover o cursors
 *
 *****************************************************************************/
void LCD_PutCursor(unsigned short usRelPos) {
    LCD_SetCursorPosition(LCD_CalcAbsolutePosition(usRelPos));

    LCD_WriteByte(usRelPos, LCD_COMMAND);
    LCD_WriteByte( LCD_CONFIG_GRP_CURSOR_ON, LCD_COMMAND);
}

unsigned char LCD_GetCurrentPosition(void) {
    return lcdCurrentPosition;
}

void LCD_SetCursorPosition(unsigned short value) {
    lcdCursorPosition = value;
}

unsigned char LCD_GetCursorPosition(void) {
    return lcdCursorPosition;
}

