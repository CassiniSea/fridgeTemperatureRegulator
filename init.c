#include "stm8s.h"
#include "clk.h"
#include "uart.h"
#include "tim1.h"
#include "adc.h"

void init() {
	clkInit();
	uartInit();
	tim1Init();
	adcInit();
	enableInterrupts();
}