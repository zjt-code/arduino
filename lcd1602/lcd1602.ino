
#include "i2c.h"
#include "lcd1602.h"

// lcd mylcd(0x20);

void setup() {
uint8_t ret;
  Serial.begin(9600); 
  delay(1000);
  // mylcd.begin();
  // mylcd.print("hello world");
    // // mylcd.print(1,0,"jingtao.zhang");

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
  //lcdSetDDramAddr(0X80);

  //lcd_print("hello world");
  lcd_print(0,2,"hello world");

 // lcdSetDDramAddr(0Xc0);

  lcd_print(1,3,"jingtao.zhang");

  

  pinMode(7, INPUT);
  pinMode(5,INPUT);
}

static bool bInitFlag =false;
void loop()
{
   uint8_t ret;
//   if(!bInitFlag)
//   {     
//             delay(100);
//             ret= lcdSetDDramAddr(0XC0);
//                     Serial.print("status=");
// Serial.println(ret,HEX);
//              delay(100);
//             lcdWriteData('B');
//             lcdWriteData('C');
//             lcdWriteData('a');
//             bInitFlag=true;
//   }
  // {
  //     ret =lcd_set_dl();
  //    Serial.print("set dl ret=");
  //    Serial.println(ret,HEX);
  //    lcdSetFunction();
  //    lcd_clear();
     
  //   //  for(int x=0; x<20; x++)
  //   //  {
  //   //   delay(10);
  //   //   uint8_t status =lcdReadStatus();

  //   //  Serial.print("status=");
  //   //  Serial.println(status,HEX);

  //   //  if((status & 0x80)==0)break;

  //   //  }    
 

  // lcdDisplayOn();
  
  // lcdSetDDramAddr();

  // lcdWriteData('a');
  //   //    for(int x=0; x<20; x++)
  //   //  {
  //   //   delay(10);
  //   //   uint8_t status =lcdReadDateStatus();

  //   //  Serial.print("status=");
  //   //  Serial.println(status,HEX);

  //   //  if((status & 0x80)==0)break;

  //   //  }    
 
  //   lcdWriteData('a');
  //   //      for(int x=0; x<20; x++)
  //   //  {
  //   //   delay(10);
  //   //   uint8_t status =lcdReadDateStatus();

  //   //  Serial.print("status=");
  //   //  Serial.println(status,HEX);

  //   //  if((status & 0x80)==0)break;

  //   //  }    
 
  //     lcdWriteData('a');
  //   //        for(int x=0; x<20; x++)
  //   //  {
  //   //   delay(10);
  //   //   uint8_t status =lcdReadDateStatus();

  //   //  Serial.print("status=");
  //   //  Serial.println(status,HEX);

  //   //  if((status & 0x80)==0)break;

  //   //  }    
 

  //   bInitFlag =true;
  //   Serial.println("lcd init completely!!!!");

  // }

    delay(1000);
    Serial.println("lcd test");
    Serial.println('\0',HEX);

}

// // void loop()
// // {

// //     if(digitalRead(7))
// //     {
// //       Serial.println("IR detected!!!!");
// //     }

// //     if( !digitalRead(5))
// //     {

// //       Serial.println("Obstacle Avoidance detected!!!!");
// //     }
// //     delay(100);
// // }
// void loop(){

 

  //   delay(500);
  //  uint8_t ret= lcdWriteData('a');
  //     Serial.print("set dl ret=");
  // Serial.println(ret,HEX);
    // ii2c_writechar_cmd(0x4E,0b00111001);
    // Serial.println("lcd1602 display\r\rn");
    // delay(1000);
    // ii2c_writechar_cmd(0x4E,0b00111101);
    // Serial.println("lcd1602 display\r\rn");
    // ii2c_writechar_cmd(0x4E,0b00111001);
    // Serial.println("lcd1602 display\r\rn");
    // delay(1000);
    // ii2c_writechar_cmd(0x4E,0b00111101);
    // Serial.println("lcd1602 display\r\rn");

  //   uint8_t buff;
  //   ii2c_read_nosubaddr(0x4E,&buff,1);
    
  // Serial.print("buff ret=");
  // Serial.println(buff,HEX);
  //  delay(10);

    
// }

/*
  Hello World 
  Author: Bonezegei (Jofel Batutay)
  Date:  January 2024
*/

// #include <Bonezegei_LCD1602_I2C.h>

// Bonezegei_LCD1602_I2C lcd(0x20);

// void setup() {
//   lcd.begin();
//   lcd.print("Bonezegei");
//   lcd.setPosition(0, 1);      //param1 = X   param2 = Y
//   lcd.print("HD44780");
//   delay(2000);
//   lcd.setPosition(0, 0);
//   lcd.print("Hello World");
// }

// void loop() {
//   lcd.setPosition(0, 1);
//   String str = "ms:";
//   str += millis();
//   lcd.print(str.c_str());
//   delay(500);
// }


//   / ** Help **
//   https://github.com/locple/LCDI2C_Multilingual
// */

// #include <LCDI2C_Multilingual.h>

// LCDI2C_Generic lcd(0x27, 16, 2);  // I2C address: 0x27; Display size: 20x4

// void setup() {
//   lcd.init();
//   lcd.backlight();

// //   lcd.print("Ernest Miller Hemingway was born in Chicago in 1899 as the son of a doctor\
// //  and the second of six children. After a stint as an ambulance driver at the Italian front,\
// //  Hemingway came home to America in 1919, only to return to the battlefield - this time\
// //  as a reporter on the Greco-Turkish war - in 1922. Resigning from journalism to focus on\
// //  his writing instead, he moved to Paris where he renewed his earlier friendship with fellow\
// //  American expatriates such as Ezra Pound and Gertrude Stein. Through the years, Hemingway\
// //  travelled widely and wrote avidly, becoming an internationally recognized literary\
// //  master of his craft. He received the Nobel Prize for Literature in 1954, following\
// //  the publication of The Old Man and the Sea.", 3); // wait for 3 seconds before each next screen
//   lcd.println();
//   lcd.print("He died in 1961.");

//   lcd.setCursor(8, 2); lcd.println("←÷→");
//   lcd.println("(https://amazon.com)");
// }

// void loop() {}
