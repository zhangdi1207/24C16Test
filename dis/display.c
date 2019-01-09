#include <oled.h>

uchar code F6x8[][6] =
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
};

void disW(uchar dat,uchar com)
{
	disCS=0;
	start();
	write8(0x78);
	ack();
	write8(com);
	ack();
	write8(dat);
	ack();
	stop();
	disCS=1;
}

void disWdat(uchar dat)
{
	disW(dat,0x40);
}
void disWcom(uchar dat)
{
	disW(dat,0x00);
}
void disSetPos(uchar x, uchar y)
{
	disWcom(0xb0+y);
	disWcom(((x&0xf0)>>4)|0x10);
	disWcom((x&0x0f)|0x01);
}
void disFill(uchar bmp_dat)
{
	uchar y,x;
	for(y=0;y<8;y++)
	{
		disWcom(0xb0+y);
		disWcom(0x01);
		disWcom(0x10);
		for(x=0;x<X_WIDTH;x++)
		disWdat(bmp_dat);
	}
}
void disCLS()
{
	disFill(0);
}
void disInit()
{
	delayMs(500);
	disWcom(0xae);//--turn off oled panel
	disWcom(0x00);//---set low column address
	disWcom(0x10);//---set high column address
	disWcom(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	disWcom(0x81);//--set contrast control register
	disWcom(Brightness); // Set SEG Output Current Brightness
	disWcom(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	disWcom(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	disWcom(0xa6);//--set normal display
	disWcom(0xa8);//--set multiplex ratio(1 to 64)
	disWcom(0x3f);//--1/64 duty
	disWcom(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	disWcom(0x00);//-not offset
	disWcom(0xd5);//--set display clock divide ratio/oscillator frequency
	disWcom(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	disWcom(0xd9);//--set pre-charge period
	disWcom(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	disWcom(0xda);//--set com pins hardware configuration
	disWcom(0x12);
	disWcom(0xdb);//--set vcomh
	disWcom(0x40);//Set VCOM Deselect Level
	disWcom(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	disWcom(0x02);//
	disWcom(0x8d);//--set Charge Pump enable/disable
	disWcom(0x14);//--set(0x10) disable
	disWcom(0xa4);// Disable Entire Display On (0xa4/0xa5)
	disWcom(0xa6);// Disable Inverse Display On (0xa6/a7) 
	disWcom(0xaf);//--turn on oled panel
	disFill(0x00); //初始清屏
	disSetPos(0,0);
}


void dis6x8Strs(uchar x,uchar y,uchar ch[])
{
	uchar c=0,i=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-32;
		if(x>126)
		{
			x=0;
			y++;
		}
		disSetPos(x,y);
		for(i=0;i<6;i++)
		disWdat(F6x8[c][i]);
		x+=6;
		j++;
	}	
}

void main()
{
	disInit();
	disCLS();
	dis6x8Strs(0,0,"123");
	memInit();
	memRead(0,0);
	memWchar(0,0,1);
}