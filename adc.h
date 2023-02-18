#define TARGET_ADC 115
#define TARGET_ADC_COUNT_MAX 10

void adcInit(void);
uint8_t getAdcData(void);
void updateTargetAdcCount(void);
uint8_t getTargetAdcCount(void);