#ifndef _MDL_SENSOR_ANALOG_
#define _MDL_SENSOR_ANALOG_

#include "InventTypes.h"
#include <stdint.h>
#include "MdlCalib.h"


#define NUM_SAMPLES    2500   //amostras de 16 bits




typedef enum {
    eTestIdle,
    eTestStart, 
    eTesteRun, 
    eTestDone
} eTestState;

typedef enum {
    eExcutionTime, 
    eSampleTime,    
    eRunningTime, //Tempo de teste, contador decrescente
    eNumValues
} eSensorTime;

typedef enum {
    eMaximumExcutionTime,
    eMinimumSampleTime,
    eMaximumRunningTime,   
    eNumLimitsValues
} eSensorLimits;

typedef enum{
	eCalibValueLow,
	eCalibValueHigh,
	//eCalibPressureLow,
   // eCalibPressureHigh, 
	eCalibMaxSensor
}eCalibIndex;

class C_SensorAnalog {
private:
    int8_t _scSensorType;    // Tipo de sensor

    uint16_t _uiTimeValue[eNumValues]; // Tempo de amostragem do sensor em ms ou tempo de ensaio
    uint16_t _uiTimeLimit[eNumValues]; // Limite dos tempos 
    uint16_t  _uiNumSamples;           // Numeo de amostras esperadas 
   
    eTestState _eTestState;  //estado da maquina de estados 
    
    int8_t _scPosicaoDigito;  //Posição do digito para a entrada de dados
    
    uint16_t _uiSamples[NUM_SAMPLES];   //bufer de salvamento das amostras
   
    uint8_t  IndexMuxTimer;    //!indice do Muxtimer 

    uint16_t uiBufIndex;    //  Indice de entrada no buffer

    bool  bSensorEnabled;   //Sensor habilitado 

    uint16_t _uiLastSample;   // Ultima leitura desse sensor 

    int16_t iCalib[eCalibMaxSensor];   //!Valores de Calibração

    SensorGain  _Gain;
   uint16_t _uiNEnsaio;
    
public:
     uint32_t _ulSamplesTmp;   //bufer de salvamento da amostra do AD

    //! Inicialização das variaveis do módulo
    void Init(uint8 ucindex);

    //! Leitura do intervalo de amostragem  ou tempo de amostragem
    uint16_t GetValue(eSensorTime eValue);

    //! Converte o valor de temperatura 
    float ConvertTemp(uint16_t uiSample);
    
    //! Converte o valor de pressão em Kpa sensor cl012B.01
    float ConvertPressureKpa(uint16_t uiSample);

     //!configura o tempo de teste 
    void SetTestTime(uint16_t uiValue); 

    //!configura o tempo de amostraem em ms 
    void SetSampleTime(uint16_t uiValue);

    //!Atualiza o intervalo de amostragem  ou tempo de teste /down
    void UpdateValue(uint8_t tecla, eSensorTime eValue);

    //! Atualiza o tipo de sensor
    void UpdateSensor(uint8_t tecla);

    //! Leitura do sensor configurado
    uint16_t GetSensor();
    //! Cofnigura o Sensor para a calibração
    void SetSensor(eSensorType Sensor); 

    //Verifica teste em execução
    bool IsRunnig();

    //! Sensor habilitado
    bool IsEnabled();

    //! Desabilita sensor 
    void Disabled(); 

    //! Insere amostra no buffer
    void AddToBuffer(uint32_t ulsample);

    //! Inicia o ensaio
    void Start(void);

    //!Executa o teste
    void Run();
    
    //! Salva o resultado do teste 
    bool SaveTest();

    //! Retorna a ultima leitura em formato de string
    void GetLastValue(uint8_t *ucPtrBuf); 
    
    //! ulima leitura do sensor em float
    float GetLastReading();
    //! ulima leitura do sensor em Tesnão
    float GetLastReadingVolts();
    //! 
    void UpdateCalibValue(uint8_t tecla, eCalibIndex eIndex);

    int16_t GetCalibValue(eCalibIndex eValue); 

    void SetCalibValue(eCalibIndex eValue, uint16_t uiValue);

};

extern C_SensorAnalog AnalogS0;
extern C_SensorAnalog AnalogS1;
extern C_SensorAnalog AnalogS2;
extern C_SensorAnalog AnalogS3;
extern C_SensorAnalog AnalogS4;

#endif 
