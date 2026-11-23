#include<lpc21xx.h>
#include"header.h"

  volatile u8 h,m,s,da,mo,ye,soil=10,water,rai,flame,pir,temp,humid,lig;
 u32 hexa(u8 c){
  return ((c/16)*10)+(c%16);
  }
  
  void eeprom_store()
  {
  i2c_write(0xA0,0x2,hrs);
  delay_ms(10);
i2c_write(0xA0,0x3,min);
 delay_ms(10);
i2c_write(0xA0,0x4,sec);
 delay_ms(10);
 i2c_write(0xA2,0x2,date);
 delay_ms(10);
i2c_write(0xA2,0x3,month);
 delay_ms(10);
 i2c_write(0xA2,0x4,year);
 delay_ms(10);
 i2c_write(0xA4,0x2,soil_moisture);
 delay_ms(10);
i2c_write(0xA4,0x3,water_level);
 delay_ms(10);
 i2c_write(0xA4,0x4,temparature);
 delay_ms(10);
 i2c_write(0xA4,0x5,humidity);
 delay_ms(10);
 i2c_write(0xA4,0x6,RAIN);
 delay_ms(10);
 i2c_write(0xA4,0x7,light);
 delay_ms(10);
 i2c_write(0xA4,0x8,FLAME);
 delay_ms(10);
 i2c_write(0xA4,0X9,PIR);
 delay_ms(10);
 }
 
 void eeprom_read(){
 h=i2c_read(0xA1,0x2);
 m=i2c_read(0xA1,0x3);
 s=i2c_read(0xA1,0x4);
 da=i2c_read(0xA3,0x2);
 mo=i2c_read(0xA3,0x3);
 ye=i2c_read(0xA3,0x4);
 if(h>0x12)
         {
                 u8 k=h-0x12;
 uart_tx_integer(hexa(k));
         }
         else{
         uart_tx_integer(hexa(h));
 }

 uart_tx(':');
 uart_tx_integer(hexa(m));
 uart_tx(':');
 uart_tx_integer(hexa(s));
         if(h>=0X12){
 uart_tx_string(" PM\r\n");
         }
         else{
                 uart_tx_string(" AM\r\n");
         }
 uart_tx_integer(hexa(da));
uart_tx('/');
 uart_tx_integer(hexa(mo));
 uart_tx('/');
 uart_tx_integer(20);
 uart_tx_integer(hexa(ye));
 uart_tx_string("\r\n");
soil=i2c_read(0xA5,0x2);//  u8(soil_moisture)
 uart_tx_string("soil moisture: ");
 uart_tx_integer(soil);
 uart_tx_string("%\r\n");
 water=i2c_read(0xA5,0x3);// u8(water_level)
 uart_tx_string("water level: ");
 uart_tx_integer(water);
 uart_tx_string("%\r\n");
 temp=i2c_read(0xA5,0x4);// u8(temparature)
 uart_tx_string("Temparature:");
 uart_tx_integer(temp);
 uart_tx_string("°C\r\n");
 humid=i2c_read(0xA5,0x5);// u8(humidity)
uart_tx_string("Humidity: ");
 uart_tx_integer(humid);
 uart_tx_string("%\r\n");
 rai=i2c_read(0xA5,0x6);// u8(RAIN)
 uart_tx_string("Rain: ");
 uart_tx_integer(rai);
uart_tx_string("\r\n");
 lig=i2c_read(0xA5,0x7);// u8(light)
 uart_tx_string("Light: ");
 uart_tx_integer(lig);
 uart_tx_string("%\r\n");
 flame=i2c_read(0xA5,0x8);// u8(FLAME)
 uart_tx_string("Flame: ");
 uart_tx_integer(flame);
 uart_tx_string("\r\n");
 pir=i2c_read(0xA5,0X9);// u8(PIR)
uart_tx_string("Pir: ");
 uart_tx_integer(pir);
 uart_tx_string("\r\n");
 }
