/* Board Support Package (BSP) for the EK-TM4C123GXL board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */

#include "LED.h"
#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */

/* on-board LEDs */
#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

static uint32_t volatile l_tickCtr;

/*void SysTick_Handler(void) {
    ++l_tickCtr;
}*/

void BSP_init(void) {
    /*SYSCTL->RCGCGPIO  |= (1U << 5); 
    SYSCTL->GPIOHBCTL |= (1U << 5); 
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    __enable_irq();*/
	SYSCTL->RCGCGPIO|=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	GPIOF->DIR=0x0E;
	GPIOF->DEN=0x0E;
}

uint32_t BSP_tickCtr(void) {
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

void BSP_delay(uint32_t ticks) {
    uint32_t start = BSP_tickCtr();
    while ((BSP_tickCtr() - start) < ticks) {
    }
}

void BSP_ledRedOn(void)
{
	GPIOF->DATA|=0x02;
}
void BSP_ledRedOff(void)
{
	GPIOF->DATA&=(0xFD);
}
void BSP_ledBlueOn(void)
{
	GPIOF->DATA|=0x04;
}
void BSP_ledBlueOff(void)
{
	GPIOF->DATA&=(0xFB);
}
void BSP_ledGreenOn(void)
{
	GPIOF->DATA|=0x08;
}
void BSP_ledGreenOff(void)
{
	GPIOF->DATA&=(0xF7);
}
void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}