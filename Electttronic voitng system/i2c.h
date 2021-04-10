#ifndef i2c_h
#define i2c_h


#include"type.h"
void i2c_start(void);
void i2c_restart(void);
void i2c_write(u8);
void i2c_ack(void);
void i2c_noack(void);
void i2c_stop(void);
void i2c_master_ack(void);
u8 i2c_read(void);



void i2c_dev_write(u8,u8,u8);
u8 i2c_dev_read(u8,u8);

#endif

