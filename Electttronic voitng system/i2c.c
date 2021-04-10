#include<reg51.h>
#include"i2c_define.h"
#include"delay.h"
#include"type.h"
#include"i2c.h"


void i2c_start(void)
{
 //sda=1;
 //scl=1;
 sda=1;
 scl=1;
 sda=0;
}


void i2c_write(u8 dat)
{
u8 i;
for(i=0;i<8;i++)
 {
  scl=0;
  sda=dat&(0x80>>i)?1:0;
  //sda=dat&(0x80>>i);
    
  scl=1;
 }
}


void i2c_ack(void)
{
 scl=0;
sda=1;
scl=1;
while(sda);
}

void i2c_stop(void)
{
 scl=0;
 sda=0;
 scl=1;
 sda=1;
}

void i2c_restart(void)
{
 scl=0;
 sda=1;
 scl=1;
 sda=0;
}

void i2c_noack(void)
{
 scl=0;
 sda=1;
 scl=1;
}

#if Master_ack_en >0
 
 void i2c_master_ack(void)
{
scl=0;
sda=0;
scl=1;
scl=0;
sda=1;
}

#endif
 
u8 i2c_read(void)
{
  u8 i,buff=0;
  for(i=0;i<8;i++)
  {
    scl=0;
    scl=1;
   if(sda)
      buff|=0x80>>i;
   }
  return buff;
}

void i2c_dev_write(u8 slaveaddrW,u8 buffWaddr,u8 dat)
 {

i2c_start();
i2c_write(slaveaddrW);
i2c_ack();
i2c_write(buffWaddr);
i2c_ack();
i2c_write(dat);
i2c_ack();
i2c_stop();
delay_ms(10);
}

u8 i2c_dev_read(u8 slaveaddrW,u8 buffRaddr)
{
 u8 buff;
i2c_start();
i2c_write(slaveaddrW);
i2c_ack();
i2c_write(buffRaddr);
i2c_ack();
i2c_restart();
i2c_write(slaveaddrW | 1);
i2c_ack();
buff=i2c_read();
i2c_noack();
i2c_stop();
return buff;
}


#if Page_write_en > 0
void i2c_dev_page_Write(u8 slaveAddr,u8 buffstartAddr,u8 *str,u8 size)
 {
  u8 i; 
  i2c_start();
  i2c_write(slaveAddr);
  i2c_ack();
  i2c_write(buffstartAddr);
  i2c_ack();
  for(i=0;i<size;i++)
   {
    i2c_write(*str++);
    i2c_ack();
   }
  i2c_stop();
  delay_ms(10);
}

#endif

#if Seq_read_en > 1
  void i2c_dev_seq_Read(u8 slaveAddr,u8 buffstartAddr,u8 *str,u8 size)
	{
		u8 i;
		i2c_start();
		i2c_write(slaveAddr);
		i2c_ack();
		i2c_write(buffstartAddr);
		i2c_ack();
		i2c_restart();
		i2c_write(slaveAddr | 1);
		i2c_ack();
		for(i=0;i<size-1;i++)
  		{
			str[i]=i2c_read();
			i2c_master_ack();
		}
		str[i]='\0';
		i2c_noack();
		i2c_stop();
	}
#endif 
			
 		 
 





