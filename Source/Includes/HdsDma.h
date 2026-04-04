#ifndef __HDSDMA
#define __HDSDMA

#include <stdint.h>


const float CTE_ALPHA_DIGITAL=1.0f;// 0.6f; //04
const float CTE_ALPHA_ANALOGICO=0.001f;   //100 leituras para ter o valor final 

#ifdef __cplusplus
extern "C" {
#endif

void DmaStartAD();
void DmaStopAdReading();
void DmaStartAdReading(float fcte);
uint32_t DmaGetReading (uint8_t index);
void DmaEndconversion();

#ifdef __cplusplus
}
#endif

#endif


