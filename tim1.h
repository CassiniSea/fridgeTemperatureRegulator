/*
To start using
Open stm8_interrupt_vector.c and add
#include "tim1.h"
and
TIM1_UPDATE_INTERRUPT_VECTOR to irq11
*/

/*
If you want use a update interrupt
define a TIM1_UPDATE_INTERRUPT_ENABLE and
define a void tim1Update(void) function
*/
#define TIM1_UPDATE_INTERRUPT_ENABLE

// =================================================

#include "stm8s.h"

#if defined(TIM1_UPDATE_INTERRUPT_ENABLE)
	#define TIM1_UPDATE_INTERRUPT_VECTOR tim1UpdateInterrupt
#else
	#define TIM1_UPDATE_INTERRUPT_VECTOR NonHandledInterrupt
#endif

#if defined(TIM1_UPDATE_INTERRUPT_ENABLE)
	INTERRUPT_HANDLER_TRAP(TIM1_UPDATE_INTERRUPT_VECTOR);
#endif

void tim1Init(void);
void tim1Update(void);