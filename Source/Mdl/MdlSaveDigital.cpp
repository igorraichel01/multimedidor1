/**\******************************** NOME DO MODULO *******************************************//**
 *\file     MdlSaveDigital.cpp
 
 *\details   Módulo para salvamento do experimetno digital 
 
 *		
 *
 
 * ----------------------------------------------------------------------------------------------
 * \version   s.00 - Primeira versão documentada
 * \date      30/04/2021
 ***********************************************************************************************/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Modo0.h"
#include "MdlSaveDigital.h"
#include <stdio.h>
#include <string.h>
#include "MdlSensor.h"
#include "File_Handling.h"
#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_msc.h"

/*************************************************************************************************
 Variaveis locais ao modulo
 *************************************************************************************************/
C_SaveDigital SaveDigital;

/*********************************************************************************************//**
 * \function     SaveFunc1
 * \details      Salva as informações da função 1
 *               pode ser 2 ou 5 sensores, salva sempre como se fosse 5. os campos vão ficar zerados se não foram alimentados com ifnormações
 *               variável velocidade
 indice 0= 0->1
 *                       1= 0->2
 *                       2= 0->3
 *                       3= 0->4
 *                       4= 1->2
 *                       5= 2->3
 *                       6= 3->4

 * Salva o arquivo de tempos F1-t_0000x  e vai incrementadno o número conforme o teste
 * Salva o arquivo de Velocidade caso tenha F1-Vm_0000x  e vai incrementadno o número conforme o teste

 primeira linha tempos     0->1,0->2,0->3,0->4,1->2,2->3,3->4
 Segunda linha velocidade  0->1,0->2,0->3,0->4,1->2,2->3,3->4


 Nsensores   indica 2 ou 5 sensores
 bVelocity  mostra ou não a velocidade

 * \author     
 * \date        28/09/2022
 ************************************************************************************************/
bool C_SaveDigital::SaveFunc1(uint8_t Nsensores, bool bVelocity) {
    uint8_t filename[20];
    uint8_t Line[20];
    uint8_t ucBufUsb[200];
    uint16_t i = 0;

    FRESULT Result;
    //! Limpa o buffer
    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    //! Na primeira vez incrementa o salvamento
    if (SensorDigital.Result.uiNEnsaio[FUNC_1 - 1] == 0)
        SensorDigital.Result.uiNEnsaio[FUNC_1 - 1]++;

    //! Sempre salva o tempo
    sprintf((char*) &filename, "F1-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[FUNC_1 - 1]);

    //monta o arquivo
    if (Nsensores == 2) {
        sprintf((char*) Line, "0,1;%f\n", SensorDigital.Result.fTempoFinal[0]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }
    else {
        sprintf((char*) Line, "0,1;%f\n", SensorDigital.Result.fTempoFinal[0]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "0,2;%f\n", SensorDigital.Result.fTempoFinal[1]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "0,3;%f\n", SensorDigital.Result.fTempoFinal[2]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "0,4;%f\n", SensorDigital.Result.fTempoFinal[3]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "1,2;%f\n", SensorDigital.Result.fTempoFinal[4]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "2,3;%f\n", SensorDigital.Result.fTempoFinal[5]);     strcat((char*) &ucBufUsb, (char*) &Line);
        sprintf((char*) Line, "3,4;%f\n", SensorDigital.Result.fTempoFinal[6]);     strcat((char*) &ucBufUsb, (char*) &Line);
    }
    
    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;

    //!Deve apagar o arquivo de velocidade caso exista , para nao gerar confusão
    sprintf((char*) &filename, "F1-Vm_%05u.CSV", SensorDigital.Result.uiNEnsaio[FUNC_1 - 1]);

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);

    if (bVelocity) {
        memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

        //monta o arquivo
        if (Nsensores == 2) {
            sprintf((char*) Line, "0,1;%f\n", SensorDigital.Result.fvelocidade[0]);  strcat((char*) &ucBufUsb, (char*) &Line);
        }
        else {
            sprintf((char*) Line, "0,1;%f\n", SensorDigital.Result.fvelocidade[0]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "0,2;%f\n", SensorDigital.Result.fvelocidade[1]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "0,3;%f\n", SensorDigital.Result.fvelocidade[2]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "0,4;%f\n", SensorDigital.Result.fvelocidade[3]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "1,2;%f\n", SensorDigital.Result.fvelocidade[4]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "2,3;%f\n", SensorDigital.Result.fvelocidade[5]); strcat((char*) &ucBufUsb, (char*) &Line);
            sprintf((char*) Line, "3,4;%f\n", SensorDigital.Result.fvelocidade[6]); strcat((char*) &ucBufUsb, (char*) &Line);
        }

        //Substitui o ponto por virgula
        for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
            if (ucBufUsb[i] == '.')
                ucBufUsb[i] = ',';
        }

        //!Salva o arquivo
        Create_File((char*) &filename);

        Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    }

    if (Result != FR_OK)
        return false;
    else {
        SensorDigital.Result.uiNEnsaio[FUNC_1 - 1]++; //Incrementa para o próximo salvamento
        return true;
    }
}

/*********************************************************************************************//**
 * \function     SaveFunc2
 * \details      Salva as informações da função 1
 
 * Salva o arquivo de tempos F2-t_0000x  e vai incrementadno o número conforme o teste
 * Salva o arquivo de Velocidade caso tenha F2-Vm_0000x  e vai incrementadno o número conforme o teste


 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
bool C_SaveDigital::SaveFunc2(bool bVelocity, int16 iFunc) {
    uint8_t filename[20];
    uint8_t Line[40];
    uint8_t ucBufUsb[200];
    uint16_t i = 0;

    FRESULT Result;
    //! Limpa o buffer
    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    //! Na primeira vez incrementa o salvamento
    if (SensorDigital.Result.uiNEnsaio[iFunc - 1] == 0)
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++;

    if (!bVelocity) {

        //! Sempre salva o tempo
        if (iFunc == FUNC_2)
            sprintf((char*) &filename, "F2-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        else if (iFunc == FUNC_5) {
            sprintf((char*) &filename, "F5-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        }
        else {
            return false;
        }

        //monta o arquivo
        sprintf((char*) Line, "%f\n", SensorDigital.Result.fTempoFinal[0]); strcat((char*) &ucBufUsb, (char*) &Line);

        //Substitui o ponto por virgula
        for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
            if (ucBufUsb[i] == '.')
                ucBufUsb[i] = ',';
        }

        //apaga o arquivo caso ele exista
        Remove_File((char*) &filename);
        //!Salva o arquivo
        Create_File((char*) &filename);

        Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    }
    else {

        //!Deve apagar o arquivo de velocidade caso exista , para nao gerar confusão
        if (iFunc == FUNC_2)
            sprintf((char*) &filename, "F2-t-Vm_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        else if (iFunc == FUNC_5) {
            sprintf((char*) &filename, "F5-t-V_a_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        }
        else if (iFunc == FUNC_9) {
            sprintf((char*) &filename, "F9-t-Vm_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        }

        else if (iFunc == FUNC_12) {
            sprintf((char*) &filename, "F12-t-Vm_Ec_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
        }
        else {
        }

        //apaga o arquivo caso ele exista
        Remove_File((char*) &filename);

        memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

        //monta o arquivo

        if (iFunc == FUNC_2 || iFunc == FUNC_9) {
            sprintf((char*) Line, "%f;%f\n", SensorDigital.Result.fTempoFinal[0], SensorDigital.Result.fvelocidade[0]);
            strcat((char*) &ucBufUsb, (char*) &Line);
        }
        else if (iFunc == FUNC_5) {
            sprintf((char*) Line, "%f;%f;%f\n", SensorDigital.Result.fTempoFinal[0], SensorDigital.Result.fvelocidade[0], SensorDigital.Result.fAcel);
            strcat((char*) &ucBufUsb, (char*) &Line);
        }
        else if (iFunc == FUNC_12) {
            sprintf((char*) Line, "%f;%f;%f\n", SensorDigital.Result.fTempoFinal[0], SensorDigital.Result.fvelocidade[0], SensorDigital.Result.energia);
            strcat((char*) &ucBufUsb, (char*) &Line);
        }
        else {
        }

        //Substitui o ponto por virgula
        for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
            if (ucBufUsb[i] == '.')
                ucBufUsb[i] = ',';
        }

        //!Salva o arquivo
        Create_File((char*) &filename);

        Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    }
    
    if (Result != FR_OK)
        return false;
    else {
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++; //Incrementa para o próximo salvamento
        return true;
    }
}

/*********************************************************************************************//**
 * \function     SaveFunc3
 * \details      Salva as informações da função 3
 *               10 tempos de passagem 
 


 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
bool C_SaveDigital::SaveFunc3_10(int16 iFunc) {
    uint8_t filename[20];
    uint8_t Line[20];
    uint8_t ucBufUsb[200];
    uint16_t i = 0;

    FRESULT Result;
    //! Limpa o buffer
    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    //! Na primeira vez incrementa o salvamento
    if (SensorDigital.Result.uiNEnsaio[iFunc - 1] == 0)
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++;

    //! Sempre salva o tempo
    if (iFunc == FUNC_3)
        sprintf((char*) &filename, "F3-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else if (iFunc == FUNC_10)
        sprintf((char*) &filename, "F10-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else
        return false;

    for (i = 0; i < 10; i++) {
        sprintf((char*) Line, "%d;%f\n", i + 1, SensorDigital.Result.fTempoFinal[i]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }
   

    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;
    else {
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++; //Incrementa para o próximo salvamento
        return true;
    }
}

/*********************************************************************************************//**
 * \function     SaveFunc4
 * \details      Salva as informações da função 3
 *               10 tempos de passagem  e 10 frequencias 
 
 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
bool C_SaveDigital::SaveFunc4_6(int16 iFunc) {
    uint8_t filename[20];
    uint8_t Line[20];
    uint8_t ucBufUsb[200];
    uint16_t i = 0;

    FRESULT Result;
    //! Limpa o buffer
    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    //! Na primeira vez incrementa o salvamento
    if (SensorDigital.Result.uiNEnsaio[iFunc - 1] == 0)
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++;

    //! Sempre salva o tempo
    if (iFunc == 4)
        sprintf((char*) &filename, "F4-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else if (iFunc == 6)
        sprintf((char*) &filename, "F6-t_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else
        return false;

    for (i = 0; i < 10; i++) {
        sprintf((char*) Line, "%d;%f\n", i + 1, SensorDigital.Result.fTempoFinal[i]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }

    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;

    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    if (iFunc == 4)
        sprintf((char*) &filename, "F4-f_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else if (iFunc == 6)
        sprintf((char*) &filename, "F6-f_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else
        return false;

    for (i = 0; i < 10; i++) {
        sprintf((char*) Line, "%d;%f\n", i + 1, SensorDigital.Result.ffrequencia[i]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }

    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;
    else {
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++; //Incrementa para o próximo salvamento
        return true;
    }
}

/*********************************************************************************************//**
 * \function     SaveFunc7_8
 * \details      Salva as informações da função 7  e 8
 *               10 tempos de passagem  e 10 frequencias 
 
 * \author     
 * \date        06/10/2022
 ************************************************************************************************/
bool C_SaveDigital::SaveFunc7_8(int16 iFunc) {
    uint8_t filename[20];
    uint8_t Line[20];
    uint8_t ucBufUsb[300];
    uint16_t i = 0;

    FRESULT Result;
    //! Limpa o buffer
    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    //! Na primeira vez incrementa o salvamento
    if (SensorDigital.Result.uiNEnsaio[iFunc - 1] == 0)
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++;

    //! Sempre salva o tempo
    if (iFunc == 7)
        sprintf((char*) &filename, "F7-t-S0_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else if (iFunc == 8)
        sprintf((char*) &filename, "F8-t-S0_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else
        return false;

    for (i = 0; i < 10; i++) {
        sprintf((char*) Line, "%d;%f\n", i + 1, SensorDigital.Result.fTempoFinal[i]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }

    if (iFunc == 8) {
        for (i = 0; i < 11; i++) {
            sprintf((char*) Line, "%d;%f\n", i + 11, SensorDigital.Result.fTempoFinal_S0[i]);
            strcat((char*) &ucBufUsb, (char*) &Line);
        }
    }

    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;

    memset((char*) &ucBufUsb, 0, sizeof(ucBufUsb));

    if (iFunc == 7)
        sprintf((char*) &filename, "F7-t-S1_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else if (iFunc == 8)
        sprintf((char*) &filename, "F8-t_S1_%05u.CSV", SensorDigital.Result.uiNEnsaio[iFunc - 1]);
    else
        return false;

    for (i = 0; i < 10; i++) {
        sprintf((char*) Line, "%d;%f\n", i + 1, SensorDigital.Result.fTempoFinal_S1[i]);
        strcat((char*) &ucBufUsb, (char*) &Line);
    }

    //Substitui o ponto por virgula
    for (i = 0; i < strlen((char*) &ucBufUsb); i++) {
        if (ucBufUsb[i] == '.')
            ucBufUsb[i] = ',';
    }

    //apaga o arquivo caso ele exista
    Remove_File((char*) &filename);
    //!Salva o arquivo
    Create_File((char*) &filename);

    Result = Update_File((char*) &filename, (char*) &ucBufUsb);

    if (Result != FR_OK)
        return false;
    else {
        SensorDigital.Result.uiNEnsaio[iFunc - 1]++; //Incrementa para o próximo salvamento
        return true;
    }
}

