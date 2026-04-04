/*
 //////////////////////////////////////////////////////////////////////////
 CRONOMETRO MULTIFUNCIONAL - EQ228E -

 Versão do software: 1.0
 10/02/2012
 Versão do software: 1.1
 03/08/2012
 Incluido a funcao F12 - energia cinetica
 07/10/2013
 Alterado mensagens (MSG.h) conforme descricao abaixo:
 ->“F1   2ou5 sens” deve ser alterada para “F1   2 a 5 sens”
 ->“F1  2 or 5 sens”  deve ser alterada para “F1   2 to 5 sens”
 ->“F1   2 o 5 sens”   deve ser alterada para “F1   2 a 5 sens”
 Fabio - 07/10/2013


 Autor: Pablo A. Spiller
 Co-Autor : Fabio de A. Bairros

 //////////////////////////////////////////////////////////////////////////
 */
#include "InventTypes.h"
#include "MdlMSG.h"
#include "Modo0.h"
#include "LCD.h"
#include "KBD2.h"
#include "MdlSensor.h"
#include "sensores.h"

int Func = 0;

extern int numInt;
extern int16 flagEstado;
extern float fTimeruS;

extern int numIntervalosF7;

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2

float ftmp;
char portab;
char *PORTB;

//caso ocorram outras interrupcoes
//@@ #int_default
void isr_default() {

}


void startTimer() {
//@@ 	setup_timer_1(T1_INTERNAL | T1_DIV_BY_1 );
//@@	set_timer1(65284);
//@@	enable_interrupts(INT_TIMER1);
    timeCounter = 0;
    timeCounter2 = 0;
    sensor0 = 1;
    sensor1 = 16;
    sensor2 = 64;
    sensor3 = 128;
    sensor4 = 32;
    fTimeruS=0;
//@@	bit_clear(*INTCON,1);		

}

void stopTimer() {
//@@	tempoTotal=timeCounter;
    tempoTotal2 = timeCounter2;
//@@	disable_interrupts(INT_TIMER1);
//@@	setup_timer_1(T1_DISABLED);
//@@	sensores_desab();
}

void modo0_zera_valores() {
    SensorDigital.Init();

    //	Larg=0;
    timeCounter2 = 0;
    timeCounter = 0;
    tempoTotal = 0;
    tempoTotal2 = 0;
    flagMostraVel = 0;
    flagFimS0 = 0;
    flagFimS1 = 0;
    numInt = 1;
}








///////////////////////  SENSORES /////////////////////////
// interrupcao pela portaB <B4-B7>
// B4-B7 -> sensores S1 a S4
// interrupcao gerada pela acao de um sensor 
// armazena valor da porta do teclado e zera flag

//@@ #INT_RB
void int_sensores() {

    //	int portab;
    //??	portab=*PORTB;
    if (Func == 9) {
        if (sensor == 1) {
            if (portab & sensor1) {
                sensor = 0;
                SensorDigital.Result.tempos[0] = timeCounter;
                SensorDigital.Result.tempos2[0] = timeCounter2;

                //!  também calcula os valores da Func9
                SensorDigital.CalcFunc2();
            }
        }
    } else if (Func == 1) {
        if (portab & sensor1) {
            sensor = 1;
            SensorDigital.Result.tempos[0] = timeCounter;
            SensorDigital.Result.tempos2[0] = timeCounter2;
            sensor1 = 0;
        } else if (portab & sensor2) {
            sensor = 2;
            SensorDigital.Result.tempos[1] = timeCounter;
            SensorDigital.Result.tempos2[1] = timeCounter2;
            sensor2 = 0;
        } else if (portab & sensor3) {
            sensor = 3;
            SensorDigital.Result.tempos[2] = timeCounter;
            SensorDigital.Result.tempos2[2] = timeCounter2;
            sensor3 = 0;
        } else if (portab & sensor4) {
            sensor = 4;
            SensorDigital.Result.tempos[3] = timeCounter;
            SensorDigital.Result.tempos2[3] = timeCounter2;
            sensor4 = 0;
        }
    } else if (Func == 7) {
        if (flagEstado == 703 ) {
            if (portab & sensor1) {
                SensorDigital.Result.S1tempos[passag2] = (int32) timeCounter;
                SensorDigital.Result.S1tempos2[passag2] = timeCounter2;
                passag2++;
                if (passag2 == numIntervalosF7) {
                    //@@						disable_interrupts(INT_RB);
                    flagFimS1 = 1;
                    if(numIntervalosF7==2){
                        numIntervalosF7=1;
                    }
                    SensorDigital.CalcFunc_3467810();
                }
            }
        }
    }
    else if (Func == 8) {
        if ( flagEstado == 803 & !flagFimS1 ) {
            if (portab & sensor1) {
                SensorDigital.Result.S1tempos[passag2] = (int32) timeCounter;
                SensorDigital.Result.S1tempos2[passag2] = timeCounter2;
                passag2++;
                if (passag2 == numIntervalosF7) {
                    //@@						disable_interrupts(INT_RB);
                    flagFimS1 = 1;
                    SensorDigital.CalcFunc_3467810();
                }
            }
        }
    }

    //@@		bit_clear(*INTCON,0);			//clear_interrupt(INT_RB);

}





// interrupcao pela INT externa <RB0>  
// B0 -> sensores S0 ou Bobina
// interrupcao gerada pela acao de um sensor 
// armazena valor da porta do teclado e zera flag
// parametro estado 1 borda descida 0 borda subida 
//@@	 #INT_EXT
void int_sensorS0(bool bBorda) {

    switch (flagEstado) {

    case 100:
        if (Func == 9) {
            startTimer();
            msg_zeraTimer();
            sensor = 1;
            flagEstado = 101;
            
            EstadoModo1(flagEstado);

        } else {
            startTimer();
            sensor = 0;
            msg_zeraTimer();
            if (Func == 3) {
                timeCounter = 700;
            }
            flagEstado = 101;
            passag = 0;
            passag2 = 0;
            despresa = 0;
            flagFimS0 = 0;
            flagFimS1 = 0;
            Gpio.Write( Led,ePortHigh);

            EstadoModo1(flagEstado);

        }

        break;

    case 202:
        if (Func == 2) {
            //borda de descida do sensor em F2
            stopTimer();
            SensorDigital.Result.tempos[0] = timeCounter;
            SensorDigital.Result.tempos2[0] = timeCounter2;
            ftmp=fTimeruS/1000;
            flagEstado = 106;
            SensorDigital.CalcFunc2();
        }

        if (Func == 12) {
            //borda de descida do sensor em F12
            stopTimer();
            SensorDigital.Result.tempos[0] = timeCounter;
            SensorDigital.Result.tempos2[0] = timeCounter2;
            flagEstado = 106;
            SensorDigital.CalcFunc5_12();        
        }
        break;

    case 302:
        //Só considera a borda de descida do sensor 
        if (!bBorda) {
            SensorDigital.Result.tempos[passag] = (int32) timeCounter;
            SensorDigital.Result.tempos2[passag] = timeCounter2;
            passag++;
            if (Func == 6) {
                timeCounter = 0;
                timeCounter2 = 0;
            }
            if (passag == numInt) {
                //??				sensores_desab();
                stopTimer();
                flagEstado = 106;
                //! usa a função 3 e 6
                SensorDigital.CalcFunc_3467810();
            }
        }

        break;

    case 402:
        if (!bBorda) {

            if (despresa == 1) {
                SensorDigital.Result.tempos[passag] = (int32) timeCounter;
                SensorDigital.Result.tempos2[passag] = timeCounter2;
                passag++;
                timeCounter = 0;
                timeCounter2 = 0;
                if (passag == 10) {
                    //??					sensores_desab();
                    stopTimer();
                    flagEstado = 106;
                    //funcao  
                    SensorDigital.CalcFunc_3467810();
                }
                despresa = 0;
            }
            else {
                despresa = 1;
            }
        }
        break;

    case 503:
        SensorDigital.Result.tempos[0] = timeCounter;
        SensorDigital.Result.tempos2[0] = timeCounter2;
        stopTimer();
        //Modo=2;
        flagEstado = 504;
        break;

    case 702:
        if (!bBorda) {
            SensorDigital.Result.tempos[passag] = (int32) timeCounter;
            SensorDigital.Result.tempos2[passag] = timeCounter2;
            passag++;
            if (passag == numIntervalosF7) {
                if(numIntervalosF7==1){
                    numIntervalosF7=2;
                    passag2 = 0;
                }
                else{
                    passag2 = 0;
                    passag = 0;
                }
                flagEstado = 703;
                flagFimS0 = 1;
            }
        }
        break;

    case 802:
        if (!bBorda) {
            SensorDigital.Result.tempos[passag] = (int32) timeCounter;
            SensorDigital.Result.tempos2[passag] = timeCounter2;
            passag++;
            if (passag >= numIntervalosF7) {
                if(numIntervalosF7==1)
                    numIntervalosF7=2;

                passag2 = 0;
                passag = 0;
                flagEstado = 803;
            }
        }
        break;



    case 803:
        if (!bBorda) {
            SensorDigital.Result.S0vtempos[passag] = (int32) timeCounter;
            SensorDigital.Result.S0vtempos2[passag] = timeCounter2;
            passag++;
            if (passag == numIntervalosF7) {
                if (numIntervalosF7==1){
                    numIntervalosF7=2;
                }
                else{
                    //@@							disable_interrupts(INT_EXT);
                    flagFimS0 = 1;
                    //! funcao 8
                    SensorDigital.CalcFunc_3467810();
                }
            }
        }

        break;

    }    

}

extern float fTimeruS;
///////////////////////////////////////////////////////////////
//             
// Função chamada a cada 50us
//	cronometragem de eventos dos sensores
// incrementa timeCounter2 a cada 1ms

//@@	 #int_timer1                     
void clock1_isr() {

    //@@		set_timer1(65284);		/// 50us
    //set_timer1(65000);
    if (timeCounter == 10000)    //? base de tempo de 10ms
    {
        timeCounter = 0;
        timeCounter2++;
        // Gpio.Toggle(Led);

    }
    timeCounter+=5;
    fTimeruS+=50;
}

//----------------------------------FIM INTERRUPCAO-----------------------------------

