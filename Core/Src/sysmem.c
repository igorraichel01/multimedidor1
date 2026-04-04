/**
  ******************************************************************************
  * @file    sysmem.c
  * @brief   Newlib heap management for STM32CubeIDE / arm-none-eabi-gcc.
  *          Provides _sbrk() used by malloc/free.
  ******************************************************************************
  */

#include <errno.h>
#include <stdint.h>

extern uint8_t _end;       /* Provided by linker script: start of heap */
extern uint8_t _estack;    /* Provided by linker script: end of RAM     */
extern uint32_t _Min_Stack_Size; /* Provided by linker script           */

void *_sbrk(ptrdiff_t incr)
{
  static uint8_t *heap_end = NULL;
  uint8_t *prev_heap_end;

  if (heap_end == NULL)
  {
    heap_end = &_end;
  }

  prev_heap_end = heap_end;

  if (heap_end + incr > (&_estack - (ptrdiff_t)&_Min_Stack_Size))
  {
    errno = ENOMEM;
    return (void *)-1;
  }

  heap_end += incr;
  return (void *)prev_heap_end;
}
