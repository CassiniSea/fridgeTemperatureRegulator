#include "stm8s.h"
#include "main.h"
#include "init.h"
#include "uart.h"
#include "adc.h"

uint8_t adcData;
uint8_t targetAdcCount = 0;
uint8_t programStatus = STARTING;
uint32_t programTime = 0;

void updateTargetAdcCount(void) {
	adcData = getAdcData();
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
}

void startCompressor(void) {
	GPIO_WriteLow(SWITCH_PORT, SWITCH_PIN);
}

void stopCompressor(void) {
	GPIO_WriteHigh(SWITCH_PORT, SWITCH_PIN);
}

void setProgramStatus(uint8_t newProgramStatus) {
	programStatus = newProgramStatus;
	programTime = 0;
	switch(newProgramStatus) {
		case WORKING:
			startCompressor();
		break;
		case RESTING:
			stopCompressor();
		break;
	}
}

void doStarting(void) {
	if(programTime >= STARTINGTIME) {
		if(targetAdcCount == TARGETADCCOUNTMAX) {
			setProgramStatus(RESTING);
		}
		else {
			setProgramStatus(WORKING);
		}
	}
}

void doWorking(void) {
	if(programTime >= WORKINGTIME) {
		setProgramStatus(RESTING);
	}
}

void doResting(void) {
	if(programTime >= RESTINGTIME && targetAdcCount == 0) {
		setProgramStatus(WORKING);
	}
}

void tim1Update(void)	{
	programTime++;
	updateTargetAdcCount();
	switch(programStatus) {
		case STARTING:
			doStarting();
		break;
		case WORKING:
			doWorking();
		break;
		case RESTING:
			doResting();
		break;
	}
}

main() {
	init();	
	
	while (1);
}