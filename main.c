#include<LPC21xx.h>
#include "4bitlcd.h"
#define L1 1<<2
#define M1 1<<6 //low
#define M2 1<<7 //high

void uart_config(void)
{
	PINSEL0|=0x00000005;
	U0LCR=0x83;
	U0DLL=97;
	U0LCR=0x03;
}

unsigned char uart_rx()
{
	while((U0LSR & (1<<0))==0);
	return U0RBR;
}

void uart_tx(unsigned char d)
{
	while((U0LSR & (1<<5))==0);
	U0THR=d;
}

int main()
{
	char ch;
	uart_config();
	LCD_INIT();
	
	LCD_CMD(0x80);
	LCD_STRING("HOME AUTOMATION");
	milliseconds(100);
	IODIR0|=L1|M1|M2;
	IOSET0=L1;
	IOCLR0=M1|M2;
	while(1)
	{
		ch=uart_rx();
		uart_tx(ch);
		
		if(ch=='1')
		{
			LCD_CMD(0x01);
			IOCLR0=L1;
		  LCD_CMD(0xC0);
			LCD_STRING("LEDON");
		}
		if(ch=='0')
		{
			LCD_CMD(0x01);
			IOSET0=L1;
			LCD_CMD(0xC0);
			LCD_STRING("LEDOFF");
		}
		if(ch=='F')
		{
			LCD_CMD(0x01);
			IOSET0=M1;
			IOCLR0=M2;
			LCD_CMD(0xC0);
			LCD_STRING("MOTORON");
		}
		if(ch=='S')
		{
			LCD_CMD(0x01);
			IOCLR0=M1|M2;
			LCD_CMD(0xC0);
			LCD_STRING("MOTOROFF");
		}
	}
}
