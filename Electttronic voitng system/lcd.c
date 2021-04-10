#include<reg51.h>
#include"delay.h"
#include"lcd.h"

#define LCD P0


sbit rs=P3^4; //lcd pins
sbit rw=P3^5;
sbit en=P3^6;




void lcd_disp(unsigned char ch)
{
rw=0;
LCD=ch;
en=1;
en=0;
delay_ms(2);
}


void lcd_char(unsigned int ch)
{
rs=1;
lcd_disp(ch);
}

void lcd_str(unsigned char *p)
{
while(*p!='\0')
 lcd_char(*p++);
}




void lcd_cmd(unsigned char cmd)
{
rs=0;
lcd_disp(cmd);
}

void lcd_init()
{
 
 lcd_cmd(0x30);
 delay_ms(16);
 lcd_cmd(0x30);
 delay_ms(1);
 lcd_cmd(0x30);
 delay_ms(1);

 lcd_cmd(0x38);
 lcd_cmd(0x10);
 lcd_cmd(0x06);
 lcd_cmd(0x01);
 lcd_cmd(0x0f);
}





