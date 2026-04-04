#ifndef __kBD2__
#define __kBD2__

#include "HdsTeclado.h"

///////////////////////////////////////////////////////////////////////////
////                             KBD2.h                                ////
////                 Driver para modulo teclado 16 teclas (4x4)        ////
////         Define funções para identificar tecla pressionada e 	   ////
////                configurações do teclado.						   ////	
///////////////////////////////////////////////////////////////////////////  
/*
************* Pinagem****************
      PIC  teclado
//     RC0	C0
//     RC1	C1
//     RC2	C2
//     RC3	C3  	
//     RC4	L0
//     RC5	L1
//     RC6  L2
//	   RC7	L3	

//   C0-C3 sao utilizados como coluna da matriz
//	e sao ativados por software para detectar qual linha foi pressionada
//   L0-L3 sao utilizados como linhas da matriz
//	e por serem configurados como entrada, serao ativados quando pressionada
//	alguma tecla


*****************    ATENCAO !   ********************
*  utiliza TIMER0 para gerar a varredura do teclado *
*****************************************************


************* instruções de baixo nível *********************



************* Funções de alto nível ****************




*/

#include "InventTypes.h"

extern int IDIOMA;							// define o idioma 1-Port   2-Eng   3-Spa



#define KBD_DEBOUNCE_FACTOR 25 		//  para validar a tecla pressionada
#define TEMPO_TECLA_REPETIDA 400		// 1 segundo para tecla repetida (400)


//#define L_FUNC 	KEY_ESC_PRESSED 
//#define M_FUNC 	KEY_NUM1_PRESSED 
//#define R_FUNC 	KEY_NUM4_PRESSED 
//#define DESCE	KEY_NUM7_PRESSED
//#define SOBE	KEY_NUM0_PRESSED
//#define TECLA_DIR		KEY_NUM5_PRESSED 
//#define TECLA_ESQ		KEY_NUM2_PRESSED 
//#define RESET	KEY_NUM8_PRESSED  


#define L_FUNC 	    KEY_NUM0_PRESSED  //!Linha 0 coluna 1
#define SOBE	    KEY_ESC_PRESSED    //!Linha 0 coluna 0
#define M_FUNC 	    KEY_NUM2_PRESSED  //!Linha 1 coluna 1
#define TECLA_ESQ	KEY_NUM1_PRESSED    //!Linha 1 coluna 0
#define R_FUNC 	    KEY_NUM5_PRESSED    //!Linha 2 coluna 1
#define TECLA_DIR	KEY_NUM4_PRESSED    //!Linha 2 coluna 0
#define DESCE	    KEY_NUM8_PRESSED    //!Linha 3 coluna 1
#define RESET	    KEY_NUM7_PRESSED    //!Linha 3 coluna 0



#define use_portc_kbd TRUE


#define set_tris_kbd(x) set_tris_c(x)


#define COL0 (1 << 0)
#define COL1 (1 << 1)
#define COL2 (1 << 2)
#define COL3 (1 << 3)

#define LINHAS	 0xF0
#define ALL_PINS 0xFF








///////////////////////////////
// função para os estados de 0 a 200

int16 selecEstado(int16 estado, int _teclado);

///////////////////////////////////////


/// verifica a tecla e retorna o proxima sequencia

int16 selecEstado106(char _teclado);

int16 selecEstado350(char _teclado);
int16 selecEstado450(char _teclado);

int16 selecEstado470(char _teclado);


int16 selecEstado750(char _teclado,int NumIntervalos);
int16 selecEstado751(char _teclado,int NumIntervalos);
int16 selecEstado770(char _teclado,int NumIntervalos);

int16 selecEstado850(char _teclado,int NumIntervalos);
int16 selecEstado851(char _teclado,int NumIntervalos);
int16 selecEstado870(char _teclado,int NumIntervalos);


int16 selecEstado990(char _teclado);
int verificaSetaV(char _teclado);

int verificaSetaH(char _teclado);



extern  int16 temp_debounce;
extern char temp_tecla_anterior;
extern int flagTeclado;
extern int16 flagEstado;
extern int16 iNextState;
extern char tecla_valida;			// armazena tecla valida... apos debounce
extern uint16_t   passag;
extern uint16_t  passag2;
extern int Func;
extern int numInt;

#endif

