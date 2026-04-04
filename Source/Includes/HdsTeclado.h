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
 *******************************************************************************/

#ifndef _TECLADO_
#define _TECLADO_

#include "InventTypes.h"
#include "HdsGpio.h"

#define NUMLINHAS	4
#define NUMCOLUNAS	2

#define TEMPO_DEBOUNCE		2  //50ms

#define PRESSIONADA			TEMPO_DEBOUNCE+1    
#define NAOPRESSIONADA		0
#define AGUARDANOVOPRESS	TEMPO_DEBOUNCE+2

#define TEMPO_BUZZER_TECLADO  100

//! Definição dos pinos do telclado
#define COLUNA_1_PORT   GPIOB
#define COLUNA_1_BIT    GPIO_PIN_7
#define TEC_COLUNA_1 	COLUNA_1_PORT,COLUNA_1_BIT

#define COLUNA_2_PORT   GPIOB
#define COLUNA_2_BIT    GPIO_PIN_8
#define TEC_COLUNA_2 	COLUNA_2_PORT,COLUNA_2_BIT

//#define COLUNA_3_PORT   GPIOB
//#define COLUNA_3_BIT    GPIO_PIN_10
//#define TEC_COLUNA_3 	COLUNA_3_PORT,COLUNA_3_BIT
//
//#define COLUNA_4_PORT   GPIOB
//#define COLUNA_4_BIT    GPIO_PIN_9
//#define TEC_COLUNA_4 	COLUNA_4_PORT,COLUNA_4_BIT

#define LINHA_1_PORT    GPIOB
#define LINHA_1_BIT     GPIO_PIN_1
#define TEC_LINHA_1 	LINHA_1_PORT,LINHA_1_BIT


//#define LINHA_2_PORT    GPIOB
//#define LINHA_2_BIT     GPIO_PIN_2

//Hw Ricardo
#define LINHA_2_PORT    GPIOA
#define LINHA_2_BIT     GPIO_PIN_0


#define TEC_LINHA_2 	LINHA_2_PORT,LINHA_2_BIT

#define LINHA_3_PORT    GPIOB 
#define LINHA_3_BIT     GPIO_PIN_10
#define TEC_LINHA_3 	LINHA_3_PORT,LINHA_3_BIT

#define LINHA_4_PORT    GPIOB
#define LINHA_4_BIT     GPIO_PIN_9
#define TEC_LINHA_4 	LINHA_4_PORT,LINHA_4_BIT

#define COLUNA_1_HIGH()		Gpio.Write(TEC_COLUNA_1,ePortHigh);                   
#define COLUNA_1_LOW()		Gpio.Write(TEC_COLUNA_1,ePortLow); 

#define COLUNA_2_HIGH()		Gpio.Write(TEC_COLUNA_2,ePortHigh);                   
#define COLUNA_2_LOW()		Gpio.Write(TEC_COLUNA_2,ePortLow); 

//#define COLUNA_3_HIGH()		Gpio.Write(TEC_COLUNA_3,ePortHigh);                   
//#define COLUNA_3_LOW()		Gpio.Write(TEC_COLUNA_3,ePortLow); 
//
//#define COLUNA_4_HIGH()		Gpio.Write(TEC_COLUNA_4,ePortHigh);                   
//#define COLUNA_4_LOW()		Gpio.Write(TEC_COLUNA_4,ePortLow); 

#define LE_LINHA_1()   Gpio.Read (TEC_LINHA_1);
#define LE_LINHA_2()   Gpio.Read (TEC_LINHA_2);
#define LE_LINHA_3()   Gpio.Read (TEC_LINHA_3);
#define LE_LINHA_4()   Gpio.Read (TEC_LINHA_4);

typedef enum {
    KEY_NUM0_PRESSED = 1,
    KEY_NUM1_PRESSED,
    KEY_NUM2_PRESSED,
    KEY_NUM3_PRESSED,
    KEY_NUM4_PRESSED,
    KEY_NUM5_PRESSED,
    KEY_NUM6_PRESSED,
    KEY_NUM7_PRESSED,
    KEY_NUM8_PRESSED,
    KEY_NUM9_PRESSED,
    KEY_ENTER_PRESSED,
    KEY_ESC_PRESSED,
   // KEY_DATA_F1_DESL_PRESSED,
   // KEY_DATA_F2_DESL_PRESSED,
   // KEY_DATA_F3_DESL_PRESSED,
   // KEY_DATA_F4_DESL_PRESSED,
    KEY_NONE_PRESSED
} E_KEYS;

//linha coluna

//#define KEY_DATA_F1_DESL DebounceTeclado[3][3]
//#define	KEY_DATA_F2_DESL DebounceTeclado[2][3]
//#define	KEY_DATA_F3_DESL DebounceTeclado[1][3]
//#define	KEY_DATA_F4_DESL DebounceTeclado[0][3]

//#define	KEY_NUM9	DebounceTeclado[3][2]
//#define	KEY_NUM6	DebounceTeclado[2][2]
//#define	KEY_NUM3	DebounceTeclado[1][2]
//#define	KEY_ENTER	DebounceTeclado[0][2]

#define	KEY_NUM8    DebounceTeclado[3][1]
#define	KEY_NUM5   	DebounceTeclado[2][1]
#define	KEY_NUM2	DebounceTeclado[1][1]
#define	KEY_NUM0	DebounceTeclado[0][1]

#define	KEY_NUM7    DebounceTeclado[3][0]
#define	KEY_NUM4    DebounceTeclado[2][0]
#define	KEY_NUM1    DebounceTeclado[1][0]
#define	KEY_ESC     DebounceTeclado[0][0]

class TTeclado {
private:
    //! Deslita todas as colunas
    void _DesligaColunas(void);
    //! Aciona as colunas uma a uma
    void _AcionaColuna(unsigned char ColunaLogica);

public:
    void Init();
    void AnalisaTeclas(void);
    uint8 GetTecla(void);
    void ResetTecla(void);
    void TeclaReading(void);
    void ReadAgain(E_KEYS ETecla);

};

extern TTeclado Teclado;

#endif
