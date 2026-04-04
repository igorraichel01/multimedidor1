/********************************** NOME DO MODULO *******************************************//**
 *\file      HdsComm.cpp

 Interface com o hardware para comunicacao serial.
 Configura o clock da porta usada
 configura a função que o pino irá executar
 Configura  interrupçoes
 Rotinas de recepção e transmissão

 *\brief     Interface com o hardware de comunicacao serial
 *            
 * ----------------------------------------------------------------------------------------------
 * \version   1.00 - 
 * \date      01/04/2021
 * ----------------------------------------------------------------------------------------------

 ************************************************************************************************/

/*************************************************************************************************
 Modulos incluidos
 *************************************************************************************************/
#include "HdsComm.h"
#include "HdsGpio.h"
#include "HdsMux.h"
#include <stdio.h>

/*************************************************************************************************
 Prototipos de funcoes locais
 *************************************************************************************************/

/*************************************************************************************************
 Diretivas de pre-processador
 *************************************************************************************************/

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
TSerialComm Serial;

uint8_t debugbuffer[500];

/*************************************************************************************************
 Inicio do codigo
 *************************************************************************************************/

/*********************************************************************************************//**
 * \function        ConfigurePins
 * \details    Configura os pinos para serem utilizados como porta de comunicação

 * \author    
 * \date       01/04/2021
 
 //usart2 tx PA2,PD5,PB3 
 //usart2  Rx PA3,PD6,PB4 
 
 //usart3 tx PB10,PD8,PC10,PB8
 
 //usart3  tx PC10
 //usart3  Rx PB11,PD9,PC11,PE15, 
 
 ************************************************************************************************/
void TSerialComm::_ConfigurePins() {

		
			//!Habilita o clock para a Uart
			//RCC->APB1ENR2 |= RCC_APB2ENR_USART1EN;
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

			//Habilita o clock para a porta ( provavelmente já foi habilitado pelo HdsGpio)
			RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

			//!Configura os pinos para RX
			Gpio.GpioCfg(UART1_RX, PULL_UP, PORT_ALTERNATE, PORT_PUSH_PULL, PORT_LOW_SPEED);
    	Gpio.GpioCfg(UART1_TX, PULL_UP, PORT_ALTERNATE, PORT_PUSH_PULL, PORT_LOW_SPEED); 		

/*
	//para configurar essa função ver "Appendix_I_Alternate_Functions.pdf"
			//byte baixa configura portas de 0 a 7, parte alta de 8 a 15	
			if (Gpio.GetPinNumber(UART1_RX_PIN) <= 7) {
				UART1_RX_PORT->AFR[0] &= ~(GPIO_AF15_EVENTOUT << (Gpio.GetPinNumber(UART1_RX_PIN) * 4));    //Zera o que tinha antes
				UART1_RX_PORT->AFR[0] |= (GPIO_AF7_USART1 << (Gpio.GetPinNumber(UART1_RX_PIN) * 4));    //configura com usartRX o pino
      }
			 else{
				UART1_RX_PORT->AFR[1] &= ~(GPIO_AF15_EVENTOUT << ((Gpio.GetPinNumber(UART1_RX_PIN) - 8) * 4));    //Zera o que tinha antes
				UART1_RX_PORT->AFR[1] |= (GPIO_AF7_USART1 << ((Gpio.GetPinNumber(UART1_RX_PIN) - 8) * 4));    //configura com usartRX o pino
			 }				 
				
			//!Configura os pinos para TX


			//para configurar essa função ver "Appendix_I_Alternate_Functions.pdf"
			if (Gpio.GetPinNumber(UART1_TX_PIN) <= 7) {
				UART1_TX_PORT->AFR[0] &= ~(GPIO_AF15_EVENTOUT << (Gpio.GetPinNumber(UART1_TX_PIN) * 4));    //Zera o que tinha antes
				UART1_TX_PORT->AFR[0] |= (GPIO_AF7_USART1 << (Gpio.GetPinNumber(UART1_TX_PIN) * 4));     //configura com usartRX o pino
			 }
			 else{
				UART1_TX_PORT->AFR[1] &= ~(GPIO_AF15_EVENTOUT << ((Gpio.GetPinNumber(UART1_TX_PIN) - 8) * 4));    //Zera o que tinha antes
				UART1_TX_PORT->AFR[1] |= (GPIO_AF7_USART1 << ((Gpio.GetPinNumber(UART1_TX_PIN) - 8) * 4));     //configura com usartRX o pino
			 }
			break;

*/

}

/*********************************************************************************************//**
 * \function         Init
 * \details    Inicializacao da porta, pode ser qualquer uma das portas serias

 * \author
 * \date       01/04/2021

 ************************************************************************************************/
void TSerialComm::Init(EPorts Com, uint32_t ulBaud) {



	//Configura os pinos dessa serial
	_ConfigurePins();



		   //Configura os parâmetros da serial  14522  9600baud / 8 bits
			USART1->BRR = 48000000L / ulBaud;
		
			//! Habilita interrupção de erro
			USART1->CR3 = USART_CR3_EIE;

			//! 8 data bit, 1 start bit, 1 stop bit, sem paridade,
			USART1->CR1 = 0;
		  
		  //! Habilita USART,  transmissao e recepção
			USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
		
		 //!Limpar qualquer int pendente
			USART1->ISR = 0;
			
			//Atribui o endereço aos ponteiros
			Port.pUsart_SR = (uint32_t *) &USART1->ISR;
			Port.pUsart_CR1 = (uint32_t *) &USART1->CR1;
			Port.pUsart_IDR = (uint32_t *) &UART1_RX_PORT->IDR;     //! Para leitura da porta
			Port.pUsartRxPin = UART1_RX_PIN;      //! Para leitura do pino
			Port.pTXREG = (uint32_t *) &USART1->TDR;
			Port.pRXREG = (uint32_t *) &USART1->RDR;

			//habilita as interrupções
			NVIC_SetPriority(USART1_IRQn, 5);
			NVIC_EnableIRQ (USART1_IRQn);

				

			_InitPort(DISABLED);
		
}


/*********************************************************************************************//**
 * \function         _InitPort
 * \details    Configura os parametros de comunicação, como tamanho dos buffers e tempos  de timeout

 * \author
 * \date       01/04/2021
 ************************************************************************************************/
void TSerialComm::_InitPort(ECommState uiState) {

			Port.PortState = uiState;                 	//!<Estado inicial = FREE.
			Port.pRxBaseAdd = &_ucRxBuf[0];        		//!<Aponta para buffer de recepção
			Port.uiRxBufSize = RX_SIZE;          		//!<Tamanho do buffer de rx
			//Port.pRxCurrentStart = Port.pRxBaseAdd;
			Port.pRxCurrentPointer = Port.pRxBaseAdd;
			Port.uiBytesReceived = 0;
			Port.uiRxTimeOut = RX_END_FRAME_TIMEOUT;
			//Port.Bits.SyncControl = 1;                    //!<indicate control of idle-line time.
			//Port.Bits.RXAutoStart = 1;

			Port.pTxBaseAdd = &_ucTxBuf[0];
			Port.uiTxBufSize = TX_SIZE;
			Port.pTxFrameStart = Port.pTxBaseAdd;
			Port.pTxCurrentPointer = Port.pTxBaseAdd;
	
}

/*********************************************************************************************//**
 * \function         StartTx
 * \details   Inicializa a transmissao na porta serial associada
 * \author
 * \date       01/04/2021
************************************************************************************************/
void TSerialComm::StartTx() {

//! Desabilita interrupição de RX.
	*Port.pUsart_CR1 &= ~USART_CR1_RXNEIE;

//! Indica que esta enviando dados
	Port.PortState = SENDING;

 //! Ponteiro para inicio da transmissão      
	Port.pTxCurrentPointer = Port.pTxFrameStart;
	
//! Envia primeiro byte
	*Port.pTXREG = (uint8_t)(*Port.pTxCurrentPointer & (uint8_t) 0x00FF);

//! Inicializa contador de bytes enviados
	Port.uiBytesSent = 1;

//! Incrementa o ponteiro de transmissão

	Port.pTxCurrentPointer++;

//! Enable TX interrupt.
	*Port.pUsart_CR1 |= USART_CR1_TXEIE;
	_EnableTx();

}

/*********************************************************************************************
* \function      ProcessTXInterruption
* \details    Processa o byte recebido
* 			  pode ser chamada pela int de final de byte transmitido
* 			  pode ser chamada pela int de buffer tx vazio
*

* \param
* \author
* \date       08/04/2021
*************************************************************************************************/
void TSerialComm::ProcessTXInterruption() {

//! Tests if has finished the trasnmission
if (Port.uiBytesSent >= Port.uiTxFrameSize) {

	//! Desabilita int de TX.
	*Port.pUsart_CR1 &= ~USART_CR1_TXEIE;


	//!Prepara Recepção
	_ResetRxPointers();

	//! Habilita RX novamente.
	*Port.pUsart_CR1 |= USART_CR1_RXNEIE;
  
		//! Seta estado para esperar uma resposta ou timeou
	 Port.PortState = WAITING_TIMEOUT;
   _ulmilliSecondTimeout = MuxTimers.GetMsTicks();

	

}
else {

	//! Envia byte e incrementa ponteiro
	*Port.pTXREG = (uint8_t)(*Port.pTxCurrentPointer & (uint8_t) 0x00FF);

	Port.pTxCurrentPointer++;

	Port.uiBytesSent++;
 }

}

/*********************************************************************************************//**
* \function    ProcessRXInterruption
* \details     Atende a interrupção de recepção da porta serial
* 			   Recebe o byte e insere no buffer.
* 			   reseta o contador de timout de ultimo byte recebido

* \param
* \author
* \date       09/04/2021
*************************************************************************************************/
void TSerialComm::ProcessRXInterruption() {

	if (Port.uiBytesReceived < Port.uiRxBufSize) {

		Port.PortState = RECEIVING;

		//! Inclui o byte no buffer de recepção
		*Port.pRxCurrentPointer = (uint8_t) * Port.pRXREG;

		//! Incrementa o ponteiro
		_IncRxCircularPointer();

		//! Incrementa o número de bytes recebidos
		Port.uiBytesReceived++;

		//Comparador  para timeout do ultimo byte recebido
		_ulmilliSecondTimeout = MuxTimers.GetMsTicks();

	}
	else {

		//Ocorreu erro, tratado em uma camada acima
		Port.PortState = CERROR;
        
        //! para liberar a serial
        __IO uint8_t dummy= (uint8_t) * Port.pRXREG;
        

	}

}


 /*********************************************************************************************//**
 * \function      SerialPortMonitoring
 * \details    Monitora o estado da porta, deve ser chamada por uma base de tempo
 * 			   Dependendo do Estado pode tomar alguma ação ( erro por exemplo)
 * 			   Monitora o timeout de recepção de dados

 * \param
 * \author
 * \date       09/04/2021
 *************************************************************************************************/
ECommState TSerialComm::SerialPortMonitoring() {

	switch (Port.PortState) {
		case CERROR:
			break;

		case RECEIVING:
			//! Nesse estado monitora a recepção, se ocorreu timeout após a recepção do ultimo byte sinaliza com frame valido
			if (MuxTimers.GetMsTicks() - _ulmilliSecondTimeout > Port.uiRxTimeOut) {
				  
				//!Salva a quantidade de bytes recebidos 
				Port.uiRxFrameSize=Port.uiBytesReceived;
				
				//! 
				Port.pRxFrameStart = Port.pRxBaseAdd; //  Port.pRxCurrentStart;
								
				Port.PortState = VALID_FRAME;
			}
			break;
		
		case VALID_FRAME:
			break;
		
		case WAITING_TIMEOUT:
		    //! Aguarda uma resposta ou ACK/NAK 
			if ((MuxTimers.GetMsTicks() - _ulmilliSecondTimeout) > Port.uiAnswerTimeout) {
				 Port.PortState = TIMEOUT;
			} 	
    		break;
		
		case FREE:
			break;
		case SENDING:
			break;
		case DISABLED:
			break;
		case TIMEOUT:
			break;

		default:
			break;
	}
	return Port.PortState;
}


/*********************************************************************************************
* \function      _FlushRx
* \details    Lê os dados do buffer RX caso existam

* \param
* \author
* \date       09/04/2021
************************************************************************************************/
uint8_t TSerialComm::_FlushRx() {

	uint8_t ucDummy;

	uint8_t ucCount = 0;

	do {

		ucDummy = (uint8_t) * Port.pRXREG;     //!< Le da uart

	} while ((++ucCount < 3));

	return (ucDummy);
}


/*********************************************************************************************
* \function      InitRx
* \details     Prepara a porta para a recepcao de dados

* \param
* \author
* \date       09/04/2021
************************************************************************************************/
void TSerialComm::InitRx() {

	//! Desabilita a int de RX .
	*Port.pUsart_CR1 &= ~(USART_CR1_RXNEIE);

	//! Garante limpeza da UART ao reabilitar RX.
	_FlushRx();

	//! Inicia os ponteiros de RX.
	_ResetRxPointers();

	//! Enable RX interrupt.
	*Port.pUsart_CR1 |= USART_CR1_RXNEIE;

	//!habilita a recepção
	_EnableRx();

	//! Sinaliza porta disponível
	Port.PortState = FREE;
}


/*********************************************************************************************
 * \function      ResetTxPointers
 * \details     Reinicia ponteiros de transmissao para o inicio dos buffers

 * \param
 * \author
 * \date       09/04/2021
 *********************************************************************************************/
void TSerialComm::ResetTxPointers() {
	Port.pTxFrameStart = Port.pTxBaseAdd;
	Port.pTxCurrentPointer = Port.pTxFrameStart;
	Port.uiBytesSent=0;
	}

/*********************************************************************************************
 * \function      ResetRxPointers
 * \details     Reinicia ponteiros de recepçao para o inicio dos buffers

 * \param
 * \author
 * \date       09/04/2021
 *********************************************************************************************/
void TSerialComm::_ResetRxPointers() {
	Port.pRxFrameStart = Port.pRxBaseAdd;
	Port.pRxCurrentPointer = Port.pRxFrameStart;
	Port.uiBytesReceived=0;
    Port.pRxCurrentPointer=Port.pRxBaseAdd;

}


 /*********************************************************************************************
 * \function      _IncRxCircularPointer
 * \details      Incrementa ponteiro circular de recepcao

 * \param
 * \author
 * \date       09/04/2021
 *********************************************************************************************/
void TSerialComm::_IncRxCircularPointer() {

	Port.pRxCurrentPointer++;

	if (Port.pRxCurrentPointer >= (Port.pRxBaseAdd + Port.uiRxBufSize)) {
		Port.pRxCurrentPointer = Port.pRxBaseAdd;
	}

	return;
}

/*********************************************************************************************
 * \function      SendBuffer
 * \details    Escreve um buffer pela serial

 * \param      ponteiro com os dados a serem transmitidos, tamanho dos dados
 * \author
 * \date       09/04/2021
 *********************************************************************************************/
void TSerialComm::SendBuffer(uint8_t * buf, uint16_t ulsize) {

uint16_t i;

	//!passa os dados para o buffer interno da classe
	for (i = 0; i < ulsize; i++) {
		Port.pTxBaseAdd[i] = buf[i];
	}

	//! Aponta para o inicio do buffer
	ResetTxPointers();

	//Bytes para enviar
	Port.uiTxFrameSize = ulsize;

	//inicia a trasmissão
	StartTx();

}


/*********************************************************************************************
 * \function      SendDebug
 * \details    Rotina para debug 

 * \param      
 * \author
 * \date       20/08/2021
 *********************************************************************************************/
void TSerialComm::SendDebug(uint8_t * buf, uint16_t ulsize) {

#ifdef DEBUG_SERIAL 
    
	SendBuffer(buf,ulsize);

#endif     

}



/*********************************************************************************************//**
 * \function      GetState
 * \details    Retorna o estado da porta de comunicação

 * \param
 * \author
 * \date       08/04/2021
  *************************************************************************************************/
ECommState TSerialComm::GetState() {
	return Port.PortState;
}

/*********************************************************************************************
 * \function      GetRxlen
 * \details    Retorna o tamanho dos dados recebidos

 * \param
 * \author
 * \date       08/04/2021
  *************************************************************************************************/
uint16_t TSerialComm::GetRxlen() {
	return Port.uiBytesReceived;
}


/*********************************************************************************************
* \function      GetRxPtrBuffer
* \details    Retorna o um ponteiro para o endereço inicial da recepção

* \param
* \author
* \date       08/04/2021
*************************************************************************************************/
uint8_t * TSerialComm::GetRxPtrBuffer(){
	return Port.pRxBaseAdd;
}

void TSerialComm::_EnableRx() {
   //!habilita a recepção
*Port.pUsart_CR1 |= USART_CR1_RE;
}

void TSerialComm::_DisableRx() {
//!Desabilita a recepção
*Port.pUsart_CR1 &= ~USART_CR1_RE;

}

void TSerialComm::_EnableTx() {
	//!Habilita a transmissão
	*Port.pUsart_CR1 |= USART_CR1_TE;
}

void TSerialComm::_DisableTx() {
//!Desabilita a transmissão
	*Port.pUsart_CR1 &= ~USART_CR1_TE;		
}



/*********************************************************************************************//**
 * \fn         USART1_IRQHandler
 * \details    Método que trata as interrupções da porta de comunicação serial. (porta optica)
 * \author     
 * \date       05/04/2021
 ************************************************************************************************/
extern "C" void USART1_IRQHandler(void) {

	uint32_t isrflags = USART1->ISR;
	uint32_t cr3its = USART1->CR3;
	uint32_t errorflags = 0x00U;

	//! Verifica algum erro na Uart	
	errorflags = (isrflags & (uint32_t)(USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE));
		
	/* If some errors occur */
	if ((errorflags != RESET) && (cr3its & USART_CR3_EIE) != RESET) {
		/* UART noise error interrupt occurred -----------------------------------*/
		if ((isrflags & USART_ISR_NE) != RESET) {
			USART1->ICR |= USART_ICR_NCF;
		}
		
		/* UART frame error interrupt occurred -----------------------------------*/
		if ((isrflags & USART_ISR_FE) != RESET) {
			USART1->ICR |= USART_ICR_FECF;
		}
		
		/* UART Over-Run interrupt occurred --------------------------------------*/
		if ((isrflags & USART_ISR_ORE) != RESET) {
			USART1->ICR |= USART_ICR_ORECF;
		}

		//sinaliza que houve erro
		Serial.Port.PortState = CERROR;
	}

	//! Read Data Register Not Empty  (Recebeu 1 byte)
	if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE) {
		//! Limpa flag de sinalização de erro
		USART1->ISR &= ~USART_ISR_RXNE;
		Serial.ProcessRXInterruption();
		return;
	}

	//! Transmit data register empty
	if (((USART1->ISR & USART_ISR_TXE) == USART_ISR_TXE) && ((USART1->CR1 & USART_CR1_TXEIE) == USART_CR1_TXEIE)) {
		//! Limpa flag de sinalização de erro
		USART1->ISR &= ~USART_ISR_TXE;
		Serial.ProcessTXInterruption();
		return;
	}

	//! Transmission Complete  
	if (((USART1->ISR & USART_ISR_TC) == USART_ISR_TC) && ((USART1->CR1 & USART_CR1_TCIE) == USART_CR1_TCIE)) {
		//! Limpa flag de sinalização de erro
		USART1->ICR |= USART_ICR_TCCF;
		return;
}

	//! Character match flag
	if ((USART1->ISR & USART_ISR_CMF) == USART_ISR_CMF) {

		USART1->ICR |= USART_ISR_CMF;
	}
}





