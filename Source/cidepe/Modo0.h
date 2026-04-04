
#ifndef __MODO_0__
#define __MODO_0__

#include "InventTypes.h"


#define CURSOR_INC 100				// tempo pisca-pisca: 50 longo - 300 curto
#define CURSOR_BLACK 25000			// tempo com cursor black: 20000 longo - 40000 curto





#define STATE_INICIA_EXPERIMENTO  100


#define STATE_SAVE_USB  1000
#define STATE_SHOW_SAVING_RESULT 1001
#define STATE_REPETIR_SAIR  1002
#define STATE_WAIT_PEN_DRIVE 1003
#define  STATE_SAVE_AT_PEN_DRIVE 1004
#define  STATE_ASK_SAVE_AT_PEN_DRIVE 1005



//extern long Larg;
extern long massa;
 //long energia;
extern int posCursor;
extern int sensor;
extern int Modo;		
extern int despresa;
extern int sensor0;
extern int sensor1;
extern int sensor2;
extern int sensor3;
extern int sensor4;
extern uint32 timeCounter2;		// a cada 10000 timeCounter incrementa
extern uint32 timeCounter;
extern uint32 tempoTotal;
extern uint32 tempoTotal2;
extern uint16 black;
extern int flagFimS0;						// flag 1 quando encerra os choques
extern int flagFimS1;						// flag 1 quando encerra os choques
extern int numSensores;						// 2 ou 5
extern int flagMostraVel;						//flag  1->mostra vel   0->mostra somente tempos
extern int flag_funcao_5;




//extern uint32 SensorDigital.Result.tempos[11];

//extern uint32 tempos2[11];

//extern uint32 S1tempos[11];
//extern uint32 S1tempos2[11];

//extern uint32 SensorDigital.Result.S0vtempos[11];
//extern uint32 SensorDigital.Result.S0vtempos2[[11];





bool EstadoModo0(int16 _flagEstado);
bool EstadoModo1(int16 _flagEstado);



void modo2_escreveTempo_1(int16 passagem);
void modo2_escreveFreq_1(int16 passagem);
bool EstadoModo2(int16 _flagEstado);



#endif


