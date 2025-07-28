
/*********
*
*ENCODE: GB2312
*
**********/






#include <REGX52.H>
#include "Delay.h"

#include "LCD1602_show.h"

/**
 * @brief ������ʾ�ַ���
 * @param line ��
 * @param show_delay �ӳ�(ms)
 * @param str �ַ���
 */

void LCD_ScrollShowStr(u8 line,u32 show_delay,const char* str)
{ 
	char buffer[LCD_SCREEN_WIDTH];
	u8 len;
	u8 i;
	u8 j;

	for (len = 0; str[len]; len++);//���㳤��
	for (i = 0; i <= len + LCD_SCREEN_WIDTH; i++) {
		//д�뻺����
		for (j = 0; j < LCD_SCREEN_WIDTH; j++) {
			u8 pos = i + j - LCD_SCREEN_WIDTH;
			buffer[j] = (pos >= 0 && pos < len) ? 
			str[pos] : ' ';
		}
		LCD_WriteStr(line,1,buffer);
		delay_ms(show_delay);
	}

}

/**
 * @brief ������ʾ�����ַ���
 * @param show_delay �ӳ�(ms)
 * @param str1 �ַ���1
 * @param str2 �ַ���2
 */
void LCD_ScrollShowTwoLineStr(u32 show_delay,const char* str1,const char* str2)
{
	char buffer1[LCD_SCREEN_WIDTH];
	char buffer2[LCD_SCREEN_WIDTH];

	u8 len1;
	u8 len2;
	u8 len;
	u8 i;
	u8 j;
	u8 pos;

	for (len1 = 0; str1[len1]; len1++){}
	for (len2 = 0; str2[len2]; len2++){}

	len = len1 >= len2 ? len1 : len2;
	for (i = 0; i <= len + LCD_SCREEN_WIDTH; i++) {
		for (j = 0; j < LCD_SCREEN_WIDTH; j++) {
			pos = i + j - LCD_SCREEN_WIDTH;
			buffer1[j] = (pos >= 0 && pos < len1) ? 
			str1[pos] : ' ';
			buffer2[j] = (pos >= 0 && pos < len2) ? 
			str2[pos] : ' ';
		}

		LCD_WriteStr(1,1,buffer1);
		LCD_WriteStr(2,1,buffer2);
		delay_ms(show_delay);
	}
}

/**
 * @brief һ����һ����ʾ�ַ���
 * @param line ��
 * @param column ��
 * @param show_delay �ӳ�(ms)
 * @param str �ַ���
 */

void LCD_OnebyoneShowStr(u8 line,u8 column,u32 show_delay,const char* str)
{
	
	while (*str) {
		LCD_WriteData(line,column++,*str++);
		delay_ms(show_delay);
	}
}

/**
 * @brief ������ʾ�ַ���
 * @param line ��
 * @param column ��
 * @param show_delay �ӳ�(ms)
 * @param str �ַ���
 */
void LCD_CodeShowStr(u8 line,u8 column,u32 show_delay,const char* str)
{
	u8 _code = 0xd0;//�ֿ���ĳ�ַ�
	u8 len;
	u8 i;
	
	for (len = 0; str[len]; len++);//���㳤��
	
	while(_code > 0xbf) {
		for(i = 0; i < len; i++)
		{
			LCD_WriteData(line,column + i,_code+i);
		}
		_code--;
		delay_ms(show_delay);
	}
	LCD_WriteStr(line,column,str);
	
	
//	while (*str && i < LCD_SCREEN_WIDTH) {
//		while (_code > 0xbf) {
//			LCD_WriteData(line,column,_code--);
//			delay_ms(50);
//		}
//		LCD_WriteData(line,column,*str);
//		column++;
//		str++;
//		i++;
//		_code = 0xd0;
//		delay_ms(show_delay);
//	}
}
