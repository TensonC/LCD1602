
/*********
*
*ENCODE: GB2312
*
**********/






#include <REGX52.H>
#include "Delay.h"

#include "LCD1602_hz.h"



/**
 * @brief ��ʾ����
 * �Ḳ��ǰ6���洢���Զ����ַ�
 * @param column ��
 * @param hz ����
 */
void LCD_WriteChinese(u8 column,LCD_hz hz)
{
    /*�溺��*/
		u8 i;
		u8 j;
    for(i =0; i < 6; i++)
    {
        LCD_WriteCommand(0x40 + 8 * i);
        for(j = 0; j < 7; j++)
        {
            LCD_write(hz._data[i][j],1);
        }
    }
    /*д����*/
    LCD_WriteData(1,column,0x00);
    LCD_WriteData(1,column+1,0x01);
    LCD_WriteData(1,column+2,0x02);
    LCD_WriteData(2,column,0x03);
    LCD_WriteData(2,column+1,0x04);
    LCD_WriteData(2,column+2,0x05);

}