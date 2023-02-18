#include "stm8s.h"
#include "tim1.h"
#include "program.h"
#include "adc.h"

void tim1Init(void) {
	TIM1_DeInit();
	TIM1_TimeBaseInit(	16000,
											TIM1_COUNTERMODE_UP,
											1000,
											0);
	TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
	TIM1_Cmd(ENABLE);	
}

#if defined(TIM1_UPDATE_INTERRUPT_ENABLE)
	INTERRUPT void TIM1_UPDATE_INTERRUPT_VECTOR(void) {
		TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
		tim1Update();	
	}
	
	void tim1Update(void)	{
		updateTargetAdcCount();
		updateProgramStatus();
		sendStats();
	}
#endif