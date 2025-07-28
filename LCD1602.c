
/*********
*
*ENCODE: GB2312
*
**********/





#include <REGX52.H>
#include "delay.h"

#include "LCD1602.h"


#define LCD_PINS P0		  //��������

sbit LCD_RS = P2^5;			//����дָ��(0)����д����(1)
sbit LCD_RW = P2^6;			//���ö�(1)д(0)
sbit LCD_ENABLE = P2^7; //����ʹ��


//8λ����4λ����ģʽ
static u8 datamode = 8;

u16 code Pow10[] = {1,10,100,1000,10000};

/**
 * @brief LCD1602��ʼ������(8λ����ģʽ)
 */
void LCD_Init_8bit()
{
	datamode = 8;

	LCD_RS = 0;
	LCD_RW = 0;
	LCD_ENABLE = 0;

	delay_ms(20);
  
	LCD_WriteCommand(0x38);//8λģʽ��������ʾ��5*7����
	LCD_WriteCommand(0x0c);//��ʾ��������
	LCD_WriteCommand(0x06);//�����AC�Զ���һ
	LCD_WriteCommand(0x01);//����
  delay_ms(2);
}

/**
 * @brief д��һ������
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
 * @brief LCD1602��ʼ������(4λ����ģʽ)
 * @param RS д���ݻ�дָ������
 * @param RW ��д����
 * @param E ʹ������
 * @param PINS ���ݴ�����ʼ����
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
	LCD_write_half(0x02);// ����Ϊ 4 λģʽ

	LCD_WriteCommand(0x28);//4λģʽ��������ʾ��5*7����
	LCD_WriteCommand(0x0C);//��ʾ��������
	LCD_WriteCommand(0x06);//�����AC�Զ���һ
	LCD_WriteCommand(0x01);//����
	delay_ms(2);
}



/**
 * @brief д������
 * @param _data ����
 * @param mode ָ�������
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
		// д���4λ
    LCD_PINS &= 0x0F;//�������λ
    LCD_PINS |= _data & 0xF0;
    LCD_ENABLE = 1;
    delay_us(1);
    LCD_ENABLE = 0;
    delay_us(50);

    // д���4λ
    LCD_PINS &= 0x0F;//�������λ
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
 * @brief дָ��
 * @param command ָ��
 */
void LCD_WriteCommand(u8 command)
{
	LCD_write(command,0);
}

/**
 * @brief д����
 * @param line ��
 * @param column ��
 * @param _data ����
 */

void LCD_WriteData(u8 line,u8 column,u8 _data)
{
	LCD_SetCursor(line,column);
	LCD_write(_data,1);
}

/**
 * @brief д���ַ���
 * @param line ��ʼ��
 * @param column ��ʼ��
 * @param str �ַ���
 */
void LCD_WriteStr(u8 line,u8 column,const char* str)
{
	LCD_SetCursor(line,column);
	while (*str) {
			LCD_write(*str++,1);
	}
}



/**
 * @brief ��һ���Զ����ַ�
 * @param id �洢λ��(0-7)
 * @param figure 8��8bit������ɵ��ַ���Ϣ
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
 * @brief д���Զ����ַ�
 * @param line ��
 * @param column ��
 * @param id �ַ��洢λ��(0-7)
 */
void LCD_WriteFigure(u8 line,u8 column,u8 id)
{
	LCD_WriteData(line,column,0x00 + id);
}

/**
 * @brief д��һ������(0-65535)
 * @param line ��
 * @param column ��
 * @param num ����
 * @param len ������ʾ����
 */
void LCD_WriteNum(u8 line,u8 column,u16 num,u8 len)
{
	while(len--)
	{
		LCD_WriteData(line,column++,num / Pow10[len] % 10 + '0');
	}
}


/**
 * @brief ���ù��λ��
 * @param line ��
 * @param column ��
 */
void LCD_SetCursor(u8 line,u8 column)
{
	u8 address = (line == 2) ? 0x40 + (column - 1) : (column - 1);
	LCD_WriteCommand(0x80 | address);
}


/**
 * @brief ���һ��
 * @param line ��
 */
void LCD_ClearLine(u8 line)
{
	LCD_WriteStr(line,1,"                ");
}




