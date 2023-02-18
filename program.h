#include "stm8s.h"

#define STARTING_TIME 600
#define WORKING_TIME 400
#define RESTING_TIME 700

#define STARTING 0
#define SETTING_WORKING 1
#define WORKING 2
#define SETTING_RESTING 3
#define RESTING 4

void updateProgramStatus(void);
void setProgramStatus(uint8_t);
void doStarting(void);
void doSettingWorking(void);
void doWorking(void);
void doSettingResting(void);
void doResting(void);
void sendStats(void);