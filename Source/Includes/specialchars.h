
#ifndef __SPECIAL_CHARS__
#define __SPECIAL_CHARS__
 
//#include "HdsLCD.h"
#include <string.h>

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

#define LCD_CHAR_A_GRAVE        ((char)0xC0)
#define LCD_CHAR_A_ACUTE        ((char)0xC1)
#define LCD_CHAR_A_CIRCUMFLEX   ((char)0xC2)
#define LCD_CHAR_A_TILDE        ((char)0xC3)
#define LCD_CHAR_C_CEDILLA      ((char)0xC7)
#define LCD_CHAR_E_ACUTE        ((char)0xC9)
#define LCD_CHAR_E_CIRCUMFLEX   ((char)0xCA)
#define LCD_CHAR_I_ACUTE        ((char)0xCD)
#define LCD_CHAR_N_TILDE        ((char)0xD1)
#define LCD_CHAR_O_ACUTE        ((char)0xD3)
#define LCD_CHAR_O_CIRCUMFLEX   ((char)0xD4)
#define LCD_CHAR_O_TILDE        ((char)0xD5)
#define LCD_CHAR_U_ACUTE        ((char)0xDA)
#define LCD_CHAR_U_DIAERESIS    ((char)0xDC)
#define LCD_CHAR_INVERTED_QMARK ((char)0xBF)
#define LCD_CHAR_INVERTED_EMARK ((char)0xA1)
#define LCD_CHAR_a_ACUTE        ((char)0xE1)
#define LCD_CHAR_a_TILDE        ((char)0xE3)
#define LCD_CHAR_c_CEDILLA      ((char)0xE7)
#define LCD_CHAR_e_ACUTE        ((char)0xE9)
#define LCD_CHAR_i_ACUTE        ((char)0xED)
#define LCD_CHAR_n_TILDE        ((char)0xF1)
#define LCD_CHAR_o_ACUTE        ((char)0xF3)
#define LCD_CHAR_o_TILDE        ((char)0xF5)
#define LCD_CHAR_u_ACUTE        ((char)0xFA)
#define LCD_CHAR_u_DIAERESIS    ((char)0xFC)


const char charAlarmDisabled[CHAR_HEIGHT] =  {               //�
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charAlarmReset[CHAR_HEIGHT] =  {               //�
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charNTilde[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charCCidille[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
};

const char charATilde[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charACirc[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charOTilde[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOCirc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charECirc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charEAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charAAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charAGrv[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charIAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charNUTilde[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charCUCidille[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
};

const char charAUTilde[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charAUCirc[CHAR_HEIGHT] =  {              //�
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charOUTilde[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charOUCirc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charEUCirc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charEUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
};

const char charAUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charAUGrv[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , _X_ , _X_ , _X_ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
};

const char charIUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
};

const char charUUAcc[CHAR_HEIGHT] =  {               //�
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charUUDieresis[CHAR_HEIGHT] =  {
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charuUDieresis[CHAR_HEIGHT] =  {
CONCAT(  _X_ , ___ , _X_ , ___ , _X_    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , ___ , _X_    )   ,
CONCAT(  _X_ , ___ , ___ , _X_ , _X_    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , _X_    )   ,
};

const char charInvertedQuestion[CHAR_HEIGHT] =  {
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , _X_ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , ___ , ___ , _X_ , ___    )   ,
CONCAT(  ___ , _X_ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
};

const char charInvertedExclamation[CHAR_HEIGHT] =  {
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , ___ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
CONCAT(  ___ , ___ , _X_ , ___ , ___    )   ,
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



const char charNumber[CHAR_HEIGHT] =  {              //n�
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



#define LCD_SPECIAL_CHAR_CAPACITY  24

unsigned char lcdCGRamCount = 0;
static uint8_t lcdCurrentLanguage = LCD_LANGUAGE_PORTUGUESE;

static const sSpecialChar lcdSpecialCharsPortuguese[] =
{
    { LCD_CHAR_A_TILDE      , (char *)&charATilde    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_O_TILDE      , (char *)&charOTilde    , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_C_CEDILLA    , (char *)&charCCidille  , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_A_ACUTE      , (char *)&charAAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_A_GRAVE      , (char *)&charAGrv      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_E_ACUTE      , (char *)&charEAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_I_ACUTE      , (char *)&charIAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_O_ACUTE      , (char *)&charOAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_A_CIRCUMFLEX , (char *)&charACirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_E_CIRCUMFLEX , (char *)&charECirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_O_CIRCUMFLEX , (char *)&charOCirc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_U_ACUTE      , (char *)&charUAcc      , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_a_TILDE      , (char *)&charAUTilde   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_o_TILDE      , (char *)&charOUTilde   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_c_CEDILLA    , (char *)&charCUCidille , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_a_ACUTE      , (char *)&charAUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_e_ACUTE      , (char *)&charEUAcc     , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED }
};

static const sSpecialChar lcdSpecialCharsSpanish[] =
{
    { LCD_CHAR_N_TILDE        , (char *)&charNTilde             , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_n_TILDE        , (char *)&charNUTilde            , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_A_ACUTE        , (char *)&charAAcc               , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_E_ACUTE        , (char *)&charEAcc               , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_I_ACUTE        , (char *)&charIAcc               , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_O_ACUTE        , (char *)&charOAcc               , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_U_ACUTE        , (char *)&charUAcc               , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_U_DIAERESIS    , (char *)&charUUDieresis         , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_a_ACUTE        , (char *)&charAUAcc              , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_e_ACUTE        , (char *)&charEUAcc              , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_i_ACUTE        , (char *)&charIUAcc              , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_o_ACUTE        , (char *)&charOUAcc              , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_u_ACUTE        , (char *)&charUUAcc              , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_u_DIAERESIS    , (char *)&charuUDieresis         , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_INVERTED_QMARK , (char *)&charInvertedQuestion   , CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED } ,
    { LCD_CHAR_INVERTED_EMARK , (char *)&charInvertedExclamation, CGRAM_NO_ADDR , SPECIAL_CHAR_UNUSED }
};

sSpecialChar lcdSpecialChars[LCD_SPECIAL_CHAR_CAPACITY];
unsigned int lcdSpecialCharCount = 0;
sSpecialChar * lcdUsedSpecialChars[ CGRAM_SIZE ];

static void LCD_CopyLanguageTable(const sSpecialChar *pTable, unsigned int uiCount, uint8_t ucLanguage)
{
    memset(lcdSpecialChars, 0, sizeof(lcdSpecialChars));
    memset(lcdUsedSpecialChars, 0, sizeof(lcdUsedSpecialChars));

    if (uiCount > LCD_SPECIAL_CHAR_CAPACITY)
    {
        uiCount = LCD_SPECIAL_CHAR_CAPACITY;
    }

    if (pTable != NULL && uiCount > 0)
    {
        memcpy(lcdSpecialChars, pTable, sizeof(sSpecialChar) * uiCount);
    }

    lcdSpecialCharCount = uiCount;
    lcdCGRamCount = 0;
    lcdCurrentLanguage = ucLanguage;
}

void LCD_SetLanguage(uint8_t ucLanguage)
{
    switch (ucLanguage)
    {
        case LCD_LANGUAGE_ENGLISH:
            LCD_CopyLanguageTable(NULL, 0U, LCD_LANGUAGE_ENGLISH);
            break;

        case LCD_LANGUAGE_SPANISH:
            LCD_CopyLanguageTable(lcdSpecialCharsSpanish,
                                  sizeof(lcdSpecialCharsSpanish) / sizeof(sSpecialChar),
                                  LCD_LANGUAGE_SPANISH);
            break;

        case LCD_LANGUAGE_PORTUGUESE:
        default:
            LCD_CopyLanguageTable(lcdSpecialCharsPortuguese,
                                  sizeof(lcdSpecialCharsPortuguese) / sizeof(sSpecialChar),
                                  LCD_LANGUAGE_PORTUGUESE);
            break;
    }
}

uint8_t LCD_GetLanguage(void)
{
    return lcdCurrentLanguage;
}

#endif
