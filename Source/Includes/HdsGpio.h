#ifndef __HDSGPIOH
#define __HDSGPIOH

#include <stdint.h>
#include "InventTypes.h"

//Definição dos pnos 

#define NUM_GPIO  16   //  Cada porta tem 16 pinos de I/O 

//!  IOs
#define LedPin     GPIO_PIN_3
#define LedPort    GPIOB
#define Led        LedPort,LedPin


#define BtLigaPin     GPIO_PIN_2
#define BtLigaPort    GPIOA
#define BtLiga        BtLigaPort,BtLigaPin


#define PowerONPin     GPIO_PIN_3
#define PowerONPort    GPIOA
#define PowerON        PowerONPort,PowerONPin

//! ******************* pinos de dados do LCD ***********************************
#define LcdD4Pin 	GPIO_PIN_12
#define LcdD4Port 	GPIOB
#define LcdD4   	LcdD4Port,LcdD4Pin

#define LcdD5Pin 	GPIO_PIN_13
#define LcdD5Port 	GPIOB
#define LcdD5   	LcdD5Port,LcdD5Pin

#define LcdD6Pin 	GPIO_PIN_14
#define LcdD6Port 	GPIOB
#define LcdD6   	LcdD6Port,LcdD6Pin

#define LcdD7Pin 	GPIO_PIN_15
#define LcdD7Port 	GPIOB
#define LcdD7   	LcdD7Port,LcdD7Pin

#define LcdRsPin 	GPIO_PIN_10
#define LcdRsPort 	GPIOA
#define LcdRs   	LcdRsPort,LcdRsPin

#define LcdRwPin 	GPIO_PIN_9
#define LcdRwPort	GPIOA
#define LcdRw   	LcdRwPort,LcdRwPin

#define LcdEnablePin 	GPIO_PIN_8
#define LcdEnablePort	GPIOA
#define LcdEnable   	LcdEnablePort,LcdEnablePin

#define LcdOnPin 	GPIO_PIN_6
#define LcdOnPort	GPIOA
#define LcdOn   	LcdOnPort,LcdOnPin




typedef enum {
    PORT_PUSH_PULL,  //0: Output push-pull (reset state)
    PORT_OPEN_DRAIN    //1: Output open-drain
} EPortOut;

typedef enum {
    NONE_RESISTOR,    //00: No pull-up, pull-down
    PULL_UP,					//	01: Pull-up
    PULL_DOWN,				//		10: Pull-down
    RESERVED					//11: Reserved
} EPortResistor;

typedef enum {
    eGPIOInput,    			//00: Input mode (reset state)
    eGPIOOutput,				//	01: General purpose output mode
    PORT_ALTERNATE,			//	10: Alternate function mode
    PORT_ANALOG					//11: Analog mode
} EPortmode;

typedef enum {
    PORT_LOW_SPEED,    //x0: Low speed
    PORT_MEDIUM_SPEED,  //01: Medium speed
    PORT_HIGH_SPEED     //11: High speed
} EPortSpeed;

typedef enum {
    ePortLow, ePortHigh
} EPortState;

class C_Gpio {
private:
    void _ConfigPin(void);

public:
    //! Inicializa a classe
    void Init(void);

    //! Aciona o pino com nivel alto ou baixo
    void Write(GPIO_TypeDef *Porta, uint16_t uiPin, EPortState eState);

    //! Lê o estado do Pino
    bool Read(GPIO_TypeDef *Porta, uint16_t uiPin);

    //! Troca o estado do pino
    void Toggle(GPIO_TypeDef *Porta, uint16_t uiPin);

    //! retorna o numero do pino
    uint16_t GetPinNumber(uint16_t uiPin);

    //Configura o modo de operação dos pinos
    void GpioCfg(GPIO_TypeDef *Porta, uint16_t uiPin, EPortResistor etype, EPortmode emode, EPortOut eOut, EPortSpeed eSpeed);

};

//! Declara como extern para ser usada por outros módulos 
extern C_Gpio Gpio;

#endif
