
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

/**** clear display*****/
#define LCD_IR_CLEAR            0X01

/*function set command: 
 0 0 1 DL   N F — —  
 DL: Data length,
 -----> 1: 8 bits mode, 0: 4 bits mode,
 N: number of display lines,
 -----> 1: 2 lines, 0: 1 line
 F: Character Font
 -----> 1: 5*10 ,0: 5*8
 ****/
#define LCD_IR_SET_DL           0X28

/* Display  on/off  control 
0 0 0 0 1 D C B   
D: Display on /off , 
---->1 : on  , 0:0ff
C :cursor on/off, 
---->1 : on  , 0:0ff
B: blink of cursor position character
---->1 : on  , 0:0ff  
****/
#define LCD_IR_DIS_ON           0X0C

/******
Set  DDRAM  address
1 ADD ADD ADD ADD ADD ADD ADD   ****/
#define LCD_IR_SET_DDADRESS     (0X80|0X42)


#define LCD_IR_RET_HOME         0X02

#define ERR_CMD_OK              0X00


static uint8_t slaveAddr = (0x20<<1);


//  void lcd::IIC_delay1us(uint16_t delay)

 void IIC_delay1us(uint16_t delay)
{
	uint32_t i;
	i = delay << 3;  //  ?1us  ?8    ?delay * 8
	for(;i>0;i--) ;
}


// void lcd::delay(uint16_t delay)
void delay(uint16_t delay)
{
    for(uint16_t x=0; x< delay; x++)
    {
      IIC_delay1us(1000);
    }
}


void begin()
// void lcd::begin()
{
  Init_I2c();
  lcd_set_dl(0x30); // 8 bit interface mode
  delay(20);
  lcd_set_dl(0x30); // 8 bit interface mode
  delay(20);
  lcd_set_dl(0x30); // 8 bit interface mode
  delay(20);
  lcd_set_dl(0x20); //  set 4bit interface
  lcdSetFunction();   //set functins 
  lcd_clear();  
  lcdDisplayOn();  
  lcdSetDDramAddr(0X80);
}


// set date length , 4bits length
// this command execut in 8 bits data length
// uint8_t lcd::lcd_set_dl(uint8_t dl_cmd)
uint8_t lcd_set_dl(uint8_t dl_cmd)
{

  uint8_t ret =  ii2c_writechar_cmd(slaveAddr,dl_cmd |0x08);  //Set PIN E high
    IIC_delay1us(20);
    ret= ii2c_writechar_cmd(slaveAddr,dl_cmd|0x08| 0x04);  // Set Pin E Low
   IIC_delay1us(20);
   ret =  ii2c_writechar_cmd(slaveAddr,dl_cmd |0x08);  //Set PIN E high
  IIC_delay1us(20);
   return ret;
  
}


uint8_t  lcdWriteCommand(uint8_t command)

// uint8_t  lcd::lcdWriteCommand(uint8_t command)
{
//0: rs,  1: w/r ,2: E pin   3: Backlight
 uint8_t high4Bytes = (command & 0xf0) | 0x08;  // 0x08 backlight control pin

  /*** High 4 bits*/  
  uint8_t ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E LOW
  
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E high, toggle E, latch 

  ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E LOW
  
/****** low 4 bits*****/

  high4Bytes = (command<<0x04)|0x08;

   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low

   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E High
  
    ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E Low


  for(int x=0; x<1000; x++)
  {
    uint8_t status = lcdReadStatus();

    if((status &0x80)!=0x80){return 0;}
  }
  
   return 0x01;
}


// uint8_t lcd::lcdWriteData(uint8_t data)
uint8_t lcdWriteData(uint8_t data)
{

 uint8_t high4Bytes = (data & 0xf0)|0x08|0x01;  // 0x08 backlight control pin,x01 Data register

  /*** High 4 bits*/
  
  uint8_t ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin H 
  
   ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E Low, toggle , latch 

  ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin H 
   
/****** low 4 bits*****/ 

  high4Bytes = (data<<0x04)|0x08|0x01;         //x01 Date register

  ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E High
 
  ret= ii2c_writechar_cmd(slaveAddr,high4Bytes|0x04);  // Set Pin E Low
 
  ret= ii2c_writechar_cmd(slaveAddr,high4Bytes);  // Set Pin E High
   return ret;
}


// uint8_t lcd::lcdReadStatus(void)
uint8_t lcdReadStatus(void)
{
    // RS:0, W/R :1 ,Toggle E
    uint8_t buff;
    uint8_t ret;
    // read high 4 bits
    ii2c_writechar_cmd(slaveAddr,0xf8|0x02);  // Set Pin E Low,0x02: read  
    ii2c_writechar_cmd(slaveAddr,0xf8|0x04|0x02);  // 0x04:Set Pin E High, 0x02: read
    ii2c_read_nosubaddr(slaveAddr,&buff,1);
   // ii2c_writechar_cmd(slaveAddr,0xf8);  // Set Pin E Low,0x02: read   
    // ii2c_read_nosubaddr(slaveAddr,&buff,1);

    ret = buff&0xf0;
    // read low 4 bits
    ii2c_writechar_cmd(slaveAddr,0xf8|0x02);  // Set Pin E Low,end read 
    ii2c_writechar_cmd(slaveAddr,0xf8|0x04|0x02);  // 0x04:Set Pin E High, 0x02: read   
    ii2c_read_nosubaddr(slaveAddr,&buff,1);
    ii2c_writechar_cmd(slaveAddr,0xf8);  // Set Pin E Low, rs 0, w/r 0
    // ii2c_read_nosubaddr(slaveAddr,&buff,1);

    ret |= (buff>>4);
    return ret;

}


// uint8_t lcdReadDateStatus()
// {

//       // RS:1, W/R :1 ,Toggle E
//     uint8_t buff;
//     uint8_t ret;
//     // read high 4 bits
//     ii2c_writechar_cmd(slaveAddr,0xf9|0x04|0x02);  // 0x04:Set Pin E High, 0x02: read
//     ii2c_read_nosubaddr(slaveAddr,&buff,1);
//     ii2c_writechar_cmd(slaveAddr,0xf9|0x02);  // Set Pin E Low,0x02: read   

//     ret = buff&0xf0;
//     // read low 4 bits
//     ii2c_writechar_cmd(slaveAddr,0xf9|0x04|0x02);  // 0x04:Set Pin E High, 0x02: read   
//     ii2c_read_nosubaddr(slaveAddr,&buff,1);
//     ii2c_writechar_cmd(slaveAddr,0xf9|0x00);  // Set Pin E Low,end read

//     ret |= (buff>>4);
//     return ret;
// }


// void lcd::lcd_clear(void)
void lcd_clear(void)
{
  lcdWriteCommand(LCD_IR_CLEAR);
}


uint8_t lcdSetFunction(void)

// uint8_t lcd::lcdSetFunction(void)
{

  return lcdWriteCommand(LCD_IR_SET_DL);
}

// 4 bit data length
uint8_t lcdDisplayOn()
// uint8_t lcd::lcdDisplayOn()
{
     return lcdWriteCommand(LCD_IR_DIS_ON);
}

uint8_t lcdSetDDramAddr(uint8_t addr)
// uint8_t lcd::lcdSetDDramAddr(uint8_t addr)
{
     return lcdWriteCommand(addr);
}

uint8_t lcdReturnHome()
// uint8_t lcd::lcdReturnHome()
{
  return lcdWriteCommand(LCD_IR_RET_HOME);
}


// void lcd::print(uint8_t row,uint8_t col,char *str="")
void lcd_print(uint8_t row, uint8_t col, char*str)
{
  uint8_t row_addr[] = {0x00,0x40};
  lcdSetDDramAddr((row_addr[row]+col)|0x80);
  while(*str){
    lcdWriteData(*str++);
  }
}
