///////////////////////////////////////////////////////////////////////////
////                             LCD.H                                 ////
////                 Driver para modulo LCD ITM1602                    ////
////         Define funções para inicializar, movimentar,              ////
////                escrever e ler caracteres.						   ////	
///////////////////////////////////////////////////////////////////////////  


#ifndef __LCD__
#define __LCD__

#include "InventTypes.h"



///////////////////// instruções de baixo nível


void lcd_send_nibble( BYTE n ); 

void lcd_send_byte( BYTE address, BYTE n );

/////////////////////////////FUNÇÕES//////////////////////////////


////////////// inicializa LCD //////////////////////////
void lcd_init(void);
/////////////// posiciona cursor //////////////////////
void lcd_posicaoxy( BYTE x, BYTE y);
int lcd_getdigito( BYTE x, BYTE y); 
/////////// esreve uma linha //////////////////
void lcd_escreve( char *c); 
///////////limpa LCD///////////////////
void lcd_limpa(void);           
/////////// posiciona na linha 2///////////////////
void lcd_linha2(void);          
/////////// posiciona na linha 1///////////////////
void lcd_linha1(void);          
/////////// escreve um dígito de tempo ///////////////////
void lcd_escreve_digito(int digito);          
long lcd_getDistancia(void);
//Funcao especifica para receber o valor de massa - F12 - Energia cinetica
long lcd_getMassa(void);
void lcd_escreve_Dist(long dist);;
void lcd_escreve_Massa(long massa);
long lcd_getInt(void);
void lcd_escreve_Int(long interv);
void lcd_escreve_tempo(int32 tempo, int32 tempo2);
void lcd_escreve_tempo2(float ftempo);

void lcd_escreve_veloc(float veloc);
int lcd_desloca_H(int posCursor, int _setaH);
int lcd_desloca_H2(int posCursor, int _setaH);
int lcd_desloca_H_massa(int posCursor, int _setaH);
void lcd_atualiza_Dist(unsigned int _setaV, int posCursor);
void lcd_atualiza_Massa(unsigned int _setaV, int posCursor);
void lcd_cursorBlack(int _posCursor);

#endif 

