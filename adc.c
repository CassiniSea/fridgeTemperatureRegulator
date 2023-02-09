#include "stm8s.h"
#include "adc.h"

void adcInit(void) {
	ADC1_DeInit();
	ADC1_Init(	ADC1_CONVERSIONMODE_CONTINUOUS,
							ADC1_CHANNEL_3,
							ADC1_PRESSEL_FCPU_D18,
							ADC1_EXTTRIG_TIM,
							DISABLE,
							ADC1_ALIGN_RIGHT,
							ADC1_SCHMITTTRIG_CHANNEL3,
							DISABLE);
	ADC1_Cmd(ENABLE);
	ADC1_StartConversion();
}

uint8_t getAdcData(void) {
	return (uint8_t)(ADC1_GetConversionValue()>>2);
}