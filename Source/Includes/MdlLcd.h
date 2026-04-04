#ifndef _MDL_LCD_
#define _MDL_LCD_

#include "InventTypes.h"
#include <stdint.h>

#define LCD_LINHA_1 0
#define LCD_LINHA_2 1
 
#define LCD_NUM_COLUNAS  16
	
class C_Lcd{
private:
   uint8_t _screen[2][LCD_NUM_COLUNAS+1];      //!Espelho interno da tela do display
   uint8_t _ucLine;             //! linha a ser programada
   uint8_t _ucPosition;         //! posição a ser programada
   uint8_t _ucCursorPosition;   //! posição do cursor
   uint8    _bFlagCursorON;      //! Sinaliza cursor ON  
   

public:
 	 
   //! Inicialização das variaveis do módulo 
  void Init();
  void Update(void);
  void Write(uint32_t uwLine,char*pucLine); 
  void Add(char * pData);
  void Setxy(uint8 x, uint8 y);  //posiciona linha e coluna 

  void SetCursorOFF();
  void SetCursorOn();
  uint8 GetCursorState();
  void SetCursorPosition(uint8 ucPosicao, uint8_t ucLinha);
 
};

extern C_Lcd Lcd;
#endif 
