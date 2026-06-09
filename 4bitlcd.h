#include<LPC21xx.h>
#include"delayheader.h"
#define D (0xF << 14)
#define RS (1<<12)
#define E (1<<13)

void LCD_CMD(unsigned char c){
	unsigned char m,n;
	m=(c & 0xF0);
	IOCLR0=D;
	IOSET0=m;
	IOCLR0=RS;
	IOSET0=E;
	milliseconds(2);
	IOCLR0=E;
	
	n=(c & 0x0F);
	IOCLR0=D;
	IOSET0=(n<<4);
	IOCLR0=RS;
	IOSET0=E;
	milliseconds(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	unsigned char m,n;
	m=(d & 0xF0);
	IOCLR0=D;
	IOSET0=m;
	IOSET0=RS;
	IOSET0=E;
	milliseconds(2);
	IOCLR0=E;
	
	n=(d & 0x0F);
	IOCLR0=D;
	IOSET0=(n<<4);
	IOSET0=RS;
	IOSET0=E;
	milliseconds(2);
	IOCLR0=E;
}
void LCD_INIT(void){
	IODIR0=D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x28);
	LCD_CMD(0x0C);
	LCD_CMD(0x80);
}
void LCD_STRING(unsigned char *s){
	char pos=0;
	while(*s){
		LCD_DATA(*s++);
		pos++;
		if(pos==16)
			LCD_CMD(0xC0);
	}
}
