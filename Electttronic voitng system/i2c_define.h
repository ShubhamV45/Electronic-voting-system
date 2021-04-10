#ifndef i2c_define_h
#define i2c_define_h


#include<reg51.h>
sbit sda=P2^0;
sbit scl=P2^1;

#define Page_write_en 0
#define Seq_read_en 0
#define Master_ack_en 0

#endif
