#include "osKernel.h"
#include "LED.h"
#define QUANTA 10
uint32_t count0=0,count1=0,count2=0;  /*Globel Counter For each Task*/
int i,j;

/*Task0 is responce about turn on Red Led*/
void task0()
{
  while(1)
  {
    count0++;
     BSP_ledRedOn();
    BSP_ledBlueOff();
    BSP_ledGreenOff();
   for(i=0;i<255;i++)   /*time delay*/
    {
      for(j=0;j<1000;j++);
    }
  }
}
/*Task1 is responce about turn on Blue Led*/

void task1()
{
  while(1)
  {
    count1++;
    BSP_ledRedOff();
    BSP_ledBlueOn();
    BSP_ledGreenOff();
    for(i=0;i<255;i++)
    {
      for(j=0;j<1000;j++);
    }
  }
}
/*Task2 is responce about turn on Grean Led*/

void task2()
{
  while(1)
  {
    count2++;
    BSP_ledRedOff();
    BSP_ledBlueOff();
    BSP_ledGreenOn();
    for(i=0;i<255;i++)    /*time delay*/
    {
      for(j=0;j<1000;j++);
    }
  }
}

int main()
{
  OsKernelInit();
  BSP_init();
  OsKernelAddThread(&task0,&task1,&task2);
  OsKernelLaunch(QUANTA);
  return 0;
}