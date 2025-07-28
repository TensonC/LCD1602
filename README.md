# LCD1602
基于89C52的LCD1602功能库，支持**4位**和**8位**数据传输，可配置到其他设备

**编码格式为GB2312**

---

## lib
| 文件 | 内容 |
| --- | --- |
| main.c | 功能演示 |
| LCD1602 | 基础显示功能 |
| LCD1602_show | 更高级的显示类型 |
| LCD1602_hz | 汉字显示 |
| delay | 延迟函数 |

## API
| 函数名 | 功能 |
| --- | --- |
| ***LCD1602文件*** |  |
| LCD_Init_8bit() | 8位数据传输初始化 |
| LCD_Init_4bit() | 4位数据传输初始化 |
| LCD_ClearLine(u8 line) | 清空一行 |
| LCD_SetCursor(u8 line,u8 column) | 设置光标位置 |
| LCD_write(u8 _data,u8 mode) | 以特定模式传输数据 |
| LCD_WriteData(u8 line,u8 column,u8 _data) | 在某处写一个字符 |
| LCD_WriteCommand(u8 command) | 输入指令 |
| LCD_WriteStr(u8 line,u8 column,const char* str) | 在某处显示字符串 |
| LCD_SetFigure(u8 id,const u8 figure[8]) | 在某储存位置设置自定义字符 |
| LCD_WriteFigure(u8 line,u8 column,u8 id) | 在某处输出特定储存位置的自定义字符 |
| LCD_WriteNum(u8 line,u8 column,u16 num,u8 len) | 在某位置写一个数字 |
| ***LCD1602_show文件*** |  |
| LCD_ScrollShowStr(u8 line,u32 show_delay,const char* str) | 在某行滚动显示一串字符串 |
| LCD_ScrollShowTwoLineStr(u32 show_delay,const char* str1,const char* str2) | 在上下两行滚动显示一串字符串 |
| LCD_OnebyoneShowStr(u8 line,u8 column,u32 show_delay,const char* str) | 一个接一个显示字符串 |
| LCD_CodeShowStr(u8 line,u8 column,u32 show_delay,const char* str) | 像黑客()一样输出字符串 |
| ***LCD1602_hz文件*** |  |
| LCD_WriteChinese(u8 column,LCD_hz hz) | 在某列输出一个LCD_hz格式储存的占两行三列的汉字 |



