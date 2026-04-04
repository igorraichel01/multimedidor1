
#ifndef __SENSORES__
#define __SENSORES__

/*
// Configura as portas e as interrupcoes dos sensores e bobina
// funcoes de identificacao de sensores

void sensores_init()		inicializa os sensores S0-S4
	
void bobina_init()			inicializa a bobina e sensor S4

*/

#define INTCON 0xff2

void sensores_init(void);

void sensores_desab(void);

#endif


