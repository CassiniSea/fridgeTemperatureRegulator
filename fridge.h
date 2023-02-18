#define COMPRESSOR_SWITCH_PIN (GPIO_PIN_4)
#define COMPRESSOR_SWITCH_PORT (GPIOD)

void startCompressor(void);
void stopCompressor(void);
uint8_t isNeedStartCompressor(void);
