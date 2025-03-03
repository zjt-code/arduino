
#include "lcd1602.h"
#include  "i2c.h"

/**** I2C IC  PCF8574T ************
**** IC Pins,   lcd pin   ,descrpitons
****     P0     RS        0: Instruction register (for write) Busy flag:address counter (for read)1: Data register (for write and read)
**       P1     R/W       0: Write，1: Read
****     P2     E         Starts data read/write.
**       P3     x         back light
****     P4     D4
**       P5     D5
****     P6     D6
**       P7     D7
*****/
/*
Table 1 Register Selection
RS R/W Operation
0 0 IR write as an internal operation (display clear, etc.)
0 1 Read busy flag (DB7) and address counter (DB0 to DB6)
1 0 DR write as an internal operation (DR to DDRAM or CGRAM)
1 1 DR read as an internal operation (DDRAM or CGRAM to DR)
*/

#define LCD_IR_CLEAR            0X01
#define LCD_IR_SET_DL           0X20
#define LCD_IR_DIS_ON           0X0f
#define LCD_IR_SET_DDADRESS     0X80

#define ERR_CMD_OK              0X00


static uint8_t slaveAddr = 0x40;

void lcd_clear()
{


}


static void IIC_delay1us(uint16_t delay)
{
	uint32_t i;
	i = delay << 3;  //  ?1us  ?8    ?delay * 8
	for(;i>0;i--) ;
}


// set date length , 4bits length
// this command execut in 8 bits data length
uint8_t lcd_set_dl(void)
{

   uint8_t ret= ii2c_writechar_cmd(slaveAddr,LCD_IR_SET_DL|0x08);  // Set Pin E Low

   IIC_delay1us(20);
   ret =  ii2c_writechar_cmd(slaveAddr,LCD_IR_SET_DL | 0x04|0x08);  //Set PIN E high
   IIC_delay1us(20);
   return ret;
  
}



uint8_t  lcdWriteCommand(uint8_t command)
{

 uint8_t high4Bytes = (command & 0xf0) | 0x08;  // 0x08 backlight control pin

  /*** High 4 bits*/
  
  uint8_t ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low
   IIC_delay1us(20);
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x40);  // Set Pin E High, toggle E, latch 

/****** low 4 bits*****/

  high4Bytes = (command<<0x04)|0x08;

   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low
   IIC_delay1us(20);
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E High

  IIC_delay1us(20);

   return ret;
}


uint8_t  lcdWriteData(uint8_t data)
{

 uint8_t high4Bytes = (data & 0xf0) | 0x08|0x01;  // 0x08 backlight control pin,x01 Date register

  /*** High 4 bits*/
  
  uint8_t ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low
   IIC_delay1us(20);
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x40);  // Set Pin E High, toggle E, latch 

/****** low 4 bits*****/

  high4Bytes = (data<<0x04)|0x08|0x01;         //x01 Date register

   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low
   IIC_delay1us(20);
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E High

  IIC_delay1us(20);

   return ret;
}




// 4 bit data length
uint8_t lcdDisplayOn()
{
     return lcdWriteCommand(LCD_IR_DIS_ON);
}

uint8_t lcdSetDDramAddr()
{
     return lcdWriteCommand(LCD_IR_SET_DDADRESS);
}

// uint8_t lcd

