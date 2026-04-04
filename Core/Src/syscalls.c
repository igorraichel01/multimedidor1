/**
  ******************************************************************************
  * @file    syscalls.c
  * @brief   Newlib syscall stubs for STM32CubeIDE / arm-none-eabi-gcc.
  *          This file replaces the Keil-specific Retarget.c when building
  *          with the GNU ARM toolchain.
  ******************************************************************************
  */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "stm32f4xx_hal.h"
#include "main.h"

/* Variables */
extern int __io_getchar(void) __attribute__((weak));
extern int __io_putchar(int ch) __attribute__((weak));

int _write(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}

int _read(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    *ptr++ = __io_getchar();
  }
  return len;
}

int __io_putchar(int ch)
{
  /* Redirect stdout/stderr to UART1 */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

int __io_getchar(void)
{
  return 0;
}

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
void _exit(int status) { while (1); }
int _kill(int pid, int sig) { return -1; }
int _getpid(void) { return -1; }
