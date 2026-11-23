#include<lpc21xx.h>
#include"header.h"
 
  // scl-0.2 sda-0.3
  volatile u8 hrs,min,sec,date,month,year,am_pm;
 
  void get_time(void)
  {
            hrs=i2c_read(0xD1,0x2);//read hrs
            min=i2c_read(0xD1,0x1);//read mins
           sec=i2c_read(0xD1,0x0);//read secs
  }
  void set_time(u8 hours,u8 minutes,u8 seconds)
  {
      i2c_write(0xD0,0x02,hours);
      i2c_write(0xD0,0x01,minutes);
      i2c_write(0xD0,0x00,seconds);
  }
  void set_date(u8 date,u8 month,u8 year)
  {
      i2c_write(0xD0,0x04,date);
      i2c_write(0xD0,0x05,month);
      i2c_write(0xD0,0x06,year);
  }
 
  void get_date(void)
  {
      date  = i2c_read(0xD1,0x04);
      month = i2c_read(0xD1,0x05);
      year  = i2c_read(0xD1,0x06);
  }
  void display_time(){
  //get_time();
          if(hrs>0x12)
          {
                  u8 h=hrs-0x12;
  am_pm=1;
  uart_tx(((h)/16)+48);
  uart_tx(((h)%16)+48);
          }
          else{
          am_pm=0;
                  uart_tx((hrs/16)+48);
      uart_tx((hrs%16)+48);
          }
 
  uart_tx(':');
  uart_tx((min/16)+48);
  uart_tx((min%16)+48);
  uart_tx(':');
  uart_tx((sec/16)+48);
  uart_tx((sec%16)+48);
          if(hrs>=0X12){
  uart_tx_string(" PM\r\n");
          }
          else{
                  uart_tx_string(" AM\r\n");
          }
  }
 
  void display_date(){
  //get_date();
  uart_tx((date/16)+48);
  uart_tx((date%16)+48);
  uart_tx('/');
  uart_tx((month/16)+48);
 uart_tx((month%16)+48);
  uart_tx_string("/20");
  uart_tx((year/16)+48);
  uart_tx((year%16)+48);
  uart_tx_string("\r\n");
  }
