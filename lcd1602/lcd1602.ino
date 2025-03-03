
#include "i2c.h"
#include "lcd1602.h"



void setup() {

  Serial.begin(9600);
  // lcd.init();
  // // Wire.
  // lcd.backlight();
  // lcd.print("Hello World!");
  delay(100);
  Init_I2c();
   uint8_t ret =lcd_set_dl();

  Serial.print("set dl ret=");
  Serial.println(ret,HEX);

  lcdDisplayOn();
  lcdSetDDramAddr();
  lcdWriteData('a');
  pinMode(7, INPUT);
  pinMode(5,INPUT);


}

void loop()
{

    if(digitalRead(7))
    {
      Serial.println("IR detected!!!!");
    }

    if( !digitalRead(5))
    {

      Serial.println("Obstacle Avoidance detected!!!!");
    }
    delay(100);
}
// void loop(){

 

//   //   delay(500);
//   //  uint8_t ret= lcdWriteData('a');
//   //     Serial.print("set dl ret=");
//   // Serial.println(ret,HEX);
//     ii2c_writechar_cmd(0x40,0b00111001);
//     Serial.println("lcd1602 display\r\rn");
//     delay(1000);
//     ii2c_writechar_cmd(0x40,0b00111101);
//     Serial.println("lcd1602 display\r\rn");

//     uint8_t buff;
//     ii2c_read_nosubaddr(0x40,&buff,1);
    
//   Serial.print("buff ret=");
//   Serial.println(buff,HEX);
//    delay(10);

    
// }
