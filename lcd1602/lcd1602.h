#include <inttypes.h>

void lcd_clear();
uint8_t lcd_set_dl(void);
uint8_t lcdDisplayOn();
uint8_t lcdSetDDramAddr();
uint8_t lcdWriteData(uint8_t data);
