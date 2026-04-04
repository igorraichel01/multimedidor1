///////////////////////////////////////////////////////////////////////////
////                             KBD2.c                                ////
////                 Driver para modulo teclado 16 teclas (4x4)        ////
////         Define fun��es para identificar tecla pressionada e 	   ////
////                configura��es do teclado.						   ////	
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


************* instru��es de baixo n�vel *********************



************* Fun��es de alto n�vel ****************




*/

#include "KBD2.h"
#include "LCD.h"
#include "estados.h"
#include "Modo0.h"
#include "MdlSensor.h"

extern int IDIOMA;							// define o idioma 1-Port   2-Eng   3-Spa


// Keypad layout:
//char const KEYS[4][4] = {{'1','2','3','A'},
//                         {'4','5','6','B'},
//                         {'7','8','9','C'},
//                         {'*','0','#','D'}};


#define KBD_DEBOUNCE_FACTOR 25 		//  para validar a tecla pressionada
#define TEMPO_TECLA_REPETIDA 400		// 1 segundo para tecla repetida (400)

int16 temp_debounce=KBD_DEBOUNCE_FACTOR;
char temp_tecla_anterior;
int flagTeclado=0;
int16 flagEstado=0;
int16 iNextState=0;    //proximo estado da maquina de estados  

char tecla_valida;			// armazena tecla valida... apos debounce
uint16_t  passag=0;
uint16_t  passag2=0;


int numInt=1;							// numero intervalos 1->10

/*

    ---------------------------             ^
   |                           |            | (4)   
   |                           |  (5) <-          -> (6)
   |                           |            |
    ---------------------------             v (A)
      ----      ----       ----
      L_FUNC    M_FUNC    R_FUNC  
        (1)       (2)       (3)             
       

*/




//@@  #byte kbd = 0xF82

char kbd;

#define set_tris_kbd(x) set_tris_c(x)


#define COL0 (1 << 0)
#define COL1 (1 << 1)
#define COL2 (1 << 2)
#define COL3 (1 << 3)

#define LINHAS	 0xF0
#define ALL_PINS 0xFF


///////////////////////////////
// fun��o para os estados de 0 a 200

/*********************************************************************************************//**
 * \function        selecEstado
 * \details   Analisa a tecla recebida e retorna no novo estado casao seja uma das 3 teclas de fun��o 

 * \author     
 * \date         
 ************************************************************************************************/
int16 selecEstado(int16 estado, int _teclado){
    int16 uiRet=0;
    switch (_teclado) {
    case L_FUNC:
        //lcd_limpa();
        uiRet=(ESTADOS[estado][0]);
        break;

    case M_FUNC:
        uiRet=(ESTADOS[estado][1]);
        //lcd_limpa();
        break;

    case R_FUNC:
        uiRet=(ESTADOS[estado][2]);
        //	lcd_limpa();
        break;

    default:
        uiRet=(ESTADOS[estado][3]);
    }

    return uiRet;

}

///////////////////////////////////////


/// verifica a tecla e retorna o proxima sequencia

int16 selecEstado106(char _teclado){
    int16 iRet=0;

    switch (_teclado) {
    case L_FUNC:
        if (Func==FUNC_1){
            iRet=(110);
        }
        if (Func==2){
            iRet=(250);
        }
        if (Func==3){
            iRet=(350);
        }
        if (Func==4){
            iRet=(410);
        }
        if (Func==5){
            iRet=(550);
        }
        if (Func==6){
            iRet=(410);
        }
        if (Func==7){
            iRet=(710);
        }
        if (Func==8){
            iRet=(810);
        }
        if (Func==9){
            iRet=(950);
        }
        if (Func==10)
        {
            iRet=(350);
        }
        if (Func==12)
        {
            iRet=(250);
        }
        break;

    case M_FUNC:iRet=(100);
    break;

    case R_FUNC:
        iRet=(1);

        break;

    default:iRet=(106);
    }
    return iRet;
}


int16 selecEstado350(char _teclado){
    int16 iRet=0;

    switch (_teclado) {
    case L_FUNC:
        passag--;
        if(passag>numInt){
            passag=numInt-1;
        }
        iRet=(350);
        //@@		lcd_limpa();
        break;

    case M_FUNC:iRet=(106);
    //@@			lcd_limpa();
    break;


    case R_FUNC:
        passag++;
        if(passag>numInt-1){
            passag=0;
        }
        iRet=(350);
        //@@			lcd_limpa();
        break;

    default:iRet=(350);
    }
    return iRet;
}

int16 selecEstado450(char _teclado){
    int16 iRet=0;
    switch (_teclado) {
    case L_FUNC:
        passag--;
        if(passag>10){
            passag=9;
        }
        iRet=450;
        break;

    case M_FUNC:
        iRet=410;
        break;

    case R_FUNC:
        passag++;
        if(passag>9){
            passag=0;
        }
        iRet=450;
        break;

    default:
        iRet=450;
        break;
    }
    return iRet;
}

int16 selecEstado470(char _teclado){
    int16 iRet=0;
    switch (_teclado) {
    case L_FUNC:
        passag--;
        if(passag>10){
            passag=9;
        }
        iRet=(470);
        break;

    case M_FUNC:
        iRet=(410);
        break;


    case R_FUNC:
        passag++;
        if(passag>9){
            passag=0;
        }
        iRet=(470);
        break;

    default:
        iRet=(470);
        break;
    }
    return iRet;
}


int16 selecEstado750(char _teclado,int NumIntervalos){
    int16 iRet=0;
    switch (_teclado) {
    case L_FUNC:
        passag--;
        if(passag>NumIntervalos){
            passag=(NumIntervalos-1);
        }
        iRet=(750);
        break;

    case M_FUNC:
        iRet=(710);
        break;

    case R_FUNC:
        passag++;
        if(passag>(NumIntervalos-1)){
            passag=0;
        }
        iRet=(750);
        break;

    default:iRet=(750);
    }

    return (iRet);
}

int16 selecEstado751(char _teclado, int NumIntervalos){
    int16 iRet=0;
   
    int16 teste;

//!depende do n�mero de intervalos precisa fazer um tratamento diferente para cada tipo de tecla
    if(NumIntervalos==10)
        teste=NumIntervalos-1;
        else
        teste=NumIntervalos;


   switch (_teclado) {
    case L_FUNC:
        passag2--;
        if(passag2>NumIntervalos){
            passag=(NumIntervalos-1);
            iRet=(750);
        }
        else{
            iRet=(751);
        }
        break;

    case M_FUNC:
        iRet=(710);
        break;

    case R_FUNC:
        passag2++;
        if(passag2>(NumIntervalos-1)){
            passag=0;
            iRet=(750);

        }else{
            iRet=(751);}
        break;

    default:iRet=(751);
    }

    return (iRet);
}


int16 selecEstado770(char _teclado,int uiIntervalos){
    int16 iRet=0;
    int NumIntervalos=2;

    if(uiIntervalos==10)
          NumIntervalos= uiIntervalos;


    switch (_teclado) {
    case L_FUNC:
        passag2--;
        if(passag2>NumIntervalos){
            passag2=NumIntervalos-1;
        }
        iRet=(770);
        break;

    case M_FUNC:
        iRet=(710);
        break;

    case R_FUNC:
        passag2++;
        if(passag2>NumIntervalos-1){
            passag2=0;
        }
        iRet=(770);
        break;

    default:iRet=(770);
    }
    return iRet;
}

int16 selecEstado850(char _teclado,int NumIntervalos){
    int16 iRet=0;


    switch (_teclado) {
    case L_FUNC:
        passag--;
        if(passag>NumIntervalos){
            if(NumIntervalos==10){
                passag=NumIntervalos-1;
                passag2=NumIntervalos-1;
            }
            else{
                passag=0;
                passag2=1;
            }

            iRet=(851);
            break;
        }
        iRet=(850);
        break;

    case M_FUNC:
        iRet=(810);
        break;

    case R_FUNC:
        passag++;
        if(passag>NumIntervalos-1){
            passag=0;
            passag2=0;
            iRet=(851);
            break;

        }
        iRet=(850);
        break;

    default:iRet=(850);
    }
    return iRet;
}


int16 selecEstado851(char _teclado,int NumIntervalos){
    int16 iRet=0;

    switch (_teclado) {
    case L_FUNC:
        passag2--;
        
        if(NumIntervalos==10){
            if(passag2>NumIntervalos){
                passag2=NumIntervalos-1;
                iRet=(850);
            }
            else{
                iRet=(851);
            }
        }
        else{ //1 inervalo
            if(passag2>1){
                passag=0;
                iRet=(850);
            }
            else{
                iRet=(851);
            }
        }

        break;

    case M_FUNC:
        iRet=(810);
        break;

    case R_FUNC:
        passag2++;

        if(NumIntervalos==10){
            if(passag2>NumIntervalos-1){
                passag2=0;
                iRet=(850);
            }
            else{
                iRet=(851);
            }
        }
        else{
            if(passag2>1){
                passag=0;
                iRet=(850);
            }
            else{
                iRet=(851);
            }
        }
        break;

    default:iRet=(851);
    }
    return iRet;
}


int16 selecEstado870(char _teclado,int NumIntervalos){
    int16 iRet=0;
    int itest;     //Valor a ser testado
    int iReload;   //Valor da Recarga 

    if(NumIntervalos==10){
        itest= NumIntervalos-1;
        iReload=NumIntervalos-1;
       }
    else{
      itest= 1;
       iReload=1;
    }

    switch (_teclado) {
    case L_FUNC:
        passag2--;
        if(passag2>NumIntervalos){
            passag2=iReload;
        }
        iRet=(870);
        break;

    case M_FUNC:
        iRet=(810);
        break;

    case R_FUNC:
        passag2++;
        if(passag2>itest){
            passag2=0;

        }
        iRet=(870);
        break;

    default:iRet=(870);
    }
    return iRet;
}


int16 selecEstado990(char _teclado){
    IDIOMA=0;

    switch (_teclado) {
    case L_FUNC:
        IDIOMA=1; //portugues
        break;

    case M_FUNC:
        IDIOMA=2; //Ingles
        break;

    case R_FUNC:
        IDIOMA=3; //Espanhol
        break;

    default:
        break;

    }

    return(IDIOMA);

}
int verificaSetaV(char _teclado){
    int16 iRet=0;
    switch (_teclado) {

    case DESCE:
        iRet=(-1);
        break;

    case SOBE:
        iRet=(1);
        break;
    default:iRet=(0);

    }
    return iRet;
}

int verificaSetaH(char _teclado){
    int16 iRet=0;
    switch (_teclado) {

    case TECLA_ESQ:
        iRet=(-1);
        break;

    case TECLA_DIR:
        iRet=(1);
        break;

    default:iRet=(0);

    }
    return iRet;
}


