#include "stm8s.h"
#include "uart.h"
#include "tim1.h"

#if defined(UART_RECEIVE_STRING_ENABLE) || defined(UART_RECEIVE_BYTE_ENABLE)
	INTERRUPT_HANDLER_TRAP(UART_RECEIVE8_INTERRUPT_VECTOR);
#endif

#if defined(UART_SEND_STRING_ASYNC_ENABLE)
	INTERRUPT_HANDLER_TRAP(UART_TX_COMPLATE_INTERRUPT_VECTOR);
#endif

#if defined(TIM1_UPDATE_INTERRUPT_ENABLE)
	INTERRUPT_HANDLER_TRAP(TIM1_UPDATE_INTERRUPT_VECTOR);
#endif