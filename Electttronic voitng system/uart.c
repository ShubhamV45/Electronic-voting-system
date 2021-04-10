#include<reg51.h>
#include"uart.h"
#include"type.h"
#include"lcd.h"
#include"delay.h"


bit r_flag,t_flag;
u8 ch=0,k,rec_buff[25];
u8 flag=0;

void serial_int(void) interrupt 4
{
 if(TI==1)
  {
    t_flag=1;
    TI=0;
  }
if(RI==1)
  {
   ch=SBUF;


   if(ch==0x02)
		flag=1;
	else if((flag==1)&&(ch!=0x03)) 
   		rec_buff[k++]=ch;
    else if(ch==0x03)
      {
        r_flag=1;flag=0;
		rec_buff[k]='\0';
        // strcpy(main_buff,rec_buff);
         k=0;
       }
	
		RI=0;
//  lcd_char(ch);
   }

}


void uart_inti()
{
  SCON=0x50;
  TMOD=0x20;
  TH1=TL1=0xFD; //set baudrate
  TR1=1;    // timer run
 IE=0x90;//ea=globle interrupt enable,es=serial interface

}

 

/*char uart_Rxint(void)
{
 while(RI==0);
  RI=0;
  return(SBUF);
}*/



void uart_Txchar(char ch)
 {
   SBUF=ch;
  while(t_flag==0);
   t_flag=0;
  }

void uart_str(unsigned char *str)
{
while(*str)
uart_Txchar(*str++);

}

 



