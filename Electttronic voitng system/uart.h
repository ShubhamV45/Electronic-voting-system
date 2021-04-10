#ifndef uart_h
#define uart_h


extern void uart_inti();
//extern char uart_Rxint(void);
extern void uart_Txchar(char);
extern void uart_str(unsigned char *str);

#endif


