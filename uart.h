/*
If you want to receive STRING by uart
define a UART_RECEIVE_STRING_ENABLE and
define a void uartStringReceived(char* str) function

else if you want receive a BYTE by uart
define a UART_RECEIVE_BYTE_ENABLE and
define a void uartReceive8(uint8_t c) function

WARNING: You can only use one option, not both.
*/
//#define UART_RECEIVE_STRING_ENABLE
//#define UART_MAX_STRING_LENGTH 32
//#define UART_RECEIVE_BYTE_ENABLE

/*
If you want to async send a sring by uart
define a UART_SEND_STRING_ASYNC_ENABLE and
use uartSendStringAsync(char* str) function
*/
//#define UART_SEND_STRING_ASYNC_ENABLE

// =================================================

#ifdef UART_RECEIVE_BYTE_ENABLE
	#undef UART_RECEIVE_STRING_ENABLE
#endif 

#if defined(UART_RECEIVE_STRING_ENABLE) || defined(UART_RECEIVE_BYTE_ENABLE)
	#define UART_RECEIVE8_INTERRUPT_VECTOR uartReceive8Interrupt
#else
	#define UART_RECEIVE8_INTERRUPT_VECTOR NonHandledInterrupt
#endif

#if defined(UART_SEND_STRING_ASYNC_ENABLE)
	#define UART_TX_COMPLATE_INTERRUPT_VECTOR uartTxCompleteInterrupt
#else
	#define UART_TX_COMPLATE_INTERRUPT_VECTOR NonHandledInterrupt
#endif

#ifdef UART_SEND_STRING_ENABLE
	#undef UART_SEND_STRING_ASYNC_ENABLE
#endif 

void uartInit(void);
void uartTransmit(uint8_t);
void uartSendString(char*);
void uartSendStringAsync(char*);
void uartTxComplete(void);
void uartStringReceived(char*);
void uartReceive8(uint8_t);
