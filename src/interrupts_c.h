#ifndef _VVC_INTERRUPTS_C_H
#define _VVC_INTERRUPTS_C_H

#include "global.h"

// C-language hardware interrupt method signatures.
#ifdef VVC_F0
// STM32F0xx EXTI lines.
// EXTI handler for interrupt lines 0-1.
void EXTI0_1_IRQ_handler(void);
// EXTI handler for interrupt lines 2-3.
void EXTI2_3_IRQ_handler(void);
// EXTI handler for interrupt lines 4-15.
void EXTI4_15_IRQ_handler(void);
#elif VVC_F3
// STM32F3xx(?) EXTI lines.
// EXTI handler for interrupt line 0.
// (Unused)
// EXTI handler for interrupt line 1.
// (Unused)
// EXTI handler for interrupt line 2.
void EXTI2_touchsense_IRQ_handler(void);
// EXTI handler for interrupt line 3.
void EXTI3_IRQ_handler(void);
// EXTI handler for interrupt line 4.
void EXTI4_IRQ_handler(void);
// EXTI handler for interrupt lines 5-9.
void EXTI5_9_IRQ_handler(void);
// EXTI handler for interrupt lines 10-15.
// (Unused)
#endif

#endif
