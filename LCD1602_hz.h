#ifndef _LCD1602_HZ_H_
#define _LCD1602_HZ_H_

#ifndef _LCD1602_H_

#include "LCD1602.h"

#endif //_LCD1602_H_


typedef struct {
	
    const char character[3];
	
    const unsigned char _data[6][8];
	
} LCD_hz;


void LCD_WriteChinese(u8 column,LCD_hz hz);





#endif //_LCD1602_HZ_H_