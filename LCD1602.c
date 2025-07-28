
/*********
*
*ENCODE: GB2312
*
**********/





#include <REGX52.H>
#include "delay.h"

#include "LCD1602.h"


#define LCD_PINS P0		  //数据引脚

sbit LCD_RS = P2^5;			//设置写指令(0)还是写数据(1)
sbit LCD_RW = P2^6;			//设置读(1)写(0)
sbit LCD_ENABLE = P2^7; //设置使能


//8位还是4位输入模式
static u8 datamode = 8;

u16 code Pow10[] = {1,10,100,1000,10000};

/**
 * @brief LCD1602初始化函数(8位数据模式)
 */
void LCD_Init_8bit()
{
	datamode = 8;

	LCD_RS = 0;
	LCD_RW = 0;
	LCD_ENABLE = 0;

	delay_ms(20);
  
	LCD_WriteCommand(0x38);//8位模式，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关
	LCD_WriteCommand(0x06);//输入后AC自动加一
	LCD_WriteCommand(0x01);//清屏
  delay_ms(2);
}

/**
 * @brief 写入一半数据
 */
static void LCD_write_half(u8 _data)
{
		LCD_RW = 0;
		LCD_PINS &= 0x0F;
    LCD_PINS |= (_data << 4) & 0xF0;
    LCD_ENABLE = 1;
    delay_us(1);
    LCD_ENABLE = 0;
}

/**
 * @brief LCD1602初始化函数(4位数据模式)
 * @param RS 写数据或写指令引脚
 * @param RW 读写引脚
 * @param E 使能引脚
 * @param PINS 数据传输起始引脚
 */

void LCD_Init_4bit()
{
	datamode = 4;
	

	LCD_RS = 0;
	LCD_RW = 0;
	LCD_ENABLE = 0;

	delay_ms(20);

	LCD_write_half(0x03);
	delay_ms(5);
	LCD_write_half(0x03);
	delay_ms(5);
	LCD_write_half(0x03);
	delay_us(150);
	LCD_write_half(0x02);// 设置为 4 位模式

	LCD_WriteCommand(0x28);//4位模式，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);//显示开，光标关
	LCD_WriteCommand(0x06);//输入后AC自动加一
	LCD_WriteCommand(0x01);//清屏
	delay_ms(2);
}



/**
 * @brief 写入内容
 * @param _data 内容
 * @param mode 指令或数据
 */
void LCD_write(u8 _data,u8 mode)
{
	LCD_RS = mode;
	LCD_RW = 0;

	switch (datamode)
	{
	case 8:
		LCD_PINS = 0x00;
		LCD_PINS = _data;

		LCD_ENABLE = 1;
		delay_us(1);
		LCD_ENABLE = 0;
		delay_us(100);
		break;
	case 4:
		// 写入高4位
    LCD_PINS &= 0x0F;//清除高四位
    LCD_PINS |= _data & 0xF0;
    LCD_ENABLE = 1;
    delay_us(1);
    LCD_ENABLE = 0;
    delay_us(50);

    // 写入低4位
    LCD_PINS &= 0x0F;//清除高四位
    LCD_PINS |= (_data << 4) & 0xF0;
    LCD_ENABLE = 1;
    delay_us(1);
    LCD_ENABLE = 0;
    delay_us(50);
	default:
			break;
	}
    
}

/**
 * @brief 写指令
 * @param command 指令
 */
void LCD_WriteCommand(u8 command)
{
	LCD_write(command,0);
}

/**
 * @brief 写数据
 * @param line 行
 * @param column 列
 * @param _data 数据
 */

void LCD_WriteData(u8 line,u8 column,u8 _data)
{
	LCD_SetCursor(line,column);
	LCD_write(_data,1);
}

/**
 * @brief 写入字符串
 * @param line 起始行
 * @param column 起始列
 * @param str 字符串
 */
void LCD_WriteStr(u8 line,u8 column,const char* str)
{
	LCD_SetCursor(line,column);
	while (*str) {
			LCD_write(*str++,1);
	}
}



/**
 * @brief 存一个自定义字符
 * @param id 存储位置(0-7)
 * @param figure 8个8bit数据组成的字符信息
 */
void LCD_SetFigure(u8 id,const u8 figure[8])
{
	u8 i;
	LCD_WriteCommand(0x40 + 8 * id);
	for(i = 0; i < 7; i++)
	{
			LCD_write(figure[i],1);
	}
}

/**
 * @brief 写入自定义字符
 * @param line 行
 * @param column 列
 * @param id 字符存储位置(0-7)
 */
void LCD_WriteFigure(u8 line,u8 column,u8 id)
{
	LCD_WriteData(line,column,0x00 + id);
}

/**
 * @brief 写入一串数字(0-65535)
 * @param line 行
 * @param column 列
 * @param num 数字
 * @param len 数字显示长度
 */
void LCD_WriteNum(u8 line,u8 column,u16 num,u8 len)
{
	while(len--)
	{
		LCD_WriteData(line,column++,num / Pow10[len] % 10 + '0');
	}
}


/**
 * @brief 设置光标位置
 * @param line 行
 * @param column 列
 */
void LCD_SetCursor(u8 line,u8 column)
{
	u8 address = (line == 2) ? 0x40 + (column - 1) : (column - 1);
	LCD_WriteCommand(0x80 | address);
}


/**
 * @brief 清除一行
 * @param line 行
 */
void LCD_ClearLine(u8 line)
{
	LCD_WriteStr(line,1,"                ");
}




