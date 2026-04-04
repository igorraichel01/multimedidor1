/**
 * Retarget.c - GCC-compatible retargeting for newlib stdio
 *
 * Replaces the Keil-specific retargeting with GCC/newlib-compatible
 * implementations that redirect printf output to USART1.
 */

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "stm32f4xx_hal.h"
#include "main.h"

/**
 * @brief  Retargets the C library printf function to USART1.
 * @param  file: file descriptor
 * @param  ptr:  data buffer
 * @param  len:  data length
 * @retval number of bytes written
 */
int _write(int file, char *ptr, int len)
{
    if (file == STDOUT_FILENO || file == STDERR_FILENO)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)ptr, (uint16_t)len, HAL_MAX_DELAY);
        return len;
    }
    errno = EBADF;
    return -1;
}

int _close(int file)
{
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

void *_sbrk(int incr)
{
    extern char _end;
    static char *heap_end = NULL;
    char *prev_heap_end;

    if (heap_end == NULL)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    heap_end += incr;
    return (void *)prev_heap_end;
}
