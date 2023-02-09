#include "stm8s.h"
#include "main.h"
#include "gpio.h"

void gpioInit(void) {
	GPIO_Init(SWITCH_PORT, SWITCH_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}