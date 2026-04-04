#include "InventTypes.h"
#include "lcd.h"
#include "KBD2.h"
#include "Mdlmsg.h"
#include "Modo0.h"
#include "MdlLcd.h"
#include "sensores.h"
#include "MdlSensor.h"
#include "HdsMux.h"
#include "File_Handling.h"
#include <stdio.h>
#include <string.h>
#include "MdlSaveDigital.h"

extern int16 flagEstado;

extern void startTimer(void);
extern void stopTimer(void);
extern void modo0_zera_valores(void);

//long Larg=0;
//long massa = 0;
//long energia=0;
int posCursor = 8;
int sensor;
int Modo;
int despresa;
int sensor0;
int sensor1;
int sensor2;
int sensor3;
int sensor4;
uint32 timeCounter2;		// a cada 10000 timeCounter incrementa
uint32 timeCounter;
uint32 tempoTotal;
uint32 tempoTotal2;
uint16 black;
int flagFimS0 = 0;						// flag 1 quando encerra os choques
int flagFimS1 = 0;						// flag 1 quando encerra os choques
int numSensores;						// 2 ou 5
int flagMostraVel = 0;			//flag  1->mostra vel   0->mostra somente tempos
int flag_funcao_5 = 0;					//Flag usado para indicar a funcao 5

int numIntervalosF7;

#define CURSOR_INC 100				// tempo pisca-pisca: 50 longo - 300 curto
#define CURSOR_BLACK 25000			// tempo com cursor black: 20000 longo - 40000 curto

#define POSICAO_CURSOR 5

#define PORTB 0xf81
extern char portab;





//MODO 2

//Resultado do Ensaio


uint32 aux_tempo;
uint32 aux_tempo2;





/*

 Retorna 1 se houve troca de estado

 */

bool EstadoModo0(int16 _flagEstado) {

    bool bret;

    //!   int setaH, setaV;

    switch (_flagEstado) {
    case 0:
        tela0();
        numSensores = 5;
        flagEstado = selecEstado(0, tecla_valida);// verifica tecla "funcao" ou "ajuda"
        
        //Caso a escolha seja a tela ajuda  para iniciar mosrar a tela 
        MuxTimers.SetMsDelay(10);
        break;

    case 1:
        tela1();
        //! lgo  04 10 2021  modo0_zera_valores();
        flagEstado = selecEstado(1, tecla_valida);// verifica tecla "funcao" ou "ajuda"
        break;

    case 2:
        tela2();
        modo0_zera_valores();
        flagEstado = selecEstado(2, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 3:
        tela3();
        modo0_zera_valores();
        flagEstado = selecEstado(3, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 4:
        tela4();
        modo0_zera_valores();
        flagEstado = selecEstado(4, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 5:
        tela5();
        modo0_zera_valores();
        flagEstado = selecEstado(5, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 6:
        tela6();
        modo0_zera_valores();
        flagEstado = selecEstado(6, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 7:
        tela7();
        modo0_zera_valores();
        flagEstado = selecEstado(7, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 8:
        tela8();
        modo0_zera_valores();
        flagEstado = selecEstado(8, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 9:
        tela9();
        modo0_zera_valores();
        flagEstado = selecEstado(9, tecla_valida);// verifica tecla "ok" ou "prox"
        break;

    case 10:
        tela10();
        modo0_zera_valores();
        flagEstado = selecEstado(10, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 11:
        tela11();
        flagMostraVel = 0;
        flagEstado = selecEstado(11, tecla_valida);
        modo0_zera_valores();
        if (flagEstado == 100) {
            flagMostraVel = 0;

        }
        if (flagEstado == 12) {
            flagMostraVel = 1;

            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }

        break;

    case 12:
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eS0S1);
        tela12();
        lcd_escreve_Dist(SensorDigital.GetValue(eS0S1));

        //Verifica se troca de estado
        flagEstado = selecEstado(12, tecla_valida);
        if (numSensores == 2) {
            if (flagEstado == 13) {

                flagEstado = 100;
            }
        }

        //Se trocou de estado desliga o cursor
        if (flagEstado != 12)
            Lcd.SetCursorOFF();

        break;

    case 13:  //! "d entre S0 e S2 "
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eS0S2);
        tela13();
        lcd_escreve_Dist(SensorDigital.GetValue(eS0S2));

        flagEstado = selecEstado(13, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 14:
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eS0S3);
        tela14();
        lcd_escreve_Dist(SensorDigital.GetValue(eS0S3));
        flagEstado = selecEstado(14, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 15:
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eS0S4);
        tela15();
        lcd_escreve_Dist(SensorDigital.GetValue(eS0S4));
        flagEstado = selecEstado(15, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 17:
        Func = 1;
        tela17();
        flagEstado = selecEstado(38, tecla_valida);
        break;

    case 18:
        numSensores = 2;
        flagEstado = 11;
        break;

    case 19:
        numSensores = 5;
        flagEstado = 11;
        break;

    case 21:
        tela21();								//Tela dentro da funcao 2
        Func = 2;
        flagMostraVel = 0;
        flagEstado = selecEstado(16, tecla_valida);
        if (flagEstado == 100)			//Escolhe nao informar a largura
        {
            flagMostraVel = 0;
        }
        if (flagEstado == 22)				//Escolhe informar a largura
        {
            flagMostraVel = 1;
        }
        break;

    case 22:
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eLargura);
        tela22();
        lcd_escreve_Dist(SensorDigital.GetValue(eLargura));
        flagEstado = selecEstado(17, tecla_valida);	// verifica tecla "ok" ou "prox"
        lcd_cursorBlack(posCursor);
        break;

    case 31:
        Func = 3;
        numInt = 10;
        flagEstado = 100;
        break;
    case 41:
        Func = 4;
        flagEstado = 100;
        break;
    case 51:
        //Func=5;
        Func = 1;
        numSensores = 2;
        flag_funcao_5 = 1;						//Indica que a funcao
        //escolhida foi 5
        //utiliza rotinas da funcao
        //1
        tela11();
        flagEstado = selecEstado(18, tecla_valida);
        if (flagEstado == 100) {
            flagMostraVel = 0;
        }
        if (flagEstado == 52) {
            flagMostraVel = 1;
        }
        break;
    case 52:
        //!Teste bobina, usa mesma distancia SOS1

        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eLargura);
        tela52();
        lcd_escreve_Dist(SensorDigital.GetValue(eLargura));

        flagEstado = selecEstado(19, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 61:
        Func = 6;
        numInt = 10;
        flagEstado = 100;
        break;
        //    case 71:
        //
        //        Func = 7;
        //        flagEstado = 100;
        //
        //        //Mensagem NUm intervalos
        //        Lcd.Write(LCD_LINHA_1, (char*) &MSG_NUM_INTERVALOS[IDIOMA - 1][0]);
        //        Lcd.Write(LCD_LINHA_2, (char*) &MSG_1_10[0]);
        //        Func = 7;
        //
        //        if(tecla_valida== L_FUNC ){
        //           flagEstado = 100;
        //           numInt=1;
        //         }
        //         else if(tecla_valida== R_FUNC ){
        //           flagEstado = 100;
        //           numInt=10;
        //        }
        //         else{
        //             }
        //
        //        break;




        //    case 81:
        //        Func = 8;
        //        flagEstado = 100;
        //        break;
        //
    case 72:
        Func=7;
        tela72();
        flagEstado=selecEstado(62,tecla_valida);
        break;
    case 73:
        numIntervalosF7=1;
        flagEstado=77;
        break;
    case 74:
        numIntervalosF7=10;
        flagEstado=77;
        break;
    case 77:
        Func=7;
        flagEstado=100;
        break;
    case 82:
        Func=8;
        tela72();
        flagEstado=selecEstado(63,tecla_valida);
        break;
    case 83:
        numIntervalosF7=1;
        flagEstado=87;
        break;
    case 84:
        numIntervalosF7=10;
        flagEstado=87;
        break;
    case 87:
        Func=8;
        flagEstado=100;
        break;


    case 92:
        Func = 9;
        //! d entre mic
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.UpdateReading(tecla_valida, eLargura);
        tela92();
        lcd_escreve_Dist(SensorDigital.GetValue(eLargura));
        flagEstado = selecEstado(37, tecla_valida);	// verifica tecla "ok" ou "prox"
        
        flagMostraVel = 1;

        break;

    case 99:
        Func = 10;

        //! Numero de intervalos
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR+2, LCD_LINHA_2);
        }
        //atualiza distancia
        SensorDigital.IncNumInterval(tecla_valida);
        tela99();

        numInt=SensorDigital.GetNumInterval();
        lcd_escreve_Int(numInt);

        flagEstado = selecEstado(55, tecla_valida);	// verifica tecla "ok" ou "prox"

        if (numInt < 1) {
            flagEstado = 99;
        }
        if (numInt > 10) {
            flagEstado = 99;
        }

        break;

    case STATE_INICIA_EXPERIMENTO:   //100
        if (Lcd.GetCursorState()) {
            Lcd.SetCursorOFF();
        }

        tela100();
        //flagEstado=selecEstado100(tecla_valida);
        // Inicializa sensores
        // modo0_zera_valores();  //Lgo
        

        stopTimer();
        timeCounter = 0;
        timeCounter2 = 0;
        flagEstado = 100;
        despresa = 0;
        Modo = 1;

        //@@					delay_ms(400);
        //??					sensores_init();	// habilita interrupcoes dos sensores
        break;

    case 240:
        if(MuxTimers.CheckMsDelay()){
            tela240();
            MuxTimers.SetMsDelay(2000);
            flagEstado=241;
        }
        break;

    case 241:
        if(MuxTimers.CheckMsDelay()){
            tela241();
            MuxTimers.SetMsDelay(2000);
            flagEstado=242;
        }
        break;

    case 242:
        if(MuxTimers.CheckMsDelay()){
            flagEstado=0;
        }
        break;

    case 900:
        tela900();
        modo0_zera_valores();
        flagEstado = selecEstado(56, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;
    case 902:
        Func = 11;
        sensor0 = 1;
        sensor1 = 16;
        sensor2 = 64;
        sensor3 = 128;
        sensor4 = 32;
        //@@					set_tris_b(0xFF);
        tela902();
        //@@					portab=*PORTB;
        

        lcd_posicaoxy(1, LCD_LINHA_1);
        lcd_escreve("S:0");
        //        if (portab & sensor0) {
        if(SensorDigital.GetLevel(eS0)){
            lcd_escreve("o ");
        } else {
            lcd_escreve("x ");
        }
        lcd_posicaoxy(6, LCD_LINHA_1);
        lcd_escreve("1");
        //if (portab & sensor1) {
        if(SensorDigital.GetLevel(eS1)){ 
            lcd_escreve("o ");
        } else {
            lcd_escreve("x ");
        }
        lcd_posicaoxy(9, LCD_LINHA_1);
        lcd_escreve("2");
        // if (portab & sensor2) {
        if(SensorDigital.GetLevel(eS2)){
            lcd_escreve("o ");
        } else {
            lcd_escreve("x ");
        }
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve("3");
        
        //if (portab & sensor3) {
        if(SensorDigital.GetLevel(eS3)){
            lcd_escreve("o ");
        } else {
            lcd_escreve("x ");
        }
        lcd_posicaoxy(15, LCD_LINHA_1);
        lcd_escreve("4");

        // if (portab & sensor4) {
        if(SensorDigital.GetLevel(eS4)){
            lcd_escreve("o");
        } else {
            lcd_escreve("x");
        }

        //	portab=0; //Laercio

        flagEstado = selecEstado(57, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;
    case 990:
        tela990();
        flagEstado = selecEstado(58, tecla_valida);	// verifica tecla "funcao" ou "ajuda"
        break;
    case 1012:
        tela1012();
        modo0_zera_valores();
        flagEstado = selecEstado(58, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case 1021:
        /*
         Func=12;
         flagMostraVel = 1;
         if(black > CURSOR_BLACK)
         {
         lcd_cursorBlack(posCursor);
         }
         else
         {
         lcd_escreve_Dist(Larg);
         tela1021();
         //atualiza distancia
         setaV = verificaSetaV(tecla_valida);
         lcd_atualiza_Dist(setaV,posCursor);
         Larg = lcd_getDistancia();		//armazena na variavel o valor escrito na tela
         }
         black = black + CURSOR_INC;

         //posicao do cursor
         setaH = verificaSetaH(tecla_valida);
         posCursor = lcd_desloca_H(posCursor,setaH);

         flagEstado=selecEstado(59,tecla_valida);	// verifica tecla "ok" ou "prox"
         lcd_cursorBlack(posCursor);
         */

        //! Numero de intervalos
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(POSICAO_CURSOR, LCD_LINHA_2);
        }

        Func = 12;
        flagMostraVel = 1;

        //atualiza a largura
        SensorDigital.UpdateReading(tecla_valida, eLargura);
        tela1021();
        lcd_escreve_Dist(SensorDigital.GetValue(eLargura));

        flagEstado = selecEstado(59, tecla_valida);	// verifica tecla "ok" ou "prox"

        break;

    case 1022:
        /*

        if (black > CURSOR_BLACK) {
            lcd_cursorBlack(posCursor);
        } else {
            //lcd_escreve_Dist(massa);
            lcd_escreve_Massa(massa);
            tela1022();
            //atualiza massa
            setaV = verificaSetaV(tecla_valida);
            lcd_atualiza_Dist(setaV, posCursor);

            //massa=lcd_getDistancia();		//armazena na variavel o valor escrito na tela
            massa = lcd_getMassa();
        }
        black = black + CURSOR_INC;

        //posicao do cursor
        setaH = verificaSetaH(tecla_valida);
        //posCursor=lcd_desloca_H(posCursor,setaH);
        posCursor = lcd_desloca_H_massa(posCursor, setaH);
        flagEstado = selecEstado(60, tecla_valida);	// verifica tecla "ok" ou "prox"
        lcd_cursorBlack(posCursor);
         */
        if (!Lcd.GetCursorState()) {
            Lcd.SetCursorOn();
            Lcd.SetCursorPosition(4, LCD_LINHA_2);
        }
        SensorDigital.UpdateReading(tecla_valida, eMassa);
        SensorDigital.Result.massa=SensorDigital.GetValue(eMassa);
        tela1022();
        lcd_escreve_Massa(SensorDigital.Result.massa);
        flagEstado = selecEstado(60, tecla_valida);	// verifica tecla "ok" ou "prox"
        break;

    case STATE_SAVE_USB:   //Salvamento na pendrive
        Salvar_usb();
        //Aqui analisa a tecla e decide se salva na Usb ou se segue para a funçaõ
        bret=false;

        if(tecla_valida== M_FUNC ){
            if(!GetPendriveState())
                flagEstado=STATE_WAIT_PEN_DRIVE;
            else
                flagEstado=STATE_SAVE_AT_PEN_DRIVE;
        }
        else if(tecla_valida== R_FUNC ){
            flagEstado=iNextState;
        }
        else if(tecla_valida== L_FUNC ){
            flagEstado=106;
            Modo = 1;
        }
        break;

    case STATE_WAIT_PEN_DRIVE:   //Salvamento na pendrive
        if(!GetPendriveState()){
            //Escreve mensagem
            Lcd.Write(LCD_LINHA_1, (char*) &MSG_NO_PENDRIVEUSB[IDIOMA - 1][0]);
            Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR);
            
        }
        else{
            //Força a tecla para salvamento no pendrive, se não estiver inserida iria pedir pendrive e confirmação pela tecla
            flagEstado=STATE_ASK_SAVE_AT_PEN_DRIVE;
            tecla_valida= R_FUNC;
        }

        //Se pressionou a tecla da esquerda vola para o resulado do teste
        if(tecla_valida== L_FUNC ){
            flagEstado=106;
            Modo = 1;
        }
        break;

    case STATE_ASK_SAVE_AT_PEN_DRIVE:
        Lcd.Write(LCD_LINHA_1, (char*) &MSG_SAVE_AT_PENDRIVEUSB[IDIOMA - 1][0]);
        Lcd.Write(LCD_LINHA_2, (char*) &MSG__MENOR_________OK[IDIOMA - 1]);


        if(tecla_valida== R_FUNC){
            flagEstado=STATE_SAVE_AT_PEN_DRIVE;
        }
        else if(tecla_valida== L_FUNC ){
            // flagEstado=106;
            // Modo = 1;
            flagEstado=STATE_SAVE_USB;
        }


        break;


    case STATE_SAVE_AT_PEN_DRIVE:
        //!Salva dados Usb
        switch(Func){
        case FUNC_1:

            if (flag_funcao_5)
                bret=SaveDigital.SaveFunc2(flagMostraVel,FUNC_5);
            else
                bret=SaveDigital.SaveFunc1(numSensores,flagMostraVel);
            flag_funcao_5 = 0;
            break;
        case FUNC_2:
        case FUNC_9:
            bret=SaveDigital.SaveFunc2(flagMostraVel,Func);
            break;
        case FUNC_3:
        case FUNC_10:
            bret=SaveDigital.SaveFunc3_10(Func);
            break;

        case FUNC_6:
        case FUNC_4:
            bret=SaveDigital.SaveFunc4_6(Func);
            break;

        case FUNC_7:
        case FUNC_8:
            bret=SaveDigital.SaveFunc7_8(Func);

            break;
        case FUNC_12:
            bret=SaveDigital.SaveFunc2(flagMostraVel,Func);

            break;
        }

        if(bret)
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_DIGITAL_OK[IDIOMA - 1][0]);
        else
            Lcd.Write(LCD_LINHA_2, (char*) &MSG_USB_DIGITAL_NOK[IDIOMA - 1][0]);

        //Configura para mostrar a mensagem por 500ms
        MuxTimers.SetMsDelay(1000);
        flagEstado= STATE_SHOW_SAVING_RESULT;
        
        break;


        case STATE_SHOW_SAVING_RESULT:
            if(MuxTimers.CheckMsDelay()){
                //flagEstado=iNextState;
                flagEstado=STATE_REPETIR_SAIR;
            }
            break;

        case STATE_REPETIR_SAIR:
            Lcd.Write(LCD_LINHA_1, (char *)&MSG106_1[IDIOMA-1][0]);  //Fim experimento
            Lcd.Write(LCD_LINHA_2, (char *)&MSG_REPETIR_FUNCAO[IDIOMA-1][0]);

            if (tecla_valida == R_FUNC) {
                flagEstado=iNextState;
            }
            else if (tecla_valida == L_FUNC){
                flagEstado=STATE_INICIA_EXPERIMENTO;

            }

            break;
            
    }

    if (_flagEstado != flagEstado)
        return true;
    else
        return false;

}


/*********************************************************************************************//**
 * \function     EstadoModo1
 * \details     quando chegou aqui finalizou o ensaio e analisa o que deve mostrar na tela
                em função da escolha do usuário 
  
 * \author     
 * \date   atualizado      29/09/2022
 ************************************************************************************************/
bool EstadoModo1(int16 _flagEstado) {
    int value = 255;					//leitura do AD

    switch (_flagEstado) {

    case 100:
         tela100();
    
        if (tecla_valida == R_FUNC) {
            flagEstado = 0;
            Modo = 0;
            flag_funcao_5 = 0;
            lcd_limpa();
        }
        //if (Func==5){
        //	timeCounter=0;
        //	timeCounter2=0;
        //	flagEstado=501;
        //	sensores_desab();
        //setup_adc_ports( ALL_ANALOG );
        //setup_adc(ADC_CLOCK_INTERNAL );
        //set_adc_channel( 5 );
        //}
        break;
    case 101:
        lcd_limpa();
        switch (Func) {
        case 1:
            flagEstado = 102;
            break;
        case 2:
            flagEstado = 202;
            break;
        case 3:
            flagEstado = 302;
            break;
        case 4:
            flagEstado = 402;
            break;
            //case 5:
            //	flagEstado=502;
            //	break;
        case 6:
            flagEstado = 302;
            break;
        case 7:
            flagEstado = 702;
            break;
        case 8:
            flagEstado = 802;
            break;
        case 9:
            flagEstado = 902;
            lcd_linha2();
            lcd_escreve((char*) &MSG100_2);
//@					disable_interrupts(INT_EXT);
            break;
        case 10:
            flagEstado = 302;
            break;
        case 12:
            flagEstado = 202;
            break;
        }

        break;

    case 102:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "S0>S1");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        if (sensor == 1) {
            if (numSensores == 2) {
                              
                if(flag_funcao_5)
                    SensorDigital.CalcFunc5_12();
                else
                    SensorDigital.CalcFunc1();    

                flagEstado = 106;
                stopTimer();
            } else {
                flagEstado = 103;
            }
        }
        break;

    case 103:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "S0>S2");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        if (sensor == 2) {
            flagEstado = 104;
        }
        break;

    case 104:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "S0>S3");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }

        if (sensor == 3) {
            flagEstado = 105;
        }
        break;

    case 105:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "S0>S4");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        if (sensor == 4) {
            //! Final experimento Func1, calcula os valores 
            SensorDigital.CalcFunc1();
            flagEstado = 106;
            stopTimer();
        }
        break;

    case 106:  
        tela106(); //! Experimento Finalizado
       
        flagEstado = selecEstado106(tecla_valida);   //! aguarda a tecla para ver o que mostrar
        if (flagEstado == 1) { //! Escolheur F?
            Modo = 0;
           //! flag_funcao_5 = 0;
            iNextState=flagEstado;
            flagEstado=STATE_SAVE_USB;
        }
        if (flagEstado == 110) {   //Na Func1 escolheu Ver
            Modo = 2;
            lcd_limpa();
        }
        if (flagEstado == 250) {
            Modo = 2;
            lcd_limpa();
        }
        if (flagEstado == 350) {
            Modo = 2;
            passag = 0;
            lcd_limpa();
        }
        if (flagEstado == 410) {
            Modo = 2;
            passag = 0;
            lcd_limpa();
        }
        if (flagEstado == 710) {
            Modo = 2;
            passag = 0;
            passag2 = 0;
            lcd_limpa();
        }
        if (flagEstado==810)
			{
				Modo=2;
				passag=0;
				passag2=0;
				lcd_limpa();
			}
        
        if (flagEstado == 950) {
            Modo = 2;
            lcd_limpa();
        }
        if (flagEstado == 100) {  //escolheu Repetir
            Modo = 0;
            //flag_funcao_5 = 0;
        }
        break;

    case 202:
        tela102();
        lcd_posicaoxy(13, LCD_LINHA_1);
        lcd_escreve((char*) "pass");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;

    case 302:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "Int:");
        lcd_escreve_digito(passag);
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;

    case 402:
        tela102();
        lcd_posicaoxy(12, LCD_LINHA_1);
        lcd_escreve((char*) "Int:");
        lcd_escreve_digito(passag);
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;

    case 501:

//@@			value = read_adc();
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 0;
//@@				setup_adc( ADC_OFF );
        }
        if (value < 128) {
            flagEstado = 502;
//@@				delay_ms(10);
        }
        break;
    case 502:
//@@			value = read_adc();
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flagEstado = 0;
            //setup_adc( ADC_OFF );
        }
        if (value > 128) {
            flagEstado = 503;
//@@				delay_ms(4);		//envenenado:: retardo devido a imantacao da bobina
            lcd_limpa();
            msg_zeraTimer();
            startTimer();
            //setup_adc( ADC_OFF );
            //setup_adc_ports(NO_ANALOGS);
//??				sensores_init();
//@@				enable_interrupts(GLOBAL);

        }
        break;
    case 503:
        tela102();
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 0;
            stopTimer();
            //setup_adc( ADC_OFF );
        }
        break;
    case 504:
        tela106();
        flagEstado = selecEstado(41, tecla_valida);
        if (flagEstado == 1) {
            Modo = 0;
            flag_funcao_5 = 0;
        }
        if (flagEstado == 550) {
            if (flagMostraVel == 0) {
                flagEstado = 549;
            }
            Modo = 2;
            lcd_limpa();
        }
        break;

    case 505:
        Modo = 0;
        flag_funcao_5 = 0;
        flagEstado = 100;
        //setup_adc( ADC_OFF );
        break;
    case 702:
    case 802:
        tela702();
        lcd_posicaoxy(10, LCD_LINHA_1);
        lcd_escreve((char*) ">");
        lcd_escreve_digito(passag);
        lcd_posicaoxy(16, LCD_LINHA_1);
        lcd_escreve_digito(passag2);

        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;
    case 703:
        tela702();
        lcd_posicaoxy(10, LCD_LINHA_1);
        if (Func == 7) {
            lcd_escreve((char*) ">");
        } else {
            lcd_escreve((char*) "<");
        }
        lcd_escreve_digito(passag);
        lcd_posicaoxy(16, LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        if ((flagFimS0 == 1) & (flagFimS1 == 1)) {
//??				sensores_desab();
            stopTimer();
            flagEstado = 106;
        }
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;


     case 803:
        tela702();
        lcd_posicaoxy(10, LCD_LINHA_1);
        if (Func == 7) {
            lcd_escreve((char*) ">");
        } else {
            lcd_escreve((char*) "<");
        }
        lcd_escreve_digito(passag);
        lcd_posicaoxy(16, LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        if ((flagFimS0 == 1) & (flagFimS1 == 1)) {
//??				sensores_desab();
            stopTimer();
            flagEstado = 106;
            if(numIntervalosF7==2){
					numIntervalosF7=1;
				}
        }
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        break;


    case 902:
        tela102();
        lcd_posicaoxy(12,LCD_LINHA_1);
        lcd_escreve("S0>S1");
        if (tecla_valida == R_FUNC) {
            Modo = 0;
            flag_funcao_5 = 0;
            flagEstado = 100;
            stopTimer();
        }
        if (sensor == 0) {
            stopTimer();
            flagEstado = 903;
        }
        break;

    case 903:
        tela106();
        flagEstado = selecEstado106(tecla_valida);
        if (flagEstado == 1) {
            Modo = 0;
            flag_funcao_5 = 0;
        }
        if (flagEstado == 150) {
            Modo = 2;
            lcd_limpa();
        }
        if (flagEstado == 100) {
            Modo = 0;
        }
        break;

    }

    if (_flagEstado != flagEstado)
        return true;
    else
        return false;

}

void modo2_escreveTempo_1(int16 passagem) {
    int16 temp;
    lcd_linha1();
    lcd_escreve("t");
    if (flagEstado == 450) {
        if (passagem == 9) {
            lcd_escreve("10");
        } else {
            temp = passagem + 1;
            lcd_escreve_digito(temp);
            lcd_escreve(" ");
        }
    } else {
        lcd_escreve("0,");
        if (passagem == 9) {
            lcd_escreve("10");
        } else {
            temp = passagem + 1;
            lcd_escreve_digito(temp);
            lcd_escreve(" ");
        }
        lcd_posicaoxy(6, LCD_LINHA_1);
    }
    lcd_escreve("=");
    //lcd_escreve_tempo(SensorDigital.Result.tempos[passagem], SensorDigital.Result.tempos2[passagem]);
    lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal[passagem]);
    lcd_escreve(" s");
}

void modo2_escreveFreq_1(int16 passagem) {
    int16 temp;
    lcd_linha1();
    lcd_escreve("f");
    if (passagem == 9) {
        lcd_escreve("10");

    } else {
        temp = passagem + 1;
        lcd_escreve_digito(temp);
        lcd_escreve(" ");
    }
//    SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[passagem] / 100;
//    SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[passagem] * 100;
//    SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
//    SensorDigital.Result.fvelocidade[0] = (float) 1 / SensorDigital.Result.tempo2;
//    SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.Result.fvelocidade[0] * 1000;
    lcd_escreve("=");
    lcd_escreve_veloc(SensorDigital.Result.ffrequencia[passagem]);
    lcd_escreve(" Hz");
}


/*********************************************************************************************//**
 * \function     EstadoModo2
 * \details      Mostra no display o resultado do ensaio 
 *               agora quando chamado já calcula os resultados (antes sempre recalculava no estado da função)
 *               
 *               
 *               
 * \author     
 * \date       atualizado  28/09/2022
 ************************************************************************************************/
bool EstadoModo2(int16 _flagEstado) {

    switch (_flagEstado) {

    case 110:
        if (flagMostraVel == 0) {
            if (flag_funcao_5 == 1) {
                flagEstado = 549;
                break;
            } else {
                flagEstado = 111;
                break;
            }
            //break;
        } else {
            if (flag_funcao_5 == 1) {
                flagEstado = 550;
                break;
            }

        }
        flagEstado = selecEstado(21, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        if (flagEstado == 150) {
            if (numSensores == 2) {
                flagEstado = 149;
                break;
            }
        }
        if (flagEstado == 170) { 
            if (numSensores == 2) {
                flagEstado = 169;
                break;
            }
        }
        tela110();
        break;
    case 111:
        tela111();
        flagEstado = selecEstado(52, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        if (flagEstado == 150) {
            if (numSensores == 2) {
                flagEstado = 149;
            }
        }
        break;

    case 149:
        tela149();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(39, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 150:
        tela150();
        lcd_posicaoxy(6, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(22, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 151:
        tela151();
        lcd_posicaoxy(6, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[1], SensorDigital.Result.tempos2[1]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(23, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 152:
        tela152();
        lcd_posicaoxy(6, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[2], SensorDigital.Result.tempos2[2]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(24, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 153:
        tela153();
        lcd_posicaoxy(6, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[3], SensorDigital.Result.tempos2[3]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(25, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 154:		// t1,2:
        tela154();
        lcd_posicaoxy(6, LCD_LINHA_1);
        if (SensorDigital.Result.tempos[1] < SensorDigital.Result.tempos[0]) {
            aux_tempo = SensorDigital.Result.tempos[1] + 10000;
            aux_tempo2 = SensorDigital.Result.tempos2[1] - 1;
        } else {
            aux_tempo = SensorDigital.Result.tempos[1];
            aux_tempo2 = SensorDigital.Result.tempos2[1];
        }
        SensorDigital.Result.tempos[4] = aux_tempo - SensorDigital.Result.tempos[0];
        SensorDigital.Result.tempos2[4] = aux_tempo2 - SensorDigital.Result.tempos2[0];
        lcd_escreve_tempo(SensorDigital.Result.tempos[4], SensorDigital.Result.tempos2[4]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(26, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 155:		// t2,3:
        tela155();
        lcd_posicaoxy(6, LCD_LINHA_1);
        if (SensorDigital.Result.tempos[2] < SensorDigital.Result.tempos[1]) {
            aux_tempo = SensorDigital.Result.tempos[2] + 10000;
            aux_tempo2 = SensorDigital.Result.tempos2[2] - 1;
        } else {
            aux_tempo = SensorDigital.Result.tempos[2];
            aux_tempo2 = SensorDigital.Result.tempos2[2];
        }
        SensorDigital.Result.tempos[5] = aux_tempo - SensorDigital.Result.tempos[1];
        SensorDigital.Result.tempos2[5] = aux_tempo2 - SensorDigital.Result.tempos2[1];
        lcd_escreve_tempo(SensorDigital.Result.tempos[5], SensorDigital.Result.tempos2[5]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(27, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 156:		// t3,4:
        tela156();
        lcd_posicaoxy(6, LCD_LINHA_1);
        if (SensorDigital.Result.tempos[3] < SensorDigital.Result.tempos[2]) {
            aux_tempo = SensorDigital.Result.tempos[3] + 10000;
            aux_tempo2 = SensorDigital.Result.tempos2[3] - 1;
        } else {
            aux_tempo = SensorDigital.Result.tempos[3];
            aux_tempo2 = SensorDigital.Result.tempos2[3];
        }
        SensorDigital.Result.tempos[6] = aux_tempo - SensorDigital.Result.tempos[2];
        SensorDigital.Result.tempos2[6] = aux_tempo2 - SensorDigital.Result.tempos2[2];
        lcd_escreve_tempo(SensorDigital.Result.tempos[6], SensorDigital.Result.tempos2[6]);
        lcd_escreve(" s ");
        flagEstado = selecEstado(28, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 169:
        tela169();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eS0S1) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[0]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");

        flagEstado = selecEstado(40, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 170: //! {"Vm0,1:"};
        tela170();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //      SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //      SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eS0S1) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[0]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(29, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 171:  //!{"Vm0,2:"};
        tela171();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //     SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[1] / 100;
        //     SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[1] * 100;
        //     SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //     SensorDigital.Result.fvelocidade[1] = (float) SensorDigital.GetValue(eS0S2) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[1]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(30, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 172:  //! {"Vm0,3:"};
        tela172(); 
        lcd_posicaoxy(7, LCD_LINHA_1);
        //      SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[2] / 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[2] * 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //      SensorDigital.Result.fvelocidade[2] = (float) SensorDigital.GetValue(eS0S3) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[2]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(31, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 173: //! {"Vm0,4:"};
        tela173();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //      SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[3] / 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[3] * 100;
        //      SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //      SensorDigital.Result.fvelocidade[3] = (float) SensorDigital.GetValue(eS0S4) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[3]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(32, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 174: //! {"Vm1,2:"};
        tela174();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //        if (SensorDigital.Result.tempos[1] < SensorDigital.Result.tempos[0]) {
        //            aux_tempo = SensorDigital.Result.tempos[1] + 10000;
        //            aux_tempo2 = SensorDigital.Result.tempos2[1] - 1;
        //        } else {
        //            aux_tempo = SensorDigital.Result.tempos[1];
        //            aux_tempo2 = SensorDigital.Result.tempos2[1];
        //        }
        //        SensorDigital.Result.tempos[4] = aux_tempo - SensorDigital.Result.tempos[0];
        //        SensorDigital.Result.tempos2[4] = aux_tempo2 - SensorDigital.Result.tempos2[0];
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[4] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[4] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[4] = (float) (SensorDigital.GetValue(eS0S2)
        //                - SensorDigital.GetValue(eS0S1)) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[4]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(33, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 175:  //! {"Vm2,3:"};
        tela175();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //        if (SensorDigital.Result.tempos[2] < SensorDigital.Result.tempos[1]) {
        //            aux_tempo = SensorDigital.Result.tempos[2] + 10000;
        //            aux_tempo2 = SensorDigital.Result.tempos2[2] - 1;
        //        } else {
        //            aux_tempo = SensorDigital.Result.tempos[2];
        //            aux_tempo2 = SensorDigital.Result.tempos2[2];
        //        }
        //        SensorDigital.Result.tempos[5] = aux_tempo - SensorDigital.Result.tempos[1];
        //        SensorDigital.Result.tempos2[5] = aux_tempo2 - SensorDigital.Result.tempos2[1];
        //
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[5] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[5] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[5] = (float) (SensorDigital.GetValue(eS0S3)- SensorDigital.GetValue(eS0S2)) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[5]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(34, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 176:     //!{"Vm3,4:"};
        tela176();
        lcd_posicaoxy(7, LCD_LINHA_1);
        //       if (SensorDigital.Result.tempos[3] < SensorDigital.Result.tempos[2]) {
        //           aux_tempo = SensorDigital.Result.tempos[3] + 10000;
        //           aux_tempo2 = SensorDigital.Result.tempos2[3] - 1;
        //       } else {
        //           aux_tempo = SensorDigital.Result.tempos[3];
        //           aux_tempo2 = SensorDigital.Result.tempos2[3];
        //       }
        //       SensorDigital.Result.tempos[6] = aux_tempo - SensorDigital.Result.tempos[2];
        //       SensorDigital.Result.tempos2[6] = aux_tempo2 - SensorDigital.Result.tempos2[2];
        //       SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[6] / 100;
        //       SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[6] * 100;
        //       SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //       SensorDigital.Result.fvelocidade[6] = (float) (SensorDigital.GetValue(eS0S4)- SensorDigital.GetValue(eS0S3)) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[6]);
        lcd_posicaoxy(14, LCD_LINHA_1);
        lcd_escreve("m/s");
        flagEstado = selecEstado(35, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 250:
        if (flagMostraVel == 0) {
            if (Func == 2) {
                flagEstado = 252;
                break;
            }
        }
        tela250();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s   ");
        flagEstado = selecEstado(47, tecla_valida);
        if (Func == 12) {
            if (flagEstado == 1253)	//Se a funcao he 12 o proximo estado deve
                //o que mostra a energia
            {
                flagEstado = 1253;
            }
        }
        if (Func == 2) {
            if (flagEstado == 1253)		//Se a funcao he 2 o proximo estado deve
                //o que mostra a vm
            {
                flagEstado = 251;
            }
        }
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 251:
        tela251();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //  SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //  SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //  SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //  SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[0]);
        lcd_escreve(" m/s");
        flagEstado = selecEstado(48, tecla_valida);
        if (Func == 12) {
            if (flagEstado == 250)	//Se a funcao he 12 o proximo estado deve
                //o que mostra a energia
            {
                flagEstado = 250;
            }
        }
        if (Func == 2) {
            if (flagEstado == 1253)		//Se a funcao he 2 o proximo estado deve
                //o que mostra a vm
            {
                flagEstado = 250;
            }
        }
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 252:
        tela149();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s");
        if (Func == 2) {
            flagEstado = selecEstado(53, tecla_valida);
        }
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 350:
        tela350();
        modo2_escreveTempo_1(passag);
        flagEstado = selecEstado350(tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 410:
        tela410();
        flagEstado = selecEstado(42, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        if (flagEstado == 450) {
            passag = 0;
        }
        if (flagEstado == 470) {
            passag = 0;
        }
        break;

    case 450:
        tela450();
        modo2_escreveTempo_1(passag);
        flagEstado = selecEstado450(tecla_valida);
        break;

    case 470:
        tela470();
        modo2_escreveFreq_1(passag);
        flagEstado = selecEstado470(tecla_valida);
        break;

    case 549:
        tela149();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s");
        flagEstado = selecEstado(54, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    case 550:
        if (flagMostraVel == 0) {
            flagEstado = 549;
        }
        tela250();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve(" s   ");
        flagEstado = selecEstado(43, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 551:    //"Vm="
        tela251();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[0]);
        lcd_escreve(" m/s  ");
        flagEstado = selecEstado(44, tecla_valida);
        //lcd_limpa();
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 552:    //"a =" 
        tela552();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 * SensorDigital.Result.tempo2; //tempo quadrado
        //        SensorDigital.Result.fAcel = (float) SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;//acel=2*x/t2
        //        SensorDigital.Result.fAcel = (float) SensorDigital.Result.fAcel * 2000;
        lcd_escreve_veloc(SensorDigital.Result.fAcel);
        lcd_escreve(" m/s2");
        flagEstado = selecEstado(45, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 553:    //"Vf="
        tela553();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempo2; 		 // tempo
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 * SensorDigital.Result.tempo2; //tempo quadrado
        //        SensorDigital.Result.fAcel = (float) 2 * SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;
        //        SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.Result.fAcel * SensorDigital.Result.tempo;	//SensorDigital.Result.fvelocidade final = a*t
        SensorDigital.Result.fvelocidade[1] = (float) SensorDigital.Result.fAcel * SensorDigital.Result.fTempoFinal[0];	//SensorDigital.Result.fvelocidade final = a*t
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[1]);
        lcd_escreve(" m/s ");
        flagEstado = selecEstado(46, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 710:
        tela710();
        flagEstado = selecEstado(49, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        if (flagEstado == 750) {
            passag = 0;

        }
        if (flagEstado == 770) {
            passag2 = 0;

        }
        break;

    case 750:
        tela750();   //função 7 mostra temo s0
        lcd_posicaoxy(3, LCD_LINHA_1);
        //lcd_escreve_tempo(SensorDigital.Result.tempos[passag], SensorDigital.Result.tempos2[passag]);
        lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal[passag]);
        lcd_escreve("s");
        lcd_posicaoxy(15, LCD_LINHA_1);
        lcd_escreve_digito(passag);
        flagEstado = selecEstado750(tecla_valida,numIntervalosF7);
        
        //Se escolheu um sensor
        //    if(passag>=numInt)
        //         passag=0;

        break;
    case 751:
        tela751();
        lcd_posicaoxy(3, LCD_LINHA_1);
        lcd_escreve_tempo(SensorDigital.Result.S0vtempos[passag2], SensorDigital.Result.S0vtempos2[passag2]);
        lcd_escreve("s");
        lcd_posicaoxy(15, LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        flagEstado = selecEstado751(tecla_valida,numIntervalosF7);
        break;
    
       case 770:
        tela770();
        lcd_posicaoxy(3, LCD_LINHA_1);
        // lcd_escreve_tempo(SensorDigital.Result.S1tempos[passag2], SensorDigital.Result.S1tempos2[passag2]);
        lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal_S1[passag2]);
        lcd_escreve("s");
        lcd_posicaoxy(15, LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        flagEstado = selecEstado770(tecla_valida,numIntervalosF7);

        break;

    case 810:
        tela710();
        flagEstado=selecEstado(64,tecla_valida);
        if (flagEstado==106){
            Modo=1;
        }
        if (flagEstado==850){
            passag=0;
        }
        if (flagEstado==870){
            passag2=0;
        }
        break;

    case 850:
        tela750();
        lcd_posicaoxy(3,LCD_LINHA_1);
        //	lcd_escreve_tempo(tempos[passag],tempos2[passag]);
        lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal[passag]);
        lcd_escreve("s");
        lcd_posicaoxy(15,LCD_LINHA_1);
        lcd_escreve_digito(passag);
        flagEstado=selecEstado850(tecla_valida,numIntervalosF7);
        break;

    case 851:
        tela751();
        lcd_posicaoxy(3,LCD_LINHA_1);
        //lcd_escreve_tempo(S0vtempos[passag2],S0vtempos2[passag2]);
        lcd_escreve_tempo(SensorDigital.Result.S0vtempos[passag2], SensorDigital.Result.S0vtempos2[passag2]);
        lcd_escreve("s");
        lcd_posicaoxy(15,LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        flagEstado=selecEstado851(tecla_valida,numIntervalosF7);
        break;

    case 870:
        tela770();
        lcd_posicaoxy(3,LCD_LINHA_1);
        //lcd_escreve_tempo(S1tempos[passag2],S1tempos2[passag2]);
        lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal_S1[passag2]);
        lcd_escreve("s");
        lcd_posicaoxy(15,LCD_LINHA_1);
        lcd_escreve_digito(passag2);
        flagEstado=selecEstado870(tecla_valida,numIntervalosF7);
        break;

    case 950:
        tela250();
        lcd_posicaoxy(3, LCD_LINHA_1);
        //        lcd_escreve_tempo(SensorDigital.Result.tempos[0], SensorDigital.Result.tempos2[0]);
        lcd_escreve_tempo2(SensorDigital.Result.fTempoFinal[0]);
        lcd_escreve(" s  ");
        flagEstado = selecEstado(50, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 951:
        tela251();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;
        lcd_escreve_veloc(SensorDigital.Result.fvelocidade[0]);
        lcd_escreve(" m/s");
        flagEstado = selecEstado(51, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;
    case 1253:
        tela1253();
        lcd_posicaoxy(4, LCD_LINHA_1);
        //        SensorDigital.Result.tempo = (float) SensorDigital.Result.tempos[0] / 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempos2[0] * 100;
        //        SensorDigital.Result.tempo2 = (float) SensorDigital.Result.tempo2 + SensorDigital.Result.tempo;
        //        SensorDigital.Result.fvelocidade[0] = (float) SensorDigital.GetValue(eLargura) / SensorDigital.Result.tempo2;
        ////			massa = (float)massa/1000;
        //        SensorDigital.Result.energia = (float) SensorDigital.Result.massa * SensorDigital.Result.fvelocidade[0] * SensorDigital.Result.fvelocidade[0] / 2;
        //        SensorDigital.Result.energia = SensorDigital.Result.energia / 1000;					//Divide por 1000
        //                                                    //para adequar a massa
        //                                                    //em kg
        lcd_escreve_veloc(SensorDigital.Result.energia);
        lcd_escreve("  J  ");
        flagEstado = selecEstado(61, tecla_valida);
        if (flagEstado == 106) {
            Modo = 1;
        }
        break;

    }

    if (_flagEstado != flagEstado)
        return true;
    else
        return false;

}






