#ifndef _MDL_ENSAIO_ANALOGICO_
#define _MDL_ENSAIO_ANALOGICO_

#include "InventTypes.h"
#include "MdlSensorAnalog.h"

#include <stdint.h>

#define MOD(x) ((x)>=0?(x):-(x))

//#pragma anon_unions
typedef struct {
    union {
        uint8_t ucValue;
        struct {
            uint8_t S0 :1, S1 :1, S2 :1, S3 :1, S4 :1, Sx :3;

        };
    };
} bBits;

    


//!Mensagees dos Sensores Analógicos 
const char MSG_TIPO_SENSOR[3][17] =  {{"Analog   digital"}, {"Analog   digital"}, {"Analóg   digital"}};


const char MSG_INDICADOR_L1[3][17] =    {{"Modo de Operação"}, {"Operation mode  " }, {"modo de operacio"}};
const char MSG_INDICADOR_L2[3][17] =      {{"Aqui  Cal   Indi"}, {"Aqui  Cal   Indi"}, {"Aqui  Cal   Indi"}};

const char MSG_S0_SEL_SENSOR[3][17] = { { "Selecione S0    " }, { "Select S0       " }, { "Seleccione S0   " } };
const char MSG_S0_TEMPO_AMOSTRA[3][17] = { { "Tempo Amostragem" }, { "Sample Time     " }, { "Tiempo Muestreo " } };
const char MSG_S0_TEMPO_TESTE[3][17] = { { "Tempo de Ensaio " }, { "Experience Time " }, { "Tiempo de Prueba" } };
const char MSG_S0_PROXIMO_SENSOR[3][17] = { { "Próximo Sensor? " }, { "Next Sensor?    " }, { "Próximo Sensor? " } };
const char MSG_SALVA_RESULTADO[3][17] =      { { "Salvar Dados?   " }, { "Save Data?      " }, { "Guardar Datos?  " } };
const char MSG_SALVANDO_DADOS_USB[3][17] =   { { "Salvando Dados  " }, { "Saving Data     " }, { "Guardando Datos " } };
const char MSG_REPETIR_SAIR[3][17] = {{"repetir     sair"},	{"repeat      quit"}, {"repetir    salir"}};

const char MSG_PAUSE[3][17] =        {{"<    Pausar    >"}, {"<    Pause     >"}, {"<    Pausa     >"}};
const char MSG_CANCELA[3][17] =      {{"<   Cancelar   >"}, {"<    Cancel    >"}, {"<   Cancela    >"}};

const char MSG_VER_VOLTAR_PARAR[3][17] =  {{"Ver Voltar Parar"}, {"See Return  Stop"}, {"Ver Volver Stop"}};  
const char MSG_VOLTAR[3][17] =            {{"<    Voltar    >"}, {"<    Return    >"}, {"<    Volver    >"}}; 
const char MSG_CONCLUIDO[3][17] =         {{"<   Concluído  >"}, {"<   Concluded  >"}, {"<   Concluido  >"}};



const char MSG_S1_SEL_SENSOR[3][17] = { { "Selecione S1    " }, { "Select S1       " }, { "Seleccione S1   " } };
const char MSG_S2_SEL_SENSOR[3][17] = { { "Selecione S2    " }, { "Select S2       " }, { "Seleccione S2   " } };
const char MSG_S3_SEL_SENSOR[3][17] = { { "Selecione S3    " }, { "Select S3       " }, { "Seleccione S3   " } };
const char MSG_S4_SEL_SENSOR[3][17] = { { "Selecione S4    " }, { "Select S4       " }, { "Seleccione S4   " } };


const char MSG_USB_S0_OK[3][17] =     { { "Salvou dados S0 " }, { "Saved data S0   " }, { "Guardado S0     " } };
const char MSG_USB_S1_OK[3][17] =     { { "Salvou dados S1 " }, { "Saved data S1   " }, { "Guardado S1     " } };
const char MSG_USB_S2_OK[3][17] =     { { "Salvou dados S2 " }, { "Saved data S2   " }, { "Guardado S2     " } };
const char MSG_USB_S3_OK[3][17] =     { { "Salvou dados S3 " }, { "Saved data S3   " }, { "Guardado S3     " } };
const char MSG_USB_S4_OK[3][17] =     { { "Salvou dados S4 " }, { "Saved data S4   " }, { "Guardado S4     " } };

const char MSG_USB_S0_NOK[3][17] =     { { "Erro dados S0   " },  {  "Error data S0   " }, {  "Error S0        " } };
const char MSG_USB_S1_NOK[3][17] =     { { "Erro dados S1   " }, { "Error data S1   " }, { "Error S1        " } };
const char MSG_USB_S2_NOK[3][17] =     { { "Erro dados S2   " }, { "Error data S2   " }, { "Error S2        " } };
const char MSG_USB_S3_NOK[3][17] =     { { "Erro dados S3   " }, { "Error data S3   " }, { "Error S3        " } };
const char MSG_USB_S4_NOK[3][17] =     { { "Erro dados S4   " }, { "Error data S4   " }, { "Error S4        " } };


     /******************** CALIBRACAO DOS SENSORES ***********************/
//const char MSG_CALIB_TEMP_150[3][17] =      {{"Ajusta Temp150  "}, {"Adjust  Temp150 "}, {"Aqui   Indicador"}};
//const char MSG_CALIB_PRESSAO[3][17] =       {{"Ajusta Pressao  "}, {"Aqui   Indicador"}, {"Aqui   Indicador"}};


const char MSG_MODELO_SENSOR[eNumSensor][3][17] = { 
                                                   {{"Pressão    ðÿ OK" }, { "Pessure    ðÿ OK" }, { "Presión    ðÿ OK" } },
                                                   {{"Temp 150   ðÿ OK" }, { "Temp 150   ðÿ OK" }, { "Temp 150   ðÿ OK" } }, 
                                                   {{"Força 10N  ðÿ OK" }, {"Force 10N  ðÿ OK" }, {"Fuerza 10N ðÿ OK" }},
                                                   {{"PreDif250  ðÿ OK" }, {"DifPre250  ðÿ OK" }, {"PreDif250  ðÿ OK" }},
                                                   {{"Luminosida ðÿ OK" }, {"Bright     ðÿ OK" }, {"Brillo     ðÿ OK" }},
                                                   {{"Tensão 20V ðÿ OK" }, {"Volt20V    ðÿ OK" }, {"Tens20V    ðÿ OK" }},
                                                   {{"Corr200mA  ðÿ OK" }, {"Curr200mA  ðÿ OK" }, {"Corr200mA  ðÿ OK" }}, 
                                                   {{"Corr20mA   ðÿ OK" }, {"Curr20mA   ðÿ OK" }, {"Corr20mA   ðÿ OK" }},
                                                   {{"Magnético  ðÿ OK" }, {"Magnetic   ðÿ OK" }, {"Magnético  ðÿ OK" }},
                                                   {{"Fluxo      ðÿ OK" }, {"Flow       ðÿ OK" }, {"Flujo      ðÿ OK" }}
                                                   };



const char MSG_CALIB_SENSOR[eNumSensor][3][17] ={
                                                {{"Ajusta Pressao  "} , {"Adjust pressure "},  {"Ajusta Pression "}},       
                                                {{"Ajusta Temp150  "} , {"Adjust  Temp150 "},  {"Ajusta Temp150  "}},
                                                {{"Ajusta Força 10N"} , {"Adjust  Force   "} , {"Ajusta Fuerzaa  "}},
                                                {{"Ajusta PreDif250"} , {"Adj  Pressure Di"} , {"Ajusta PreDif   "}},
                                                {{"Ajus Luminosidad"} , {"Adj  Brightness "} , {"Ajusta Brillo   "}},
                                                {{"Ajus Tensão 20V "} , {"Adj  Volt 20V   "} , {"Ajus Tensión 20V"}},
                                                {{"Ajusta I 200mA  "} , {"Adjust I 200mA  "} , {"Ajusta I 200mA  "}},
                                                {{"Ajusta I 20mA   "} , {"Adjust I 20mA   "} , {"Ajusta I 20mA   "}},
                                                {{"Ajus Campo Mag  "} , {"Adjust Mag Field"} , {"Ajusta Campo Mag"}},
                                                {{"Ajusta Fluxo    "} , {"Adjust  Flow    "} , {"Ajusta Flujo    "}},
                                                };


const char MSG_CALIB_MENOR_VALUE[eNumSensor][3][17]={
                                                    {{"Menor Pressão   "}, {"Lower pressure  "}, {"Presión más baja"}},
                                                    {{"Menor Temperatu "}, {"Lower Temperatu "}, {"Temp. más baja  "}},
                                                    {{"Menor Força 10N "}, {"Lower Force     "}, {"Fuerza más baja "}},
                                                    {{"Menor Pressão Di"}, {"Lower Pressure D"}, {"Press 250  baja "}},
                                                    {{"Menor Luminosida"}, {"Lower Brightness"}, {"Brillo mas bajo "}},
                                                    {{"Menor Tensão 20V"}, {"Lower Volt 20V  "}, {"Tensión 20V baja"}},
                                                    {{"Menor I 200mA   "}, {"Lower I 200mA   "}, {"I 200mA más baja"}},
                                                    {{"Menor I 20mA    "}, {"Lower I 20mA    "}, {"I 20mA más baja "}},
                                                    {{"Menor Campo Mag "}, {"Lower Mag Field "}, {"Campo Mag bajo  "}},
                                                    {{"Menor Fluxo     "}, {"Lower Flow      "}, {"Flujo más bajo  "}},
                                                    };




const char MSG_CALIB_MAIOR_VALUE[eNumSensor][3][17] =   {
                                                        {{"Maior Pressão   "},  {"Greater pressure"}, {"Presión más alta"}},
                                                        {{"Maior Temperatu "},  {"Greater Temperat"}, {"Temp. más alta  "}},
                                                        {{"Maior Força 10N "} , {"Greater Force   "}, {"Temp. más alta  "}},
                                                        {{"Maior Pressão Di"} , {"Greater Press Di"}, {"Press 250  alta "}},
                                                        {{"Maior Luminosida"} , {"Greater Bright  "}, {"Brillo mas alta "}},
                                                        {{"Maior Tensão 20V"} , {"Greater Volt 20V"}, {"Tensión 20V alta"}},
                                                        {{"Maior I 200mA   "} , {"Greater I 200mA "}, {"I 200mA más alta"}},
                                                        {{"Maior I 20mA    "} , {"Greater I 20mA  "}, {"I 20mA más alta "}},
                                                        {{"Maior Campo Mag "} , {"Greater Magnetic"}, {"Campo Mag alto  "}},
                                                        {{"Maior Fluxo     "} , {"Greater Flow    "}, {"Flujo más alto  "}},
                                                        };





const char MSG_CALIB_INSIRA_S0[3][17] =         {{"Insira S0     OK"}, {"Aqui   Indicador"}, {"Aqui   Indicador"}};
const char MSG_CALIB_RETURN_DEFALULT[3][17] =   {{"Calib. Padrão   "}, {"Standard calib. "}, {"Calib. Estándar "}};
const char MSG_CALIB_RETURN_DEFALULT_2[3][17] = {{"<             OK"}, {"<             OK"}, {"<             OK"}};





typedef enum {
    eAnalogSelSensorS0,    //Seleciona sensor Analogico 0
    eAnalogSelOperationMode,  //Seleciona o modo de operação, aquisição de dados ou  indicador
    eAnalogIndicatorMode,     //Modo indicador   
    eAnalogTimeSampleSensorS0,    //Seleciona tempo de amostragem do sensor 0
    eAnalogTimeTestS0,    		//Seleciona tempo de testedo sensor 0
    eAnalogNextSensorS0,     //pergunta para proximo estado
    eAnalogSelSensorS1,
    eAnalogTimeSampleSensorS1,
    eAnalogTimeTestS1,
    eAnalogNextSensorS1,
    eAnalogSelSensorS2,
    eAnalogTimeSampleSensorS2,
    eAnalogTimeTestS2,
    eAnalogNextSensorS2,
    eAnalogSelSensorS3,
    eAnalogTimeSampleSensorS3,
    eAnalogTimeTestS3,
    eAnalogNextSensorS3,
    eAnalogSelSensorS4,
    eAnalogTimeSampleSensorS4,
    eAnalogTimeTestS4,
    eAnalogNextSensorS4,
    eAnalogStartTest,
    //eAnalogShowTest,
    eAnalogShowTestWaitPause,
    eAnalogShowTestVerVoltarParar,
    eAnalogShowTestCancela,
    eAnalogShowTestVoltar,
    eAnalogStopTest,
    eAnalogShowTestconcluded,
    eAnalogStartTestAgain, 
    eAnalogSaveTestQuestion,
    eAnalogCheckPenDrive,
    eAnalogInsertPenDrive,
    eAnalogAskSavePenDrive,
    eAnalogSaveTest,
    eAnalogSavingTest,
    eAnalogRepeatExit,
    eAnalogExit,
    //calib
    eAnalogCalibSelSensor,     //Seleciona o tipo de sensor 
    eAnalogCalibSelectReturnDefault, //!volta calib default
    eAnalogCalibInsiraSensorLow,
    eAnalogCalibSensorLow,
    eAnalogCalibSensorHigh, 
    eAnalogLastState				//Sempre a ultima posição do buffer
} eEstadoAnalogico;

typedef enum {
    eShowTestIdle, eShowS0, eShowS1, eShowS2, eShowS3, eShowS4, eShowDone,
} eEstadoShowTest;


typedef enum {
    eTestePaused, eTesteRunning, eTesteFinished
} eTesteStatus;



// estados layout:
uint16_t const _EstadosAnalogico[eAnalogLastState][4] = {

//Estado atual, estado tecla                ESQUERDA                      CENTRO                  DIREITA


        { eAnalogSelOperationMode   , eAnalogSelSensorS0        , eAnalogCalibSelSensor   , eAnalogIndicatorMode }, 
        { eAnalogSelSensorS0        , eAnalogSelSensorS0        , eAnalogSelSensorS0        , eAnalogTimeSampleSensorS0 },
        { eAnalogTimeSampleSensorS0 , eAnalogTimeSampleSensorS0 , eAnalogTimeSampleSensorS0 , eAnalogTimeTestS0 },
        { eAnalogTimeTestS0         , eAnalogTimeTestS0         , eAnalogTimeTestS0       , eAnalogNextSensorS0 },
        { eAnalogNextSensorS0       , eAnalogStartTest          , eAnalogNextSensorS0       , eAnalogSelSensorS1 },

        { eAnalogSelSensorS1        , eAnalogSelSensorS1        , eAnalogSelSensorS1        , eAnalogTimeSampleSensorS1 },
        { eAnalogTimeSampleSensorS1 , eAnalogTimeSampleSensorS1 , eAnalogTimeSampleSensorS1         , eAnalogTimeTestS1 },
        { eAnalogTimeTestS1         , eAnalogTimeTestS1         , eAnalogTimeTestS1       , eAnalogNextSensorS1 },
        { eAnalogNextSensorS1       , eAnalogStartTest          , eAnalogNextSensorS1       , eAnalogSelSensorS2 },

        { eAnalogSelSensorS2        , eAnalogSelSensorS2        , eAnalogSelSensorS2        , eAnalogTimeSampleSensorS2 },
        { eAnalogTimeSampleSensorS2 , eAnalogTimeSampleSensorS2 , eAnalogTimeSampleSensorS2         , eAnalogTimeTestS2 },
        { eAnalogTimeTestS2         , eAnalogTimeTestS2         , eAnalogTimeTestS2       , eAnalogNextSensorS2 },
        { eAnalogNextSensorS2       , eAnalogStartTest          , eAnalogNextSensorS2       , eAnalogSelSensorS3 },

        { eAnalogSelSensorS3        , eAnalogSelSensorS3        , eAnalogSelSensorS3        , eAnalogTimeSampleSensorS3 },
        { eAnalogTimeSampleSensorS3 , eAnalogTimeSampleSensorS3 , eAnalogTimeSampleSensorS3         , eAnalogTimeTestS3 },
        { eAnalogTimeTestS3         , eAnalogTimeTestS3         , eAnalogTimeTestS3       , eAnalogNextSensorS3 },
        { eAnalogNextSensorS3       , eAnalogStartTest          , eAnalogNextSensorS3       , eAnalogSelSensorS4 },


        { eAnalogSelSensorS4        , eAnalogSelSensorS4        , eAnalogSelSensorS4        , eAnalogTimeSampleSensorS4 },
        { eAnalogTimeSampleSensorS4 , eAnalogTimeSampleSensorS4 , eAnalogTimeSampleSensorS4         , eAnalogTimeTestS4 },
        { eAnalogTimeTestS4         , eAnalogTimeTestS4         , eAnalogTimeTestS4          , eAnalogStartTest },
    //  { eAnalogNextSensorS4       , eAnalogStartTest          , eAnalogNextSensorS4       , eAnalogNextSensorS4 },


        //Salvamento do teste  
        { eAnalogSaveTestQuestion    , eAnalogRepeatExit        , eAnalogSaveTestQuestion   , eAnalogCheckPenDrive },
      
        //inserir pendrive
        { eAnalogInsertPenDrive    , eAnalogSaveTestQuestion        , eAnalogInsertPenDrive   ,   eAnalogSaveTestQuestion /*eAnalogAskSavePenDrive*/ },

        //pede confirmação para salvar depois de inserido
        { eAnalogAskSavePenDrive    , eAnalogSaveTestQuestion        , eAnalogAskSavePenDrive   ,   eAnalogSaveTest },

                    

        //Repetir /Sair 
        { eAnalogRepeatExit        , eAnalogStartTest         , eAnalogRepeatExit           , eAnalogExit },


        //! Execução do teste
        { eAnalogStartTest, eAnalogStartTest, eAnalogShowTestWaitPause, eAnalogStartTest },

        //!apresentação dos resultados e navegação.

          //! <     pause     >
          { eAnalogShowTestWaitPause        , eAnalogShowTestWaitPause         , eAnalogShowTestVerVoltarParar           , eAnalogShowTestWaitPause },
          //! <Ver  voltar Parar>  
          { eAnalogShowTestVerVoltarParar        , eAnalogShowTestVoltar         , eAnalogStartTestAgain           , eAnalogStopTest },
          //! <     voltar     r>  
          { eAnalogShowTestVoltar        , eAnalogShowTestVoltar         , eAnalogStartTestAgain           , eAnalogShowTestVoltar },
          
          //! <     Cancelar     >
          { eAnalogShowTestCancela        , eAnalogShowTestCancela         , eAnalogStopTest           , eAnalogShowTestCancela },
         

          { eAnalogShowTestconcluded        , eAnalogShowTestconcluded      , eAnalogSaveTestQuestion       , eAnalogShowTestconcluded },      

          //Calibracao  
            { eAnalogCalibSelSensor             , eAnalogSelOperationMode         , eAnalogCalibSelectReturnDefault   ,eAnalogCalibInsiraSensorLow }, 
            { eAnalogCalibInsiraSensorLow       , eAnalogCalibSelSensor   , eAnalogCalibInsiraSensorLow   ,eAnalogCalibSensorLow }, 
            { eAnalogCalibSensorLow             ,  eAnalogCalibInsiraSensorLow        , eAnalogCalibSensorHigh         ,eAnalogCalibSensorLow },      
            { eAnalogCalibSensorHigh            , eAnalogCalibSensorLow        , eAnalogCalibSelSensor        , eAnalogCalibSensorHigh },      
            { eAnalogCalibSelectReturnDefault   , eAnalogSelOperationMode , eAnalogCalibSelectReturnDefault  , eAnalogCalibSelSensor },      
        //    { eAnalogCalibPressaoInsiraS0       , eAnalogCalibPressaoInsiraS0    , eAnalogCalibPressaoInsiraS0      , eAnalogCalibMenorPressao },
        //    { eAnalogCalibMenorPressao         , eAnalogCalibMenorPressao      , eAnalogCalibMaiorPressao          , eAnalogCalibMenorPressao },
        //    { eAnalogCalibMaiorPressao         , eAnalogCalibMaiorPressao      , eAnalogStopTest                , eAnalogCalibMaiorPressao },             
         };


#define BUFFER_LCD_SIZE 17

class C_Analogico {
private:
     uint8_t _buflcd[BUFFER_LCD_SIZE];
    
    uint16_t _eState;
    uint16 _uiTimedelay;

    uint16_t eTestState;
    
    eTesteStatus _eTestStatus;

    int8_t  _scShowSensorNumber; 

    bool   bModoIndicador; 
 
    
    //!Mostra no display o tipo de sensor
    void _ShowSensor(uint16_t uiIndex);
   
    //!Mostra no display o tipo de sensor que será calibrado 
//    void _ShowSensorCalib(uint16_t uiIndex); 

    //!Mostra o tempo de amostragem ou teste
    void _ShowTime(uint16_t uiValue, uint16_t uiType);

    //! Mostra o resultado do teste
    uint16_t _ShowTest();


    //!Seleciona o proximo estado
    uint16 _CheckNextState(int16 estado, int _teclado);

    //! altera o sensor a ser mostrado
    void  _UpdateShowLine1(uint8_t ucTecla);

    //! Mostra o andamento do teste na linha 1
     void _ShowTestLine1();
    
    //!  mostra o andamento do salvamento usb 
    uint32_t _ShowUsb( bool init);

    //! mostra os valores da calibração
    void _ShowCalib(uint16_t eType, eCalibIndex CalibHighLow) ;

    void fomatLine(int16_t firstValue, int16_t SecondValue, uint8_t Numdigitos, uint8_t ucUnidade,  uint8_t *pbufLcd);

public:
    void Init();

    //!Start Again
   // void Start(void);

    //Avanca os estados da maquina de estados 
    uint16_t Run();

};

extern C_Analogico EnsaioAnalogico;
#endif 
