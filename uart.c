#include "stm8s.h"
#include "uart.h"

#ifdef UART_SEND_STRING_ASYNC_ENABLE
char* __uartStrPtr;
#endif

#ifdef UART_RECEIVE_STRING_ENABLE
char __uartBuffer[UART_MAX_STRING_LENGTH];
uint8_t __uartBufferIndex = 0;
#endif

void uartInit(void) {
	UART1_DeInit();
	UART1_Init(	57600,
							UART1_WORDLENGTH_8D,
							UART1_STOPBITS_1,
							UART1_PARITY_NO,
							UART1_SYNCMODE_CLOCK_DISABLE,
							UART1_MODE_TXRX_ENABLE);
	#if defined(UART_RECEIVE_STRING_ENABLE) || defined(UART_RECEIVE_STRING_ENABLE)
		UART1_ITConfig(	UART1_IT_RXNE, ENABLE);
	#endif
	UART1_Cmd(ENABLE);
}

void uartSendByte(uint8_t byte) {
	while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
	UART1_SendData8(byte);
}

void uartSendString(char* str) {
	while(*str) {
		uartSendByte(*str++);
	}
}

#ifdef UART_SEND_STRING_ASYNC_ENABLE
void uartSendStringAsync(char* str) {
	__uartStrPtr = str;
	UART1_ITConfig(UART1_IT_TXE, ENABLE);
}

void uartTxComplete(void) {
	if (*__uartStrPtr) {
		UART1_SendData8(*__uartStrPtr++);
	}
	else {
		UART1_ITConfig(UART1_IT_TXE, DISABLE);
	}
}
#endif

#ifdef UART_RECEIVE_STRING_ENABLE
void uartReceiveByte(uint8_t byte) {
	if(byte == '\r' || __uartBufferIndex >= UART_MAX_STRING_LENGTH) {
		__uartBuffer[__uartBufferIndex] = byte;
		__uartBufferIndex = 0;
		uartStringReceived(__uartBuffer);
	}
	else {
		__uartBuffer[__uartBufferIndex++] = byte;
	}
}
#endif

#if defined(UART_RECEIVE_STRING_ENABLE) || defined(UART_RECEIVE_BYTE_ENABLE)
	INTERRUPT void UART_RECEIVE8_INTERRUPT_VECTOR(void)	{
		UART1_ClearITPendingBit(UART1_IT_RXNE);
		uartReceiveByte(UART1_ReceiveData8());
	}
#endif

#if defined(UART_SEND_STRING_ASYNC_ENABLE)
	INTERRUPT void UART_TX_COMPLATE_INTERRUPT_VECTOR(void) {
		UART1_ClearITPendingBit(UART1_IT_TC);
		uartTxComplete();	
	}
#endif