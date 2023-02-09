#include "stm8s.h"
#include "uart.h"

#if defined(UART_RECEIVE_STRING_ENABLE) || defined(UART_RECEIVE_BYTE_ENABLE)
	INTERRUPT void UART_RECEIVE8_INTERRUPT_VECTOR(void)	{
		UART1_ClearITPendingBit(UART1_IT_RXNE);
		uartReceive8(UART1_ReceiveData8());
	}
#endif

#if defined(UART_SEND_STRING_ASYNC_ENABLE)
	INTERRUPT void UART_TX_COMPLATE_INTERRUPT_VECTOR(void) {
		UART1_ClearITPendingBit(UART1_IT_TC);
		uartTxComplete();	
	}
#endif