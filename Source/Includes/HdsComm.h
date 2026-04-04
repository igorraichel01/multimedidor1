#ifndef HdsCommH
#define HdsCommH

#include "InventTypes.h"

#define _DEBUG_SERIAL

//! Portas de comunicaçãp

//Porta optica UART 1
#define UART1_TX_PIN 	GPIO_PIN_4
#define UART1_TX_PORT   GPIOC
#define UART1_TX        UART1_TX_PORT,UART1_TX_PIN

#define UART1_RX_PIN 	GPIO_PIN_5
#define UART1_RX_PORT   GPIOC
#define UART1_RX        UART1_RX_PORT,UART1_RX_PIN


//Porta REMOTA 
#define UART3_TX_PIN 	GPIO_PIN_10
#define UART3_TX_PORT   GPIOC
#define UART3_TX        UART3_TX_PORT,UART3_TX_PIN

#define UART3_RX_PIN 	GPIO_PIN_11
#define UART3_RX_PORT   GPIOC
#define UART3_RX        UART3_RX_PORT,UART3_RX_PIN

//Porta SSU / Pcom UART 2
#define UART2_TX_PIN 	    GPIO_PIN_3
#define UART2_TX_PORT       GPIOB
#define UART2_TX            UART2_TX_PORT,UART2_TX_PIN



#define TX_SIZE        400        //!< Tamanho do buffer de transmissão da porta remota
#define RX_SIZE        400        //!< Tamanho do buffer de recepção da porta remota
#define RX_END_FRAME_TIMEOUT     5    //5ms




#define TIME_CONNECTION_OPTICAL_PORT         10    //! multiplo 10ms


//! Estado da porta serial
typedef enum {
	DISABLED,           //!< Porta nao configurada
	FREE,               //!< porta nao ativa
	RECEIVING,          //!< Porta esta recebendo caracteres
	VALID_FRAME,        //!< detectado um frame valido
	SENDING,            //!< enviando caracteres pela porta
	WAITING_TIMEOUT,    //!< Contagem de timeout.
	TIMEOUT,            //!< Uma ocorrencia de timeout
	CERROR             //!< Uma ocorrencia de erro
} ECommState;

//Estados da comunicação ABNT
typedef enum
{
  ABNT_WAIT_COMMAND, //
  ABNT_REPROCESS_COMMAND,
  ABNT_PROCESS_COMMAND,
  ABNT_WAIT_RESPONSE,
  ABNT_IDLE_LINE
} EProtocolAbntState;

typedef struct
{
 EProtocolAbntState State;
	uint8_t ucAction ; 
  uint8_t ucRetry;
} TDtl;


//! tipos de portas seriais
typedef enum {
	OPTICAL_PORT,      
	REMOTE_PORT,      
	SSU_PORT,
	NUM_ANBNT_PORTS
} EPorts;

//! tipos para desconexão
typedef enum {
	OPTICAL_WAIT_CONNECT,     //!< Para a contagem da desconexão
	OPTICAL_CONNECTED,          //!< Executa a monitoração da porta ótica
	OPTICAL_WAIT_DISCONNECT,     //!< Inicia a contagem da para desconexão da porta ótica
    OPTICAL_CLOSE_SESSION,       //!< para encerrar a sessão de comunicação 
	OPTICAL_DISCONNECTED

} TOpticalState;     
 

#pragma anon_unions
			
//! Define a estrutura que mapeia uma porta de comunicacao
typedef struct {
	ECommState PortState;  		//! Estado da porta de comunicação
	

	//! Recepção.
	uint8_t* pRxBaseAdd;             //!< Endereco base do buffer de recepção da porta de comunicação.
	uint16_t uiRxBufSize;            //!< Tamanho do buffer de recepção. Utilizado para gerenciar a fila circular
	uint8_t* pRxFrameStart;          //!< Ponteiro para um frame válido recebido
	uint16_t uiRxFrameSize;          //!< numero de bytes recebidos no frame apontado por pRxFrameStart
//	uint8_t* pRxCurrentStart;        //!< Ponteiro para o buffer de rx corrente
	uint8_t* pRxCurrentPointer;      //!< Ponteiro corrente para buffer de rx
	uint16_t uiBytesReceived;        //!< numero de bytes recebidos
	uint16_t uiRxTimeOut;            //!< Define o timeout de rx entre bytes (final de frame)
//	uint16_t uiSyncTimeout;          //!< Timeout apos a recepção dou transmissao de um frame
    uint16_t uiAnswerTimeout;          //!< Timeout para respota ou Ack 

	//! Transmissão.
	uint8_t* pTxBaseAdd;             //!< Pointer para o buffer de transmissao
	uint16_t uiTxBufSize;            //!< Tamanho do buffer de tx, utilizado para gerencia da fila circular
	uint8_t* pTxFrameStart;          //!<  Aponta para endereço de inicio do buffer de  tx
	uint16_t uiTxFrameSize;          //!< tamanho do frame a ser transmitido
	uint8_t* pTxCurrentPointer;      //!< Ponteiro atual para o buffer de transmissão
	uint16_t uiBytesSent;            //!< Quantidade de bytes enviados


	//! Registradores da Serial.
	uint32_t* pRXREG;                 //!< Endereço do UART Rx register.
	uint32_t* pTXREG;                 //!< Endereço do UART Tx register.

	uint32_t* pUsart_SR;		        //!< CTS LBD TXE TC RXNE IDLE ORE NF FE PE
	uint32_t* pUsart_CR1;				//!< OVER8 Reserved UE M WAKE PCE PS PEIE TXEIE TCIE RXNEIE IDLEIE TE RE RWU SBK
	uint32_t* pUsart_IDR;       		//!< Registro para leitura das portas
   	uint16_t pUsartRxPin;   			//!<  Pino utilizado para o Rx da serial


	// Flags.
	union {
		uint8_t ucValue;
		struct {
			uint8_t //RxOccured :1,   //!< Sinaliza bytes sendo recebidos
					//SyncControl :1,   //!< Controle to tempo de idle
					//Sync :1,          //!< Sinaliza a condição de sync, tempo de idle expirou
					//CountFinalTx :1, //!< Sinaliza que o timer está contando o tempo de término de transmissão
					//RXAutoStart :1,   //!< Auto-reinicio ativado após a transmissão
					PassWriting :1,   //!< Senha de escrita válida recebida
					PassReading :1,   //!< Senha recebida para leitura
					Free :6;
		} Bits;
	};

} TCommPort;

class TSerialComm {
private:

	uint64_t _ulmilliSecondTimeout;   //! usado para timeout da recepção

	//! Buffers de comunicacao
	uint8_t _ucTxBuf[TX_SIZE]; //!< Buffer de transmissão
	uint8_t _ucRxBuf[RX_SIZE]; //!< Buffer de recepção

	//!Configura os pinos do processador
	void _ConfigurePins(void);

	//! Incrementa ponteiro circular de recepcao
	void _IncRxCircularPointer();

	void _InitPort(ECommState uiState);

	//! Limpa a Uart RX
	uint8_t _FlushRx();

	//! Reinicia ponteiros de recepção
	void _ResetRxPointers();

	//! Habilita Recepção
	void _EnableRx();
	//! Desabilita  Recepção
	void _DisableRx();
	//! Habilita Transmissão
	void _EnableTx();
	//! Desabilita Transmissão
	void _DisableTx();

public:
  //! Estrutura da porta serial
	TCommPort Port;

  //! Estrutura do estado do comando 
   EProtocolAbntState   CmdState;

	//! Inicializa a porta remota
	void Init(EPorts Com, uint32_t ulBaud);
	//! Inicializa a transmissao na porta serial associada
	void StartTx();
	//! Prepara a porta para a recepcao de dados
	void InitRx();
	//! Processamento da interrupcao de transmissao 
	void ProcessTXInterruption();
	//! Processamento da interrupcao de recepcao 
	void ProcessRXInterruption();
	//! Monitoramento do funcionamento das portas seriais, deve ser chamada por timer
	ECommState SerialPortMonitoring();
	//! Reinicia ponteiros de transmissao para o inicio dos buffers
	void ResetTxPointers();

	//! Escreve um buffer pela serial
	void SendBuffer(uint8_t * buf, uint16_t ulsize);
    
    //! Rotina para debug pela serial 
    void SendDebug(uint8_t * buf, uint16_t ulsize); 

	//Retorna o estado do canal de comunicação
	ECommState GetState();

	//! Tamanho dos dados recebidos
	uint16_t GetRxlen();

	//!ponteiro para onde os dados estão armazenados.
	uint8_t * GetRxPtrBuffer();




};

//! Exporta classe para uso
//extern TSerialComm SerialComm;

extern TSerialComm RemotePort;
extern TSerialComm OpticalPort;
extern TSerialComm SsuPort;
extern uint8_t debugbuffer[500];


#endif

