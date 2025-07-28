#include <REGX52.H>
#include "LCD1602_show.h"

int main()
{

	u8 code figure0[8] = {0x00,0x00,0x0a,0x00,0x00,0x0a,0x04,0x00};
	
	LCD_Init_4bit();
	
	LCD_SetFigure(0,figure0);
	
	LCD_OnebyoneShowStr(1,1,200,"Hello");
	LCD_WriteFigure(1,7,0);
	LCD_CodeShowStr(1,10,200,"89C52");
	LCD_ScrollShowStr(2,1000,"Welcom to use the LCD1602!!");
	LCD_ClearLine(1);
	LCD_ClearLine(2);
	LCD_WriteStr(1,4,"loading...");
	LCD_WriteData(2,1,'[');
	LCD_WriteData(2,16,']');
	
	
	while(1)
	{
		LCD_OnebyoneShowStr(2,2,500,"==============");
		LCD_WriteStr(2,2,"              ");
	}
	
	
}