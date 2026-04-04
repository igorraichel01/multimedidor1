/******************************************************************************
 *                                                                             *
 *   Programa......: DISPLAY.h                                                 *
 *   Versao........: 1.00                                                      *
 *   Data..........: 09/05/2005                                                *
 *   Atualizacao...: 14/05/2005                                                *
 *   Projeto.......: Terminal teclado + Display                                *
 *   Programador...: Laércio Oliveira                                          *
 *   Compilador....: Keil C51 7.06,7.08, 7.09                                  *
 *   Descricao.....: Funcao do display                                          *
 *******************************************************************************/
#ifndef _DISPLAY_
#define _DISPLAY_

#include "InventTypes.h"


#define ON  1
#define OFF 0

#define SIZE_8_BITS  0
#define SIZE_4_BITS 1

#define TIME_OUT_BUZY_FLAG   2   //MULTIPLO DE 100uS
#define  BF_BIT   0x80       				 	 // Busy flag
#define  DD_ADDR  0x80        				 // set DDRAM address
#define  CG_ADDR  0x40        				 // set CGRAM address
#define  LCD_LINE_LENGTH  0x000F			 // length of single line on lcd display

#define  CLEAR_HOME      	  0x01     	 // Clear display and HOME
#define  HOME                 0x02     // HOME
#define  DISP_MODE1           0x06     // Mode Set: Increment and not shift
#define  DISP_MODE2           0x07     // Mode Set: Increment and shift
#define  DISP_OFF             0x08     // Display Control: Disp OFF!
#define  CURSOR_OFF           0x0C     // Display Control: Disp ON, Cursor OFF, Blink OFF
#define  BLINK_ON             0x0D     // Display Control: Disp ON, Cursor OFF, Blink  ON
#define  CURSOR_ON            0x0E     // Display Control: Disp ON, Cursor  ON, Blink OFF
#define  CURSOR_BLINK_ON      0x0F     // Display Control: Disp ON, Cursor  ON, Blink  ON
#define  SHIFT_DISP_L         0x18     // Display Shift Left
#define  SHIFT_DISP_R         0x1C     // Display Shift Right
#define  FUNCTION_SET1        0x34     // Function Set: 8 bits, 1 line and 5x10 char
#define  FUNCTION_SET2        0x38     // Function Set: 8 bits, 2 lines and 5x7 char
#define NULLL  0

#define DELAY_DISPLAY  50 //20

//! Definição dos pinos

#define BUZY_CHECK_PORT GPIOA
#define BUZY_CHECK_BIT 6
#define BUZY_CHECK_IN()  BUZY_CHECK_PORT->IDR & (1<<BUZY_CHECK_BIT)


//#define DISPLAY_ON_PORT GPIOF
//#define DISPLAY_ON_BIT 1

#define DISPLAY_RS_PORT GPIOA
#define DISPLAY_RS_BIT 10

#define DISPLAY_RW_PORT GPIOA
#define DISPLAY_RW_BIT 9

#define DISPLAY_EN_PORT GPIOA
#define DISPLAY_EN_BIT 8

#define LCD_D4_PORT GPIOB
#define LCD_D4_BIT 12

#define LCD_D5_PORT GPIOB
#define LCD_D5_BIT 13

#define LCD_D6_PORT GPIOA
#define LCD_D6_BIT 14

#define LCD_D7_PORT GPIOA
#define LCD_D7_BIT 15


//#define LCD_ON_HIGH()	   DISPLAY_ON_PORT->BSRR = (1 << DISPLAY_ON_BIT) 
//#define LCD_ON_LOW()	   DISPLAY_ON_PORT->BRR = (1 << DISPLAY_ON_BIT) << 16U

#define LCD_RS_HIGH()	   DISPLAY_RS_PORT->BSRR = (1 << DISPLAY_RS_BIT) 
#define LCD_RS_LOW()	   DISPLAY_RS_PORT->BSRR = (1 << DISPLAY_RS_BIT) << 16U

#define LCD_RW_HIGH()	   DISPLAY_RW_PORT->BSRR = (1 << DISPLAY_RW_BIT) 
#define LCD_RW_LOW()	   DISPLAY_RW_PORT->BSRR = (1 << DISPLAY_RW_BIT) << 16U

#define LCD_EN_HIGH()	   DISPLAY_EN_PORT->BSRR = (1 << DISPLAY_EN_BIT) 
#define LCD_EN_LOW()	   DISPLAY_EN_PORT->BSRR = (1 << DISPLAY_EN_BIT) << 16U

				
#define LCD_D4_HIGH()	   LCD_D4_PORT->BSRR = (1 << LCD_D4_BIT) 
#define LCD_D4_LOW()	   LCD_D4_PORT->BSRR = (1 << LCD_D4_BIT)  << 16U 
#define LCD_D4_IN()        LCD_D4_PORT->IDR & (1<<LCD_D4_BIT)

#define LCD_D5_HIGH()	   LCD_D5_PORT->BSRR = (1 << LCD_D5_BIT) 
#define LCD_D5_LOW()	   LCD_D5_PORT->BSRR = (1 << LCD_D5_BIT) << 16U
#define LCD_D5_IN()        LCD_D5_PORT->IDR & (1<<LCD_D5_BIT)

#define LCD_D6_HIGH()	   LCD_D6_PORT->BSRR = (1 << LCD_D6_BIT) 
#define LCD_D6_LOW()	   LCD_D6_PORT->BSRR = (1 << LCD_D6_BIT) << 16U
#define LCD_D6_IN()      LCD_D6_PORT->IDR & (1<<LCD_D6_BIT)

#define LCD_D7_HIGH()	   LCD_D7_PORT->BSRR = (1 << LCD_D7_BIT) 
#define LCD_D7_LOW()	   LCD_D7_PORT->BSRR = (1 << LCD_D7_BIT) << 16U
#define LCD_D7_IN()      LCD_D7_PORT->IDR & (1<<LCD_D7_BIT)


enum MENSAGEM_DISPLAY_tag {
	MENSAGEM_IDLE, MENSAGEM_INICIO, MENSAGEM_DATA_HORA

};



class TDisplay
{
private:
void _delaylcd (unsigned int cnt);
void _LCD_WriteDado(char);
uint8 _ReadDado4b(void);
char _LCD_ReadDado(void);
void _LCD_WriteComando(char,bool);
void _WriteOutPut4b(uint8 dado);
	
public:	
void BusyCheck(void);
void CursorPos(unsigned char byPosicao);
void Init();
void PrintLCD(uint8 byPosicao, int8  *pDados,uint8 size);
void CursorBlock(uint8 estado);
void ClrScr(void);
void SetSpecial(void);
void SetF14(void);
void SetUserCG(char *data_ptr);
void LCD_WriteDado(char dado);
char LCD_ReadDado(void);
char LCD_ReadComando(void);
void LCD_HardwareReset(void);
bool DisplayNeedsInit(void);
bool IsDisplayFail(void);
void DecTimoutDisplay(void);

};


extern TDisplay Display;

#endif
