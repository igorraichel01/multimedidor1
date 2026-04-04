/******************************************************************************
 *                                                                             *
 *   Programa......: DISPLAY.C                                                 *
 *   Versao........: 1.00                                                      *
 *   Data..........: 09/05/2005                                                *
 *   Atualizacao...: 14/05/2005                                                *
 *   Projeto.......: Terminal teclado + Display                                *
 *   Programador...: Laércio Oliveira                                          *
 *   Compilador....: Keil C51 7.06,7.08, 7.09                                  *
 *   Descricao.....: Funcao do display                                          *
 *******************************************************************************/

#ifdef HIGH_LEVEL
#include <vcl.h>
#pragma hdrstop
#include "main_highLevel.h"
#include "HL_CursorBlink.h"

#endif
#include "InventTypes.h"
#include "Hdsdisplay.h"
#include <stdio.h>
#include <string.h>
#include "HdsGpio.h"
//#include "telas.h"
//#include "gpio.h"
//#include "rtc.h"
//#include "services.h"



TDisplay Display;

#ifdef HIGH_LEVEL
//AnsiString linha1,linha2;
uint8 linha1[17]=
{ '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
uint8 linha2[17]=
{ '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
#endif

#ifdef HIGH_LEVEL
//     FComThread = new TElsterComm(FHSerial, RxFunction, FRxSilence);
//  ThCursorBlink = new CursorBlink(true);
CursorBlink *ThCursorBlink;

#endif 

unsigned char EstadoDisplay;
static uint8 ucFalhaDisplay = true; //!< indica que houve falha na comunicação com o display
static uint8 ucFlagInicializaDisplay = false;

//static unsigned char Cursor_LCD;


const char PatternSpecial[] =
{0x00, 0x00, 0x0E, 0x10, 0x10, 0x12, 0x0E, 0x08,//ç
 0x05, 0x0A, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x00,//ã
 0x02, 0x04, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x00,//á
 0x02, 0x04, 0x11, 0x11, 0x11, 0x13, 0x0D, 0x00,//ú
 0x0E, 0x11, 0x10, 0x10, 0x10, 0x12, 0x0E, 0x08,//Ç
 0x05, 0x0A, 0x0E, 0x11, 0x1F, 0x11, 0x11, 0x00,//Ã
 0x02, 0x04, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00,//Ó
 0xff//-1
    };
const char PatternF14[] =
{0x1C, 0x10, 0x18, 0x12, 0x16, 0x02, 0x02, 0x07, //F1
 0x1C, 0x10, 0x18, 0x17, 0x11, 0x07, 0x04, 0x07, //F2
 0x1C, 0x10, 0x18, 0x17, 0x11, 0x03, 0x01, 0x07, //F3
 0x1C, 0x10, 0x18, 0x15, 0x15, 0x07, 0x01, 0x01, //F4
 0xff //-1
    };

void TDisplay::_delaylcd(unsigned int cnt)
{
  while (--cnt)
  {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

  }
  //Delay_uS(5);
}

/*
 Retorna se o display precis ser inicializado
 1 precisa
 0 não precisa
 */
bool TDisplay::DisplayNeedsInit(void)
{
  return ucFlagInicializaDisplay;

}

/*
 Retorna se o display esta em falha
 1 sim
 0 não
 */
bool TDisplay::IsDisplayFail(void)
{
  return ucFalhaDisplay;

}

#define TIMEOUT_BUZY   10

void TDisplay::BusyCheck(void)
{ // wait until BF is cleared
uint16 uiCont=0;

//if(!ucFlagInicializaDisplay)
	_delaylcd(3500);   //1000us
	/*
else{
	
do{
if (LCD_D7_IN())
  _delaylcd(350);   //100us
 else
	 break;
	
}while(++uiCont<35);
}
	*/ 
}

// Posiciona cursor na posicao recebida como parametro (R7)
void TDisplay::CursorPos(unsigned char byPosicao)
{

#ifdef HIGH_LEVEL
  uint8 caracter;
  //pega o caracter
  if( byPosicao>=16)
  ThCursorBlink->SetPosition(byPosicao,linha2[byPosicao-16]);
  else
  ThCursorBlink->SetPosition(byPosicao,linha1[byPosicao]);

#else

  BusyCheck();

  //LCD_reg.LCD_CMD_WR = CURSOR_OFF;
  _LCD_WriteComando(CURSOR_OFF,SIZE_4_BITS);

  BusyCheck();
  if (byPosicao <= 15)
  { //Primeira linha
    //LCD_reg.LCD_CMD_WR = ( byPosicao | 0x80);		//Posiciona o display no local desejado
    _LCD_WriteComando(byPosicao | 0x80,SIZE_4_BITS);
  }
  else
  { //Segunda linha
    //LCD_reg.LCD_CMD_WR = ( (byPosicao & 0x0f) | 0xc0 );
    _LCD_WriteComando((byPosicao & 0x0f) | 0xc0,SIZE_4_BITS);
  }

#endif
}
/*


 MODER Modo de operação: 0: Entrada, 1: Saída, 2: Alternativo, 3: Analógico

 MODERy[1:0]: Port x configuration bits (y = 0..15)
 These bits are written by software to configure the I/O mode.
 00: Input mode (reset state)
 01: General purpose output mode
 10: Alternate function mode
 11: Analog mode


 OTYPE Tipo de saída: 0: Push-pull, 1: Open drain

 OSPEED Frequencia de relógio do módulo (Ver Tabela 60 do Datasheet [4])


 PUPD Ativa-se Pull-up ou Pull Down ou nenhum dos dois
 These bits are written by software to configure the I/O pull-up or pull-down
 00: No pull-up, pull-down
 01: Pull-up
 10: Pull-down
 11: Reserved

 */
void TDisplay::Init()
 {

    //Váriáveis de controle de Erro no display
    ucFalhaDisplay = false;

    //Pinos de controle
    Gpio.GpioCfg(LcdRs, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdRw, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdEnable, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
//    Gpio.GpioCfg(LcdOn, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);

    Gpio.GpioCfg(LcdD4, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdD5, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdD6, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);
    Gpio.GpioCfg(LcdD7, NONE_RESISTOR, eGPIOOutput, PORT_PUSH_PULL, PORT_LOW_SPEED);

    //Delsiga o display
//    LCD_ON_HIGH();
//    _delaylcd(25 * 3500);  //50ms antes de qualquer comando

    //Liga o display
//    LCD_ON_LOW();
    _delaylcd(50 * 3500);  //50ms antes de qualquer comando

    LCD_RS_HIGH();
    LCD_RW_HIGH();
    LCD_EN_LOW();
    _delaylcd(1 * 3500);

    //! Envia sequencia de bytes em 8 bits para configurar para 4 bits
    _LCD_WriteComando(0x30, SIZE_8_BITS);
    _delaylcd(1 * 3500);
    _LCD_WriteComando(0x30, SIZE_8_BITS);
    _delaylcd(1 * 3500);
    _LCD_WriteComando(0x30, SIZE_8_BITS);
    _delaylcd(1 * 3500);
    _LCD_WriteComando(0x20, SIZE_8_BITS);
    _delaylcd(1 * 3500); //configura para 4 bits

    //Esta em 4 bits, configura o numero de linhas e a fonte
    _LCD_WriteComando(0x28, SIZE_4_BITS);
    _delaylcd(2 * 3500); //3500 = 1ms

    ucFlagInicializaDisplay = true;   //!< display inicializado

//Escreve e le no Display
    BusyCheck();
     LCD_WriteDado('A'); //Escreve no display

    CursorPos(0);
    BusyCheck();
    //	if (LCD_ReadDado() == 'A')	{
    //			printf("leu A");
    //			}

    BusyCheck();
    _LCD_WriteComando(0x01, SIZE_4_BITS);
    _delaylcd(1000); //Clear display
    BusyCheck();

    _LCD_WriteComando(0x02, SIZE_4_BITS);
    _delaylcd(1000); //Cursor home

    SetSpecial();

    ClrScr();

}

/*****************************************************************************
 ** Function name:	void PrintLCD(unsigned char byPosicao, unsigned char  *pDados,uint8 size){
 **
 ** Descriptions:
 Mostra no lcd os dados envidos,


 **
 **
 ** parameters:posicao de inicio         0 primeira posicao linha 1
 16 primeira posicao linha 2
 ** 			  ponteiro com os dados
 ** 			  numero de dados
 **
 ** Returned value:	None
 **
 *****************************************************************************/
void TDisplay::PrintLCD(uint8 byPosicao, int8 *pDados, uint8 size)
{
  char temp;

  CursorPos(byPosicao);

  do
  {
    temp = *pDados++;

    //analsa se é caracter especial
    if (temp == 'ç')
      temp = 0x01;
    else if (temp == 'ã')
      temp = 0x02;
    else if (temp == 'á')
      temp = 0x03;
    else if (temp == 'é')
      temp = 0x04;
    else if (temp == 'Ç')
      temp = 0x05;
    else if (temp == 'Ã')
      temp = 0x06;
    else if (temp == 'Ó')
      temp = 0x07;
    else
    {
    }

    BusyCheck();
    LCD_WriteDado(temp); //Escreve no display
  } while (--size > 0);

}

// Prepara cursor de edicao
void TDisplay::CursorBlock(uint8 estado)
{
  BusyCheck();

  if (estado == ON)
    _LCD_WriteComando(CURSOR_ON,SIZE_4_BITS /*BLINK_ON*/);
  else
    _LCD_WriteComando(CURSOR_OFF,SIZE_4_BITS);
}

//  Limpa Display
void TDisplay::ClrScr(void)
{
  PrintLCD(0, (int8 *) "                ", 16);
  PrintLCD(16, (int8 *) "                ", 16);

}

void TDisplay::SetSpecial(void)
{
  SetUserCG((char *) &PatternSpecial);
}
void TDisplay::SetF14(void)
{
  SetUserCG((char *) &PatternF14);
}

void TDisplay::SetUserCG(char *data_ptr)
{ // Inicializa  pattern especial

  BusyCheck();
  _LCD_WriteComando(CG_ADDR | (8 * 1),SIZE_4_BITS); //from character code 1

  //while (*data_ptr != (char)-1) {
  while (*data_ptr != 0xFF)
  {
    BusyCheck();
    LCD_WriteDado(*data_ptr++);
  }
}

/****************************************************************************
 * void WriteOutPut(uint8 dado)
 * 	Atualiza os pinos de saida do display 4 bits. pega os 4 
 * bytes mais significativos
 *
 ******************************************************************************/
void TDisplay::_WriteOutPut4b(uint8 dado)
{

  if (dado & BIT4)
  {
    LCD_D4_HIGH();
  }
  else
  {
    LCD_D4_LOW();
  }


  if (dado & BIT5)
  {
    LCD_D5_HIGH();
  }
  else
  {
    LCD_D5_LOW();
  }


  if (dado & BIT6)
  {
    LCD_D6_HIGH();
  }
  else
  {
    LCD_D6_LOW();
  }


  if (dado & BIT7)
  {
    LCD_D7_HIGH();
  }
  else
  {
    LCD_D7_LOW();
  }

  //! ciclo no enable
  LCD_EN_HIGH();
  _delaylcd(DELAY_DISPLAY);

  LCD_EN_LOW();
  _delaylcd(DELAY_DISPLAY); //para teste o dado e validado em nivel baixo
}

/****************************************************************************
 //RS=1 dado =0 comando
 //RW= 1 le display =0 Escreve display
 //E=1; Habilita display
 //
 ******************************************************************************/
void TDisplay::LCD_WriteDado(char dado)
{
  //! se display em falha, retorna
  if (ucFalhaDisplay)
    return;

  LCD_RS_HIGH();
  LCD_RW_LOW();

  //! parte alta
  _WriteOutPut4b(dado);
  //! parte baixa
  _WriteOutPut4b(dado << 4);

}

/****************************************************************************
 * void _ReadDado4b(uint8 dado)
 * 	Le os 4 bits mais significativos
 * 
 *
 ******************************************************************************/
uint8 TDisplay::_ReadDado4b(void)
{
  uint8 ucbyteIn = 0;

  //! ciclo no enable
  LCD_EN_HIGH();
  _delaylcd(DELAY_DISPLAY);

  //! se o bit estiver em 1 aciona seta um no byte de retorno
  if (LCD_D4_IN())
    ucbyteIn |= BIT4;

  if (LCD_D5_IN())
    ucbyteIn |= BIT5;

  if (LCD_D6_IN())
    ucbyteIn |= BIT6;

  if (LCD_D7_IN())
    ucbyteIn |= BIT7;

  LCD_EN_LOW();

  return ucbyteIn;

}

/****************************************************************************
 char LCD_ReadDado()
 //RS=1 dado =0 comando
 //RW= 1 le display =0 Escreve display
 //E=1; Habilita display
 //
 ******************************************************************************/
char TDisplay::LCD_ReadDado()
{

  uint8 ucDado = 0;

  LCD_RS_HIGH();
  LCD_RW_HIGH();
  _delaylcd(DELAY_DISPLAY);

  ucDado = _ReadDado4b();
  ucDado |= (_ReadDado4b() >> 4);

  return ucDado;

}

/*
Envia o comando de 4 ou 8 bits
*/
void TDisplay::_LCD_WriteComando(char dado, bool b4bits)
{
  //! se display em falha, retorna
  if (ucFalhaDisplay)
    return;

  LCD_RS_LOW();
  LCD_RW_LOW();
  //! parte Alta
  _WriteOutPut4b(dado);
 
	if(b4bits){
	//! parte baixa
  _WriteOutPut4b(dado << 4);
	}
	
}

