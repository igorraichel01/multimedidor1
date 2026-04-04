 /********************************** NOME DO MODULO *******************************************//**
*\file     HdsGPIO.cpp
 
*\details   Módulo que controla a configuração dos pinos de I/O do micro 
*             
*          

* ----------------------------------------------------------------------------------------------
* \version   s.00 - Primeira versão documentada
* \date      24/03/2021
***********************************************************************************************/
#include "HdsGpio.h"

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_Gpio Gpio;



/*********************************************************************************************//**
 * \fn         Init
 * \details    configura o uso do GPIO
				habilita clock para as portas, configura o modo de operação de cada porta 
 * \author     
 * \date        24/03/2021
 ************************************************************************************************/
void C_Gpio::Init(void)
{
  //Habilita o clock para as portas
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;   //PORTA A
//	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;   //PORTA B
//    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;   //PORTA C
//    RCC->AHBENR |= RCC_AHBENR_GPIODEN;   //PORTA D
//	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;   //PORTA F
	
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  





	//! configura o modo de operação de cada pino 
	_ConfigPin();  
	
//!Configura o estado inicial de cada pino
//	Write(LedAtivo,ePortHigh);
//	Write(LedReativo,ePortHigh);

 //  Write(Buzzer,ePortLow);
	
	
}

/*********************************************************************************************//**
 * \fn         ConfigPin
 * \details    configura o modo de operação de cada pino.
								Pinos de gpiio são configurados aqui, pinos de uart, Ad são configurados nos módulos especificos
				
 * \author     
 * \date        24/03/2021
 ************************************************************************************************/
void C_Gpio::_ConfigPin(void)
{
  
	//!Parametros:  Porta e respectivo pino, pull up/pulldown/nenhum, entrada/saida, push pull/open drain, low/medium/high speed 
	
	 //!Buzzer
	GpioCfg(Led,PULL_UP,eGPIOOutput,PORT_OPEN_DRAIN,PORT_LOW_SPEED);
	
   //!Buzzer
//	GpioCfg(Buzzer,PULL_UP,eGPIOOutput,PORT_PUSH_PULL,PORT_LOW_SPEED);

    //botao liga
    GpioCfg(BtLiga,PULL_UP,eGPIOInput,PORT_PUSH_PULL,PORT_LOW_SPEED);

    GpioCfg(PowerON,PULL_UP,eGPIOOutput,PORT_PUSH_PULL,PORT_LOW_SPEED);


    //Deixa a placa ligada
    Write(PowerON,ePortHigh);

}

/*********************************************************************************************//**
 * \fn         GpioCfg
 * \details    configura o modo de operação da porta
							 Porta e respectivo pino, pull up/pulldown/nenhum, entrada/saida, push pull/open drain, low/medium/high speed 
	
 * \author     
 * \date        24/03/2021
 ************************************************************************************************/
void C_Gpio::GpioCfg(GPIO_TypeDef * Porta, uint16_t uiPin, EPortResistor eResistor,EPortmode emode,EPortOut eOut,  EPortSpeed eSpeed)
{
	uint16_t uiPosition= 0x00;
	
	//!Busca a posição do Pino
	uiPosition= GetPinNumber(uiPin);
			
	Porta->PUPDR&=~(0x03<<((uiPosition)*2U));  //Zera o valor anterior 
	Porta->PUPDR|=eResistor<<((uiPosition)*2U);
	
	Porta->MODER&=~(0x03<<((uiPosition)*2U));  //Zera o valor anterior 
	Porta->MODER|=emode<<((uiPosition)*2U);
	
	Porta->OTYPER&= ~(0x1<<(uiPosition));   //Zera o valor anterior 
	Porta->OTYPER|=eOut<<(uiPosition);
	
	Porta->OSPEEDR&=~(0x03<<((uiPosition)*2U));  //Zera o valor anterior 
	Porta->OSPEEDR|=eSpeed <<((uiPosition)*2U);
}
	
	

/*********************************************************************************************//**
 * \fn         Write
 * \details    Escreve na porta, bits 0 a 15 setam o pino 
							bits 16 a 31 resetam o pino  
 * \author     
 * \date        24/03/2021
 ************************************************************************************************/
void C_Gpio::Write(GPIO_TypeDef * Porta, uint16_t uiPin,EPortState eState)
	{
		
		if(eState==ePortHigh){
			Porta->BSRR = uiPin;    //! escreve 1 na porta 
		}
		else{
			Porta->BSRR=uiPin << NUM_GPIO;   //! escreve 0 na porta 
		}
		
	}
	
	
	
/*********************************************************************************************//**
 * \fn         Read
 * \details    Lê o estado do pino 
							 Retorna true para nivel alto e false para nivel baixo
							 
 * \author     
 * \date        25/03/2021
 ************************************************************************************************/
bool C_Gpio::Read(GPIO_TypeDef * Porta, uint16_t uiPin)
	{
		
	bool bPinstatus;	
	
		
  if((Porta->IDR & uiPin) )
  {
    bPinstatus = true;
  }
  else
  {
   bPinstatus = false;
  }
  return bPinstatus;
		
}		
		
/*********************************************************************************************//**
 * \fn         Toggle
 * \details    troca o estado do pino selecinado  
							  
 * \author     
 * \date        24/03/2021
 ************************************************************************************************/
void C_Gpio::Toggle(GPIO_TypeDef * Porta, uint16_t uiPin){

  if ((Porta->ODR & uiPin) == uiPin)
  {
    Porta->BSRR = (uint32_t)uiPin << NUM_GPIO;
  }
  else
  {
    Porta->BSRR = uiPin;
  }
}


/*********************************************************************************************//**
 * \fn         GetPinNumber
 * \details    Retorna o número do pino
							 Recebe a posição 0x01, 0x08, 0x0100...
							 retorna o numero  0, 3 , 8
							  
 * \author     
 * \date        01/04/2021
 ************************************************************************************************/
uint16_t C_Gpio::GetPinNumber(uint16_t uiPin){

  uint16_t uiRet;
	
    switch(uiPin){
			case GPIO_PIN_0:  uiRet=0;break;                 
			case GPIO_PIN_1:  uiRet=1;break;                     
			case GPIO_PIN_2:  uiRet=2;break;                     
			case GPIO_PIN_3 :  uiRet=3;break;                    
			case GPIO_PIN_4 :  uiRet=4;break;                    
			case GPIO_PIN_5 :  uiRet=5;break;                   
			case GPIO_PIN_6 :  uiRet=6;break;                    
			case GPIO_PIN_7 :  uiRet=7;break;                    
			case GPIO_PIN_8:  uiRet=8;break;    
			case GPIO_PIN_9 :  uiRet=9;break;    
			case GPIO_PIN_10:  uiRet=10;break;    
			case GPIO_PIN_11:  uiRet=11;break;    
			case GPIO_PIN_12 :  uiRet=12;break;    
			case GPIO_PIN_13:  uiRet=13;break;    
			case GPIO_PIN_14:  uiRet=14;break;    
			case GPIO_PIN_15 :  uiRet=15;break;    
			
			default: uiRet=0; break;
			
			
		}
		
return uiRet;		
		
}		
	
	
	
  




  



