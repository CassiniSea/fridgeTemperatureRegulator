#include "stm8s.h"
#include "clk.h"

void init() {
	clkInit();	
	enableInterrupts();
}