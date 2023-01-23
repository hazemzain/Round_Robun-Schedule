/*
1-schedule
2-TCB FOR EACH THREAD
3-stack to hold the context 
*/
#include "osKernel.h"
#include "TM4C123GH6PM.h"
#define NUM_OF_THREADS 3
#define STACK_SIZE    100
#define BUS_FREQ      16000000
uint32_t millisec;
struct TCB
{
	int32_t *Stack_pointer;
	struct TCB *Next_thread;
};
typedef struct TCB tcbType;
tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPtr;
int32_t Tcbs_Stack[NUM_OF_THREADS][STACK_SIZE];
/*
  Discribtion:this Funcation is used to init stack for each Task
  Take the the number of tas to init the stack
*/
void osKernalStackInit(int i)
{
  tcbs[i].Stack_pointer=&Tcbs_Stack[i][STACK_SIZE-16];
  Tcbs_Stack[i][STACK_SIZE-1]=0x01000000; /*Set defualt value for xPSR*/
}

void OsKernelLaunch(uint32_t quanta)
{
  /*
    init systick
  */
  SysTick->CTRL=0;
  SysTick->VAL=0;
  /*
    load the value of quanta with millsecend in load reg
  */
  SysTick->LOAD=(quanta*millisec)-1;
  /*
    enable systick 
  */
  SysTick->CTRL=0x00000007;
  osSchedulerLaunch();
	
}

void OsKernelInit(void)
{
  /*
    disaple all interrupt
  */
  __disable_irq();
  /*
    set systick timer to come every 10msec
  */
  millisec=BUS_FREQ/1000;
  
}

uint8_t OsKernelAddThread(void (*task0)(void),void (*task1)(void),void (*task2)(void))
{
  /*
    1-disable all interrupt
  */
   __disable_irq();
  /*
    connect each tcb for each thread to ather tcb of thread
  */
  tcbs[0].Next_thread=&tcbs[1];
  tcbs[1].Next_thread=&tcbs[2];
  tcbs[2].Next_thread=&tcbs[0];
  /*
    intialize PC for each stack
  */
  osKernalStackInit(0);
  Tcbs_Stack[0][STACK_SIZE-2]=(uint32_t)(task0);
  osKernalStackInit(1);
  Tcbs_Stack[1][STACK_SIZE-2]=(uint32_t)(task1);
  osKernalStackInit(2);
  Tcbs_Stack[2][STACK_SIZE-2]=(uint32_t)(task2);
  /*
    enable all interrupt
  */
  currentPtr=&tcbs[0];
  __enable_irq();
  return 1;
}
