#ifndef lcd_h
#define lcd_h

extern void lcd_init();
extern void lcd_cmd(unsigned char);
extern void lcd_disp(unsigned char);
extern void lcd_str(unsigned char *);
extern void lcd_char(unsigned int);


#endif
