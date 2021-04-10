#include<reg51.h>
#include<string.h>
#include<stdlib.h>


/*** USER DEFIND HEADER FILE ***/ 
	#include"lcd.h"
	#include"delay.h"
	#include"keypad.h"
	#include"uart.h"
	#include"type.h"
	#include"i2c.h"
	#include"otp.h"

sbit led=P2^7;
code u8 voter[][10]={"12563773","12621259","12332145","12555657"};// random RFID numbers 
extern u8 rec_buff[25],k,otp[5];
extern bit r_flag;
unsigned char scan_otp[5]; 

int main()
{
 
 u8 buffaddr=0;
  u8 party,party_1set=0,party_2set=0,party_3set=0,ch2;
  u8 party1_total=0,party2_total=0,party3_total=0,reset;
 int i,j,cnt_1=0,cnt_2=0, cnt_3=0,temp1=0,temp2=0, temp3=0;
 led=0;
 uart_inti();
 lcd_init();
 lcd_str("wait..");
 
 while(1)
  {

    uart_str("Waiting data...");
    lcd_cmd(0x01);
    lcd_cmd(0x80);
	lcd_str("{Ele. Voting System}");
	delay_ms(2000);
    lcd_cmd(0x01);
    
  	
   memset(rec_buff,'\0',25);
lcd_cmd(0xc0);

 lcd_str("Waiting for data!!");
    while(r_flag==0);
	r_flag=0;k=0;
    lcd_cmd(0x01);
 	lcd_cmd(0x94);
	lcd_str("Data Received..");
	delay_ms(1000);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("Data is:\n");
	lcd_cmd(0xc0);
    lcd_str(rec_buff);	
	delay_ms(500);
   
	 for(i=0;i<4;i++)
      {
			
      if((strcmp(rec_buff,voter[i])==0))
    	break ;
       }
       
			if(i==4)
	 		 {
				lcd_cmd(0x80);
				lcd_str("invalid");
				led=0;
				delay_ms(2000);
				led=1;
				delay_ms(1000);
	    	  }

		 	else if(i==3)
		    {
				lcd_str(0x01);		
				lcd_cmd(0x80);
				lcd_str("OFFICER>>>");
				delay_ms(1000);
				otp_gen();
      			lcd_cmd(0x01);
	        	lcd_cmd(0x94);
 				lcd_str("OTP..: ");
            	lcd_cmd(0xd4);
				lcd_str(otp);
				delay_ms(1500);
            	lcd_cmd(0xc0);
			
			/*	for(i=0;i<5;i++)
  				{ 
							if(i==4)
								{  scan_otp[4]='\0';
									break;
								}
						scan_otp[i]=key_scan();
						if(scan_otp[i]=='D')
						{
							i=i-2;
							lcd_cmd(0x10);
							lcd_char(' ');
							lcd_cmd(0x10);
						}
						else
							lcd_char('*');
				} */j=0;
						while(1)
						{
						here:
						scan_otp[j]=key_scan();
								if(scan_otp[j]=='#' && j==0)
								{
								lcd_cmd(0x80);
								lcd_str("not entered");
								delay_ms(1000);
								lcd_cmd(0x01);
								j++;
								goto here;
								}
								else if(scan_otp[j]=='D' && j!=0)
								{
								lcd_cmd(0x10);
								lcd_char(' ');
								lcd_cmd(0x10);
								j--;
								continue;
								}
								else if(scan_otp[j]=='#')
								{
								scan_otp[j]='\0';
								break;
								}
								else
								{
								lcd_char(scan_otp[j]);
								delay_ms(1000);
								lcd_cmd(0x10);
								lcd_char('*');
								j++;
								}
						}
						
					lcd_cmd(0x94);
					lcd_str("press #");
					while(!(key_scan()=='#'));
						delay_ms(200);
   
			if(strcmp(otp,scan_otp)==0)
				{	
					lcd_cmd(0xd4);
 			    	lcd_str("OTP matched");
					delay_ms(500);
					lcd_cmd(0x01);
					lcd_cmd(0xd4);
					party1_total=i2c_dev_read(0xa0,4);
					party2_total=i2c_dev_read(0xa0,5);
					party3_total=i2c_dev_read(0xa0,6);

					
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("party1=>[A]=");
        			lcd_char(party1_total);
					delay_ms(300);
		
					lcd_cmd(0xc0);
					lcd_str("party2=>[B]=");
        			lcd_char(party2_total);
					delay_ms(300);
   						
					lcd_cmd(0x94);
					lcd_str("party3=>[C]=");
        			lcd_char(party3_total);
					delay_ms(5000);
                   temp1=party1_total+48;
					temp2=party2_total+48;
						temp3=party3_total+48;
                      if(temp1>temp2 && temp1>temp3)
						{
							lcd_cmd(0xd4);
							lcd_str("A has won!");
							delay_ms(1000);
						}
					 else if(temp2>temp1 && temp2>temp3)
						{
							lcd_cmd(0xd4);
							lcd_str("B has won!");
							delay_ms(1000);
						}
				      else if(temp3>temp2 && temp3>temp1)
						{
							lcd_cmd(0xd4);
							lcd_str("C has won!");
							delay_ms(1000);
						}
						else
						{lcd_cmd(0xd4);
							lcd_str("no winner");
							delay_ms(1000);
						}
										

				}
				else
				{
						lcd_str("wrong *otp*");
				 			led=1;
							delay_ms(5000);
							led=0;
							
				}
       
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("[4]Reset ");
                 reset=key_scan();
				  if(reset=='4')
				 { for(i=0;i<=6;i++)
				   { i2c_dev_write(0xa0,i,'0'); }lcd_str("reset comp...");delay_ms(500); }
				  else 
				  { 
					lcd_str("Not reset"); 
					delay_ms(500); 
					}
           

			}
 	 	else
	    {	

  				
  		
		    lcd_cmd(0x94);
			lcd_str("valid card");
  			delay_ms(1000);
           	ch2=i2c_dev_read(0xa0,i);
			if(ch2=='0')
			{
					 lcd_cmd(0x01);
			 		lcd_cmd(0x80);
			 		lcd_str("voting not done!");
 					delay_ms(1000);
					otp_gen();
      		 		lcd_cmd(0x01);
	       		    lcd_cmd(0x94);
 					lcd_str("OTP : ");
            		lcd_cmd(0xd4);
					lcd_str(otp);
					delay_ms(1000);
            		lcd_cmd(0xc0);

						
                      for(j=0;j<5;j++)
  				   	   { 
							if(j==4)
								{
									scan_otp[j]='\0';
									break;
							 	}
						scan_otp[j]=key_scan();
						   
							if(scan_otp[j]=='D')
					     		{
						       		j=j-2;
							   		lcd_cmd(0x10);
						    		lcd_char(' ');
							    	lcd_cmd(0x10);
					     		}
							else
								lcd_char('*');
						} // for
					
					lcd_cmd(0x94);
					lcd_str("press #");
					while(!(key_scan()=='#'));
						delay_ms(1000);
											
 					 
						
				if(strcmp(otp,scan_otp)==0)
				  {
 			    	lcd_str("valid otp");
                    lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("Party-1==>[A]");
					lcd_cmd(0xc0);
					lcd_str("Party-2==>[B]");
					lcd_cmd(0x94);
					lcd_str("Party-3==>[C]");
					party=key_scan();

                     switch(party)
					  {
					    case 'A':
									party_1set++;
									cnt_1=party_1set+48;
									i2c_dev_write(0xa0,4,cnt_1);
									i2c_dev_write(0xa0,i,'1');
									lcd_cmd(0xd4);
									lcd_str("vote done A");
									delay_ms(2500);
								//	goto UP;
									break;
						case 'B':
									party_2set++;
									cnt_2=party_2set+48;
									i2c_dev_write(0xa0,5,cnt_2);
									i2c_dev_write(0xa0,i,'1');
									lcd_cmd(0xd4);
									lcd_str("vote done B");
									delay_ms(2500);
								//	goto UP;
									break;
						case 'C':
									party_3set++;
									cnt_3=party_3set+48;
									i2c_dev_write(0xa0,6,cnt_3);
									i2c_dev_write(0xa0,i,'1');
									lcd_cmd(0xd4);
									lcd_str("vote done C");
									delay_ms(2500);
								//	goto UP;
									break;
						default :
									lcd_cmd(0x80);
 									lcd_str("invalid press");
									led=1;
									delay_ms(1000);
									led=0;
									//goto UP;

						} // switch
				
					} // if cmp otp
		    	  else
				   {
					lcd_cmd(0x94);
					lcd_str("invalid otp");
					led=1;
					delay_ms(5000);
					led=0;
			    	} 
			
				

  			

				}// if ch2 cmp

          else if(ch2=='1')
				{
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("voting done");
					delay_ms(1000);
                   
				}
		
        // } //for
			        
 		}  // else voter
     
   }//while


   

  }//main
