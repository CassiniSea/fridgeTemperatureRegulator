/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "stm8s.h"
#include "init.h"
#include "uart.h"

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

uint8_t adcData;
uint8_t targetAdcCount = 0;
uint8_t programStatus = STARTING;
uint32_t programTime = 0;

void tim1Update(void)	{
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
	uartSendByte(adcData);
	uartSendByte(targetAdcCount);
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

	GPIO_Init(SWITCH_PORT, SWITCH_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
	
	enableInterrupts();
	
	while (1);
}