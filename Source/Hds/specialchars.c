/*!
* @file lcdSpecialChars.c   
* @brief Driver do LCD
*
*    Caracteres especiais
*           
* *\brief     Interface com o hardware de comunicacao serial
 *            
 * ----------------------------------------------------------------------------------------------
 * \version   1.00 - 
 * \date      01/04/2021
 * ----------------------------------------------------------------------------------------------
 */
 
#include "hdsLcd.h"

#define _X_ 1
#define ___ 0
#define CONCAT( b4,b3,b2,b1,b0 )  b4 << 4 | b3 << 3 | b2 << 2 | b1 << 1  | b0

#define CHAR_HEIGHT 8 
#define CGRAM_SIZE 8
#define CGRAM_START_ADDR 0x40
#define CGRAM_NO_ADDR 0xFF

#define SPECIAL_CHAR_UNUSED  0x00
#define SPECIAL_CHAR_USED    0x01

#define HAS_LCD_DISPLAY  1

#if HAS_LCD_DISPLAY
const char charAlarmDisabled[CHAR_HEIGHT] =  {               //ñ
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charAlarmReset[CHAR_HEIGHT] =  {               //ñ
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charNTilde[CHAR_HEIGHT] =  {               //ñ
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charCCidille[CHAR_HEIGHT] =  {              //ç
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
};

const char charATilde[CHAR_HEIGHT] =  {              //ã
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charACirc[CHAR_HEIGHT] =  {              //â
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charOTilde[CHAR_HEIGHT] =  {               //õ
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOAcc[CHAR_HEIGHT] =  {               //ó
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOCirc[CHAR_HEIGHT] =  {               //ô
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charECirc[CHAR_HEIGHT] =  {               //ê
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charEAcc[CHAR_HEIGHT] =  {               //é
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charAAcc[CHAR_HEIGHT] =  {               //á
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charAGrv[CHAR_HEIGHT] =  {               //á
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charIAcc[CHAR_HEIGHT] =  {               //í
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charUAcc[CHAR_HEIGHT] =  {               //ú
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charNUTilde[CHAR_HEIGHT] =  {              //Ñ
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charCUCidille[CHAR_HEIGHT] =  {              //Ç
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
};

const char charAUTilde[CHAR_HEIGHT] =  {              //Ã
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charAUCirc[CHAR_HEIGHT] =  {              //Â
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charOUTilde[CHAR_HEIGHT] =  {               //Õ
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOUAcc[CHAR_HEIGHT] =  {               //Ó
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOUCirc[CHAR_HEIGHT] =  {               //Ô
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charEUCirc[CHAR_HEIGHT] =  {               //Ê
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charEUAcc[CHAR_HEIGHT] =  {               //É
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charAUAcc[CHAR_HEIGHT] =  {               //Á
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charAUGrv[CHAR_HEIGHT] =  {               //À
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charIUAcc[CHAR_HEIGHT] =  {               //Í
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charUUAcc[CHAR_HEIGHT] =  {               //Ú
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charPLup[CHAR_HEIGHT] =  {               //pulso_subida
CONCAT(  ___ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
};

const char charPLdown[CHAR_HEIGHT] =  {               //pulso_descida
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , _X_ , _X_    )   ,
};

const char charRLopen[CHAR_HEIGHT] =  {               //rele_aberto
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charRLclose[CHAR_HEIGHT] =  {               //rele_fechado
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charArrowDown[CHAR_HEIGHT] =  {               //Seta Para Baixo
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charArrowUp[CHAR_HEIGHT] =  {               //Seta Para Cima
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charArrowLeft[CHAR_HEIGHT] =  {                //Seta Para Esquerda
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charArrowRight[CHAR_HEIGHT] =  {                //Seta Para Direita
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charAsubs[CHAR_HEIGHT] =  {                //A subscrito
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charBsubs[CHAR_HEIGHT] =  {                //B subscrito
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charCsubs[CHAR_HEIGHT] =  {                //C subscrito
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charNsubs[CHAR_HEIGHT] =  {                //N subscrito
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};



const char charNumber[CHAR_HEIGHT] =  {              //n°
CONCAT(  ___ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charWaves[CHAR_HEIGHT] =  {              // .))
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,	
};

const char charBlock[CHAR_HEIGHT] =  {              // .))
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charPi[CHAR_HEIGHT] =  {              //Pi
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charHrmGroup[CHAR_HEIGHT] =  {              //Hrm Group
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charHrmSGroup[CHAR_HEIGHT] =  {              //Hrm Sub-Group
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charAngle[CHAR_HEIGHT] =  {              //Angle
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};


const char charDegree[CHAR_HEIGHT] =  {              //Degree
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charOrdinal[CHAR_HEIGHT] =  {              //Ordinal
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charUpDown[CHAR_HEIGHT] =  {              //Up Down Arrow
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char0subs[CHAR_HEIGHT] =  {              //0 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char1subs[CHAR_HEIGHT] =  {              //1 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char2subs[CHAR_HEIGHT] =  {              //2 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char3subs[CHAR_HEIGHT] =  {              //3 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char4subs[CHAR_HEIGHT] =  {              //4 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char5subs[CHAR_HEIGHT] =  {              //5 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char6subs[CHAR_HEIGHT] =  {              //6 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char7subs[CHAR_HEIGHT] =  {              //7 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char8subs[CHAR_HEIGHT] =  {              //8 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char char9subs[CHAR_HEIGHT] =  {              //9 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charPhi[CHAR_HEIGHT] =  {              //Phi
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
};

const char charSep1[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
};

const char charSep2[CHAR_HEIGHT] = {
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
};

const char charInfo[CHAR_HEIGHT] = {
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charEnter[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charDelta[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charLt[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
};

const char charGt[CHAR_HEIGHT] = {
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
};

const char charBlack[CHAR_HEIGHT] = {
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,    
};

const char charHalfBlack[CHAR_HEIGHT] = {
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,    
};

const char charHourglass1[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charHourglass2[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,        
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charHourglass3[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,    
};

const char charApprox[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
};

const char charBar34[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,    
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , ___    )   ,    
};

const char charBar3[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,    
};

const char charBar12[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , _X_    )   ,    
};

const char charBar1[CHAR_HEIGHT] = {
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,    
};

const char charCircleFilled[CHAR_HEIGHT] = { 
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,    
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,    
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,    
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,        
};

const char charCircleEmpty[CHAR_HEIGHT] = {         
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,    
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,     
};

const char charAlrFilled[CHAR_HEIGHT] = {         
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,    
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,    
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,     
};

const char charAlrEmpty[CHAR_HEIGHT] = {         
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , _X_ , ___    )   ,    
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,    
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,    
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,     
};

const char charEsubs[CHAR_HEIGHT] =  {              //3 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charIsubs[CHAR_HEIGHT] =  {              //3 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charPsubs[CHAR_HEIGHT] =  {              //3 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charOsubs[CHAR_HEIGHT] =  {              //3 subs
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};



unsigned  char lcdCGRamCount = 0;

 sSpecialChar lcdSpecialChars[] =
{ 
    // ascii , drawing       ,  CGRAM address, prio 
    //{ 'Ù'    , charAlrFilled , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Û'    , (char *)&charAlrEmpty  , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'ñ'    , (char *)&charNTilde    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ã'    , (char *)&charATilde    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'õ'    , (char *)&charOTilde    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ç'    , (char *)&charCCidille  , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'á'    , (char *)&charAAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'à'    , (char *)&charAGrv      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'é'    , (char *)&charEAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'í'    , (char *)&charIAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ó'    , (char *)&charOAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'â'    , (char *)&charACirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ê'    , (char *)&charECirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ô'    , (char *)&charOCirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'ú'    , (char *)&charUAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ñ'    , (char *)&charNUTilde   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'Ã'    , (char *)&charAUTilde   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'Õ'    , (char *)&charOUTilde   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'Ç'    , (char *)&charCUCidille , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'Á'    , (char *)&charAUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//	  { 'À'    , (char *)&charAUGrv     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { 'É'    , (char *)&charEUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Í'    , (char *)&charIUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ó'    , (char *)&charOUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Â'    , (char *)&charAUCirc    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ê'    , (char *)&charEUCirc    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ô'    , (char *)&charOUCirc    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ú'    , (char *)&charUUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '$'    , (char *)&charPLup      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '¢'    , (char *)&charPLdown    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'ü'    , (char *)&charRLopen    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '£'    , (char *)&charRLclose   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'ð'    , (char *)&charArrowDown , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , // Alt+208
//    { 'ÿ'    , (char *)&charArrowUp   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '¥'    , (char *)&charArrowLeft , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '·'    , (char *)&charArrowRight, CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , // Alt+250 
//    { '¬'    , (char *)&charNumber    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,    
//    { '~'    , (char *)&charWaves     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'þ'    , (char *)&charBlock     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { 'å'    , (char *)&charAsubs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , // Alt+134 
//    { 'ß'    , (char *)&charBsubs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , // Alt+225 
//    { '©'    , (char *)&charCsubs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , // Alt+169
//    { 'œ'    , (char *)&charNsubs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Ý'    , (char *)&charHrmSGroup , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+237
//    { 'ý'    , (char *)&charHrmGroup  , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+236
//    { 'Å'    , (char *)&charAngle     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { '°'    , (char *)&charDegree    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'º'    , (char *)&charOrdinal   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
//    { 'Þ'    , (char *)&charUpDown    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+232    
//    { 'ï'    , (char *)&char0subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+139 	
//    { 'î'    , (char *)&char1subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+140
//    { 'ì'    , (char *)&char2subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+141 
//    { 'Ä'    , (char *)&char3subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+142
////     { 'Æ'    , char4subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+146
////     { 'û'    , char5subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+150
////     { 'ù'    , char6subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+151
////     { '¡'    , char7subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+173
////     { '×'    , char8subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+158
////     { '®'    , char9subs     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+169
//    { 'ø'    , (char *)&charPhi       , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+155
//    { '¹'	 , (char *)&charSep1		 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+155
//    { '²'	 , (char *)&charSep2		 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+157
//    { 'æ'	 , (char *)&charInfo		 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+145
//    { '¿'	 , (char *)&charEnter	 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+168
//    { '®'	 , (char *)&charDelta	 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+169
//    { '½'	 , (char *)&charLt 	 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+171
//    { '¼'	 , (char *)&charGt 	 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+172    
//    { CH_HALF_BLACK_HEX	 , (char *)&charHalfBlack , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { CH_HGLASS_1_HEX	 , (char *)&charHourglass1 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { CH_HGLASS_2_HEX	 , (char *)&charHourglass2 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { CH_HGLASS_3_HEX	 , (char *)&charHourglass3 , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { '¨'           	 , (char *)&charApprox     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , 
//    { '¦'                , (char *)&charBar34      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+176
//    { '¡'                , (char *)&charBar3       , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+173
//    { '«'                , (char *)&charBar12      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+174
//    { '»'                , (char *)&charBar1       , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+175		
//    { 'Æ'    , (char *)&charCircleFilled       , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+146
//    { 'û'     , (char *)&charCircleEmpty       , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } , //Alt+150
//    { 'è' , (char *)&charAlarmDisabled , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED }, // Alt+208
//    { 'È' , (char *)&charAlarmReset , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED }, // Alt+208
//	{ 'Ù' , (char *)&charEsubs , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED },
//	{ 'ù' , (char *)&charIsubs , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED },
//	{ 'Ü' , (char *)&charPsubs , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED },
//	{ 'Ë' , (char *)&charOsubs , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED },
    
};    

const unsigned int lcdSpecialCharCount = sizeof( lcdSpecialChars ) / sizeof( sSpecialChar );

sSpecialChar * lcdUsedSpecialChars[ CGRAM_SIZE ];

#endif
