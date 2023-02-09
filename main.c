/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "stm8s.h"
#include "init.h"

// 600
#define STARTINGTIME 600
// 400
#define WORKINGTIME 400
// 700
#define RESTINGTIME 700
#define STARTING 0
#define WORKING 1
#define RESTING 2
//115
#define TARGETADC 115
// 10
#define TARGETADCCOUNTMAX 10
#define LED_PIN (GPIO_PIN_5)
#define LED_PORT (GPIOB)
#define SWITCH_PIN (GPIO_PIN_4)
#define SWITCH_PORT (GPIOD)

uint8_t uartData;
uint8_t adcData;
uint8_t targetAdcCount = 0;
uint8_t programStatus = STARTING;
uint32_t programTime = 0;

void uartTransmit(uint8_t data){
	while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
	UART1_SendData8(data);
}

@far @interrupt void uartReceive(void)	{
	UART1_ClearITPendingBit(UART1_IT_RXNE);
	uartData=UART1_ReceiveData8();
}

@far @interrupt void tim1Update(void)	{
	TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
	//GPIO_WriteReverse(LED_PORT, LED_PIN);
	adcData = (uint8_t)(ADC1_GetConversionValue()>>2);
	if(adcData >= TARGETADC) {
		if(targetAdcCount < TARGETADCCOUNTMAX) {
			targetAdcCount++;
		}
	}
	else {
		if(targetAdcCount > 0) {
			targetAdcCount--;
		}
	}
	uartTransmit(adcData);
	uartTransmit(targetAdcCount);
	switch(programStatus) {
		case STARTING:
			programTime++;
			if(programTime >= STARTINGTIME) {
				programTime = 0;
				if(targetAdcCount == TARGETADCCOUNTMAX) {
					programStatus = RESTING;
				}
				else {
					programStatus = WORKING;
				}
			}
		break;
		case WORKING:
			GPIO_WriteLow(SWITCH_PORT, SWITCH_PIN);
			programTime++;
			if(programTime >= WORKINGTIME) {
				programTime = 0;
				programStatus = RESTING;
			}
		break;
		case RESTING:
			GPIO_WriteHigh(SWITCH_PORT, SWITCH_PIN);
			programTime++;
			if(programTime >= RESTINGTIME && targetAdcCount == 0) {
				programTime = 0;
				programStatus = WORKING;
			}
		break;
	}
}

main() {
	init();
	
	UART1_DeInit();
	UART1_Init(	57600,
							UART1_WORDLENGTH_8D,
							UART1_STOPBITS_1,
							UART1_PARITY_NO,
							UART1_SYNCMODE_CLOCK_DISABLE,
							UART1_MODE_TXRX_ENABLE);
	UART1_ITConfig(	UART1_IT_RXNE, ENABLE);
	UART1_Cmd(ENABLE);
	
	TIM1_DeInit();
	TIM1_TimeBaseInit(	16000,
											TIM1_COUNTERMODE_UP,
											1000,
											0);
	TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
	TIM1_Cmd(ENABLE);
	
	ADC1_DeInit();
	ADC1_Init(	ADC1_CONVERSIONMODE_CONTINUOUS,
							ADC1_CHANNEL_3,
							ADC1_PRESSEL_FCPU_D18,
							ADC1_EXTTRIG_TIM,
							DISABLE,
							ADC1_ALIGN_RIGHT,
							ADC1_SCHMITTTRIG_CHANNEL3,
							DISABLE);
	ADC1_Cmd(ENABLE);
	ADC1_StartConversion();
	
	//GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(SWITCH_PORT, SWITCH_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
	
	enableInterrupts();
	
	while (1);
}