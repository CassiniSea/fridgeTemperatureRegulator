#include "stm8s.h"
#include "gpio.h"
#include "fridge.h"

void gpioInit(void) {
	GPIO_Init(COMPRESSOR_SWITCH_PORT, COMPRESSOR_SWITCH_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}