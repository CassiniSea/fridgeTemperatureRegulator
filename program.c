#include "program.h"
#include "fridge.h"
#include "adc.h"
#include "uart.h"

uint8_t programStatus = STARTING;
uint32_t programTime = 0;

void updateProgramStatus(void) {
	programTime++;
	switch(programStatus) {
		case STARTING:
			doStarting();
		break;
		case SETTING_WORKING:
			doSettingWorking();
		break;
		case WORKING:
			doWorking();
		break;
		case SETTING_RESTING:
			doSettingResting();
		break;
		case RESTING:
			doResting();
		break;
	}
}

void setProgramStatus(uint8_t newProgramStatus) {
	programStatus = newProgramStatus;
	programTime = 0;
}

void doStarting(void) {
	if(programTime >= STARTING_TIME && isNeedStartCompressor()) {
		setProgramStatus(SETTING_WORKING);
	}
}

void doSettingWorking(void) {
	startCompressor();
	setProgramStatus(WORKING);
}

void doWorking(void) {
	if(programTime >= WORKING_TIME) {
		setProgramStatus(SETTING_RESTING);
	}
}

void doSettingResting(void) {
	stopCompressor();
	setProgramStatus(RESTING);
}

void doResting(void) {
	if(programTime >= RESTING_TIME && isNeedStartCompressor()) {
		setProgramStatus(SETTING_WORKING);
	}
}

void sendStats(void) {
	uartSendByte(getAdcData());
	uartSendByte(getTargetAdcCount());
	uartSendByte(programStatus);
}