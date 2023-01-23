#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
#include <stdint.h>
void osKernalStackInit(int i);
void OsKernelLaunch(uint32_t quanta);
void OsKernelInit(void);
uint8_t OsKernelAddThread(void (*task0)(void),void (*task1)(void),void (*task2)(void));
#endif
