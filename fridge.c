#include "stm8s.h"
#include "fridge.h"
#include "adc.h"

void startCompressor(void) {
	GPIO_WriteLow(COMPRESSOR_SWITCH_PORT, COMPRESSOR_SWITCH_PIN);
}

void stopCompressor(void) {
	GPIO_WriteHigh(COMPRESSOR_SWITCH_PORT, COMPRESSOR_SWITCH_PIN);
}

uint8_t isNeedStartCompressor(void) {
	return getTargetAdcCount() == 0;
}