#ifndef __INVENTYPESH
#define __INVENTYPESH


#include "stm32f4xx_hal.h"


#ifdef HIGH_LEVEL_SOFTWARE

#include <vcl.h>
#include <Controls.hpp>
#include <Classes.hpp>
#include <StdCtrls.hpp>

#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <System.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

#define __no_init
#define __interrupt
#define __root
#define __data20
#define __disable_interrupt()
#define SystemCoreClockUpdate()
#define __disable_irq();
#define __attribute__  ;
#define at(LOCATION_AUTOCAL_PARAM);
#define at(LOCATION_CALIB_DEFAULT);
#define at(LOCATION_FACTORY_CONFIG);
#define at(LOCATION_HW_CONFIG);


///HIGH LEVEL SOFTWARE TYPES
//typedef signed short int16;///< basic type, size 16 bits, signed    (i before variable name)
//typedef unsigned short uint16;///< basic type, size 16 bits, unsigned  (ui before variable name)
//typedef signed int int32;///< basic type, size 32 bits, signed    (l before variable name)
//typedef unsigned int uint32;///< basic type, size 32 bits, unsigned  (ul before variable name)
//typedef unsigned char boolean;

#else
#define __root __attribute__((used))
#define __no_init  __attribute__( ( section( "NoInit"),zero_init))

#endif




//! Tipos básicos definidos
#define true  1
#define false 0
//#define TRUE  1
//#define FALSE 0
#define ON    1
#define OFF   0
#define READ  0
#define WRITE 1

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

typedef signed  short  int16; //!< basic type, size 16 bits, signed    (i before variable name)
typedef unsigned short uint16; //!< basic type, size 16 bits, unsigned  (ui before variable name)
typedef signed long   int32; //!< basic type, size 32 bits, signed    (l before variable name)
typedef unsigned long uint32; //!< basic type, size 32 bits, unsigned  (ul before variable name)
typedef unsigned char boolean;


//! Define os tipos básicos de variáveis
// Exact-width signed integer types
typedef unsigned char BYTE; //!< basic type, size 8 bits, signed    (c before variable name)
typedef signed char int8; //!< basic type, size 8 bits, signed    (c before variable name)
typedef unsigned char uint8; //!< basic type, size 8 bits, unsigned   (uc before variable name)
typedef signed long long int64; //!< basic type, size 64 bits, signed   (x before variable name)
typedef unsigned long long uint64; //!< basic type, size 64 bits, unsigned (ux before variable name)
typedef float float32; //!< Ponto-flutuante 32 bits
typedef double float64;

//! Com este pragma, habilita uso de unioes sem nomes intermediarios
#pragma anon_unions
typedef union
{
  uint16 uiValue;
  struct
  {
    uint8 ucLow;
    uint8 ucHigh;
  };
} Uint16;

typedef union
{
  uint32 ulValue;
  struct
  {
    Uint16 Low;
    Uint16 High;
  };
} Uint32;

typedef union
{
  float fValue;
  Uint32 ulValue;

} Ufloat;

typedef union
{
  uint64 ulValue;

  struct
  {
    Uint32 Low;
    Uint32 High;
  };
} UUint64;

typedef union
{
  uint64 ulValue;

  struct
  {
    uint32 Low;
    uint32 High;
  };
} Uint64;

//! Declara um ponteiro para uma função que retorna um int16 e recebe um parâmetro int16
typedef int16 (*TPExternFunc)(int16);
//! Declara um ponteiro para uma função que recebe como parâmetro um ponteiro para uma string
typedef void (*TPMessageFunction)(const char*);
//! Declara um ponteiro para uma função que não recebe parâmetros nem retorna nada
typedef void (*TPInterruptVector)(void);


#endif
