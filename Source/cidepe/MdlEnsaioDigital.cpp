/********************************** NOME DO MODULO *******************************************//**
 *\file     MdlLcd.cpp
 
 *\details   M�dulo para controle das telas do LCD
 *		
 *

* ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira vers�o documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "MdlEnsaioDigital.h"
#include "Modo0.h"
#include "HdsTeclado.h"
#include "MdlMSG.h"
#include "MdlSensor.h"

#include "KBD2.h"

/* Forward declarations for functions defined in Fluxo.c */
extern "C" void stopTimer(void);
extern "C" void modo0_zera_valores(void);


/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Digital EnsaioDigital;



/*********************************************************************************************//**
 * \function        init
 * \details   Inicializa o m�dulo 

 * \author     
 * \date         08/01/2022
 ************************************************************************************************/
void C_Digital::Init(void) {
   
  _eState=DIG_START;
	
	//! Inicializa os sensores
	SensorDigital.Init();
	
  
 }

 #define 			TEMPO_TELA 2
 
 /*********************************************************************************************//**
 * \function        Run
 * \details   Avan�a os estados da maquina de estados do ensaio do sensor  
							chamada a cada 100ms
 * \author     
 * \date         08/01/2022
 ************************************************************************************************/
void C_Digital::Run(void) {
bool bBit;	
	
	
	switch(_eState){
		case DIG_START:
			telaInicial_1();
		  _uiTimedelay=0;
		
		  _eState=DIG_WAIT_TELA_INICIAL;
	  	break;
		
		case DIG_WAIT_TELA_INICIAL:
			if(_uiTimedelay++>TEMPO_TELA){
				  _eState=DIG_WAIT_IDIOMA;
				 //!Mosgra tela de sele��o de idioma
				 tela990();
				
			   }
	   break;
		
		case DIG_WAIT_IDIOMA:
			 tecla_valida=Teclado.GetTecla();
		   
		   if(selecEstado990(tecla_valida)){
				  telaInicial_2(); //** CRONOMETRO **" 
				  _eState=DIG_WAIT_TELA_INICIAL_2;
				  _uiTimedelay=0;   
			  }
		  break;
			 
		case DIG_WAIT_TELA_INICIAL_2:
  	   if(_uiTimedelay++>TEMPO_TELA){
				  tela0(); 		// ESCOLHA A FUNCAO 
				 _eState=DIG_RUN;
				 
				 tecla_valida=M_FUNC;  //para entrar direto na tela de sele��o dos sensores
				 EstadoModo0(flagEstado);
			   }

			break;	
			 
			 
			 
		
	case DIG_RUN:
	
     //! 	Le a tecla para o proximo estado 
		 tecla_valida=Teclado.GetTecla();

	   //if(tecla_valida!= KEY_NONE_PRESSED){
	
			if(tecla_valida== RESET ){
					Modo=0;
					flag_funcao_5 = 0;
					flagTeclado=0;
					flagEstado=0;
					stopTimer();
					modo0_zera_valores();
				}
					
					//	do{
						if (Modo==0){
							bBit=EstadoModo0(flagEstado);
						}else if(Modo==1){
							bBit=EstadoModo1(flagEstado);
						}else if(Modo==2){
							bBit=EstadoModo2(flagEstado);
						}

						if(flagEstado==0){
							stopTimer();
						}
					tecla_valida= KEY_NONE_PRESSED;
				//	}while (bBit);   //se retornou 1 repete o loop
				
		
		//	}
		
	
		
			break;
	case DIG_DONE :
			
			break;
	}
}

