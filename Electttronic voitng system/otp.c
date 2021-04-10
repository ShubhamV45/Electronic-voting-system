#include<reg51.h>
#include<stdlib.h>
#include"lcd.h"
#include"keypad.h"
#include"delay.h"

unsigned char otp[5],key_otp[5]; 


void otp_gen(void)
{
  int i,n;
  for(i=0;i<4;i++)
  {
     n=rand()%8+1;
    otp[i]=n+48;
   }

   otp[i]='\0';

 }

/*void  key_press(void)
{
  
  int i,n;

  for(i=0;i<4;i++)
  { 
    n=key_scan();
    key_otp[i]=n-48;
  	lcd_char('*');
  }
    delay_ms(1000);
	key_otp[i]='\0';
}*/
