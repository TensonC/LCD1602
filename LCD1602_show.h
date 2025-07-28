#ifndef _LCD1602_SHOW_H_
#define _LCD1602_SHOW_H_

#ifndef _LCD1602_H_

#include "LCD1602.h"

#endif //_LCD1602_H_


void LCD_ScrollShowStr(u8 line,u32 show_delay,const char* str);
void LCD_OnebyoneShowStr(u8 line,u8 column,u32 show_delay,const char* str);
void LCD_CodeShowStr(u8 line,u8 column,u32 show_delay,const char* str);
void LCD_ScrollShowTwoLineStr(u32 show_delay,const char* str1,const char* str2);



#endif //_LCD1602_SHOW_H_