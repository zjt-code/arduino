#include <inttypes.h>

void lcd_clear();
uint8_t lcd_set_dl(uint8_t dl_cmd);
uint8_t lcdDisplayOn();
uint8_t lcdSetDDramAddr(uint8_t);
uint8_t lcdWriteData(uint8_t data);
uint8_t lcdSetFunction();
uint8_t lcdReturnHome();
uint8_t lcdReadStatus();
void lcd_print(uint8_t row, uint8_t col, char*str);

uint8_t lcdReadDateStatus();

// class lcd{

// public:
//   lcd(uint8_t addr) {
//     slaveAddr = addr<<1;
//   }
//   void begin(void);
//   void lcd_clear(void);
//   // void print(uint8_t row,uint8_t col,char *str="");
//   void print(char *str);

// private:
//   void IIC_delay1us(uint16_t delay);
//   void delay(uint16_t delay);
//   uint8_t lcd_set_dl(uint8_t dl_cmd);

//   uint8_t lcdReadStatus(void);

//   uint8_t lcdWriteCommand(uint8_t command);
//   uint8_t lcdWriteData(uint8_t data);

//   uint8_t lcdSetFunction(void);
//   uint8_t lcdDisplayOn(void);
//   uint8_t lcdReturnHome();
//   uint8_t lcdSetDDramAddr(uint8_t addr);
 

  

// private:
//   uint8_t slaveAddr;
// };
