#include "stm8s.h"
#include "main.h"
#include "init.h"
#include "uart.h"

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
	
	while (1);
}