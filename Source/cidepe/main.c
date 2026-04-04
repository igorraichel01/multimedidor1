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
#include <18F4620.h>

#use delay(clock=20000000)

//#fuses HS

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //20MHz
#FUSES NOPUT                    //No Power Up Timer
                  //Code protected from reads

#FUSES NOWRT, NODEBUG
#FUSES PROTECT, NOLVP
#FUSES CPB, CPD	//Colocado para protecao do codigo
				//Fabio Bairros - 21/01/2010

int Func=0;		//Definida a variavel neste momento
				//Fabio Bairros - 22/01/2014

#include "lcd.h"
#include "msg.h"
#include "estados.h"
#include "kbd2.h"
#include "sensores.h"
#include "Modo0.h"
#include "Modo1.h"
#include "Modo2.h"



#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2




//caso ocorram outras interrupcoes
#int_default
void isr_default(){

}

///////////////////////  SENSORES /////////////////////////
// interrupcao pela portaB <B4-B7>
// B4-B7 -> sensores S1 a S4
// interrupcao gerada pela acao de um sensor 
// armazena valor da porta do teclado e zera flag

#INT_RB
void int_sensores(){

//	int portab;
	portab=*PORTB;
	if(Func==9){
		if(sensor==1){
			if(portab&sensor1){
				sensor=0;
				tempos[0]=timeCounter;
				tempos2[0]=timeCounter2;
				
			}
	}
	}else if(Func==1){
		if(portab&sensor1){
			sensor=1;
			tempos[0]=timeCounter;
			tempos2[0]=timeCounter2;
			sensor1=0;
		}else if(portab&sensor2){
			sensor=2;
			tempos[1]=timeCounter;
			tempos2[1]=timeCounter2;
			sensor2=0;
		}else if(portab&sensor3){
			sensor=3;
			tempos[2]=timeCounter;
			tempos2[2]=timeCounter2;
			sensor3=0;
		}else if(portab&sensor4){
			sensor=4;
			tempos[3]=timeCounter;
			tempos2[3]=timeCounter2;
			sensor4=0;
		}
	}else if((Func==7)|(Func==8)){
		if(flagEstado==703){
			if(portab&sensor1){	
				S1tempos[passag2]=(int32)timeCounter;
				S1tempos2[passag2]=timeCounter2;
				passag2++;
				if (passag2==10){
					disable_interrupts(INT_RB);
					flagFimS1=1;
					//flagEstado=106;	
				}
			}
		}
	}
	bit_clear(*INTCON,0);			//clear_interrupt(INT_RB);

}

// interrupcao pela INT externa <RB0>  
// B0 -> sensores S0 ou Bobina
// interrupcao gerada pela acao de um sensor 
// armazena valor da porta do teclado e zera flag
#INT_EXT
void int_sensorS0(){

	int portab;
	
	portab=*PORTB;
	
	if (flagEstado==100){
		if(Func==9){
			startTimer();
			msg_zeraTimer();
			sensor=1;
			flagEstado=101;	
			
		//timeCounter=0;										// cronometragem
			
		}else{
			startTimer();
			sensor=0;
			msg_zeraTimer();
			if(Func==3){ 
				timeCounter=700;
			}
			flagEstado=101;	
			passag=0;
			passag2=0;
			despresa=0;
			flagFimS0=0;
			flagFimS1=0;
		}
	}
	if (Func==2)
		{
		ext_int_edge(0,H_TO_L); 
		bit_clear(*INTCON,1);	
	
		//borda de descida do sensor em F2
		if (flagEstado==202)
		{
				stopTimer();
				tempos[0]=timeCounter;
				tempos2[0]=timeCounter2;

				flagEstado=106;	
				ext_int_edge(0,H_TO_L);
				
		}
		
	}

	if (Func==12)
	{
		ext_int_edge(0,H_TO_L); 
		bit_clear(*INTCON,1);	
	
		//borda de descida do sensor em F12
		if (flagEstado==202)
		{
				stopTimer();
				tempos[0]=timeCounter;
				tempos2[0]=timeCounter2;

				flagEstado=106;	
				ext_int_edge(0,H_TO_L);
				
		}
	}	



		if(flagEstado==302){
				
			tempos[passag]=(int32)timeCounter;
			tempos2[passag]=timeCounter2;
			passag++;
			if(Func==6){
				timeCounter=0;
				timeCounter2=0;
			}
			if (passag==numInt){
				sensores_desab();
				stopTimer();
				flagEstado=106;	
			}
		}
			
		if(flagEstado==402){
			if (despresa==1){
				tempos[passag]=(int32)timeCounter;
				tempos2[passag]=timeCounter2;
				passag++;
				timeCounter=0;
				timeCounter2=0;
				if (passag==10){
					sensores_desab();
					stopTimer();
					flagEstado=106;	
				}
				despresa=0;
			}else{
				despresa=1;
			}
		}
		
		if (flagEstado==503){
			tempos[0]=timeCounter;
			tempos2[0]=timeCounter2;
			stopTimer();
			//Modo=2;
			flagEstado=504;
			setup_adc( ADC_OFF );
				
		}
	
		if(flagEstado==702){
				
					tempos[passag]=(int32)timeCounter;
					tempos2[passag]=timeCounter2;
					passag++;
					if (passag==10){
						passag2=0;
						passag=0;
						flagEstado=703;	
						if(Func==7){
							disable_interrupts(INT_EXT);
							flagFimS0=1;
						}
					}
			
		}
		if(flagEstado==703){
				if(Func==8){
						S0vtempos[passag]=(int32)timeCounter;
						S0vtempos2[passag]=timeCounter2;
						passag++;
						if (passag==10){
							
							disable_interrupts(INT_EXT);
							flagFimS0=1;
						}
				}			
		}
	
}

///////////////////////////////////////////////////////////////
//             TIMER 1
//	cronometragem de eventos dos sensores
// incrementa timeCounter a cada 1ms

#int_timer1                     
void clock1_isr() {				
	
	
	set_timer1(65284);		/// 50us	
	//set_timer1(65000);
	if(timeCounter==10000)
	{
		timeCounter=0;
		timeCounter2=timeCounter2+1;
	}
	timeCounter=timeCounter+5;
	centmili=centmili+5;
	
	if (centmili==10)
	{
		centmili=0;
		decmili++;
		if (decmili==10)
		{
			decmili=0;
			mili++;
			if (mili==10)
			{
				mili=0;
				centi++;
				if (centi==10)
				{
					centi=0;
					deci++;
					
					if (deci==10)
					{
						deci=0;
						sec++;
						if (sec==10)
						{
							sec=0;
							decisec++;
							//Adicionado teste para a variavel decisec
							//zerar apos chegar a 10
							//Fabio Bairros - 22/01/2014
							if(decisec == 10)
							{
								decisec = 0;
							}
						}
					}
				}
			}
		}
	}
}


//----------------------------------FIM INTERRUPCAO-----------------------------------




void main()
{
   int1 loop;
  

	enable_interrupts(GLOBAL);
	setup_adc_ports(NO_ANALOGS);
	setup_adc(ADC_OFF);
	setup_psp(PSP_DISABLED);
	setup_spi(SPI_SS_DISABLED);
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
 
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_1 );
 	setup_timer_1(T1_DISABLED);
	//setup_timer_2( T2_DIV_BY_16, 0xFF, 16);
	setup_timer_2(T2_DISABLED,0,1);

// INICIALIZA LCD
   lcd_init();
	
	
// TELAS INICIAIS  comentadas devido ao tamanho do software
	loop=1;
    
// INICIALIZA TECLADO    
   flagTeclado=0;
	
	Modo=0;			// inicial
	flag_funcao_5 = 0;

	telaInicial_1();
	delay_ms(2000);
	while (loop){
		tela990();
		verificaTeclado();
		loop=selecEstado990(tecla_valida);
	}
	
	telaInicial_2();
	delay_ms(2000);

	flagTeclado=0;
	loop=1;
	tela0();
    flagEstado=0;
	tecla_valida='2';
	while (loop){
		
		verificaTeclado();
		if(tecla_valida=='B'){
			Modo=0;
			flag_funcao_5 = 0;
			flagTeclado=0;
			flagEstado=0;
			stopTimer();
			modo0_zera_valores();
		}
		if (Modo==0){
			EstadoModo0(flagEstado);
		}else if(Modo==1){
			EstadoModo1(flagEstado);
		}else if(Modo==2){
			EstadoModo2(flagEstado);
		}

		if(flagEstado==0){
			stopTimer();
		}

	}
}