#include<reg51.h>
#include"keypad.h"
#include"delay.h"
//#define keypad P1

sbit r3=P1^4;
sbit r2=P1^5;
sbit r1=P1^6;
sbit r0=P1^7;

sbit c0=P1^3;
sbit c1=P1^2;
sbit c2=P1^1;
sbit c3=P1^0;


//unsigned char key_otp[5];
char row_val,col_val;

code char a[][4]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

  void row_init(void)
  {
    r0=r1=r2=r3=0;
  }

  bit col_status(void)
  {
    return(c0&&c1&&c2&&c3);
  }

  char key_scan(void)
  {
    row_init();
   while(col_status());
    r0=0;r1=r2=r3=1;
	if(!col_status())
	 {
	  row_val=0;
	  goto col_check;
	 }

	 r1=0;r0=r2=r3=1;
	if(!col_status())
	 {
	  row_val=1;
	  goto col_check;
	 }

	  r2=0;r0=r1=r3=1;
	if(!col_status())
	 {
	  row_val=2;
	  goto col_check;
	 }

	  r3=0;r0=r2=r1=1;
	if(!col_status())
	 {
	  row_val=3;
	  goto col_check;
	 }

	 col_check:
	        if(c0==0)
			  col_val=0;
			  else if(c1==0)
			   col_val=1;
			   else if(c2==0)
			    col_val=2;
				else
				 col_val=3;
        while(!col_status());
			delay_ms(100);
		 return(a[row_val][col_val]);
}

