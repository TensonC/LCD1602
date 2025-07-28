#ifndef _LCD1602_H_
#define _LCD1602_H_

#define LCD_SCREEN_WIDTH 16
#define LCD_SCREEN_HIGH 2

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

void LCD_Init_8bit();
void LCD_Init_4bit();
void LCD_ClearLine(u8 line);
void LCD_SetCursor(u8 line,u8 column);
void LCD_write(u8 _data,u8 mode);
void LCD_WriteData(u8 line,u8 column,u8 _data);
void LCD_WriteCommand(u8 command);
void LCD_WriteStr(u8 line,u8 column,const char* str);
void LCD_SetFigure(u8 id,const u8 figure[8]);
void LCD_WriteFigure(u8 line,u8 column,u8 id);
void LCD_WriteNum(u8 line,u8 column,u16 num,u8 len);

#endif //_LCD1602_H_