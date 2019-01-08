#include<oled.h>

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