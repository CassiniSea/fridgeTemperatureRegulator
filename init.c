#include "stm8s.h"
#include "clk.h"
#include "uart.h"

void init() {
	clkInit();
	uartInit();
	enableInterrupts();
}