#include<reg52.h>
#include<intrins.h>

#ifndef uchar_uint
#define uchar unsigned char
#define uint unsigned int
#endif

#define Brightness 0xCF
#define X_WIDTH 128
#define Y_WIDTH 64

#define D1;   {_nop_();_nop_();_nop_();_nop_();} //>=4.7us

sbit sck=P3^0;
sbit sda=P3^1;
sbit memCS=P3^2;
sbit disCS=P3^3;



sbit test1=P3^5;

void delayMs(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}


void memDelay()//写数据过程中延时，大约需要i=1100模拟延时成功，取2倍
{
	uint i=2000;
	while(i--)
	D1;
}


void start(void)
{
	sda=1;
	D1;
	sck=1;
	D1;
	sda=0;
	D1;
}

void stop(void)
{
	sda=0;
	D1;
	sck=1;
	D1;
	sda=1;
	D1;

}

void ack()
{
	uchar i;
	sck=1;
	D1;;
	while((sda==1)&&i<200)
	{
		i++;
	}
	sck=0;
	D1;
}

void init()
{
	sda=1;
	D1;
	sck=1;
	D1;

}

uchar read8()
{
	uchar i=8,j=0;
	for(i=0;i<8;i++)
	{

		sck=1;
		j<<=1;
		j|=sda;
		sck=0;
		D1;
	}
	return j;
}

void write8(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		sck=0;
		D1;
		sda=(bit)(dat&0x80);
		D1;
		sck=1;
		dat<<=1;
	}
	sck=0;
	D1;
}

void memWchar(uchar add,uchar dat,uchar page)	  //page in(0-7)
{
	uchar con=0xa0;
	con+=(0x07&page)*2;
	memCS=0;
	start();
	write8(con);
	ack();
	write8(add);
	ack();
	write8(dat);
	ack();						
	stop();
	DT();
	memCS=1;

}

uchar memRead(uchar add,uchar page)
{
	uchar dat,con=0xa0;
	con+=(0x07&page)*2;
	start();
	write8(con);
	ack();
	write8(add);
	ack();
	con+=(0x07&page)*2;
	con+=1;
	start();
	write8(con);
	ack();
	dat=read8();
	D1;
	stop();
	return dat;
}

void disW(uchar dat,uchar com)
{
	disCS=0;
	start();
	write8(0x78);
	write8(com);
	write8(dat);
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

void main()
{
	uint i=0;
	memCS=1;
	init();
	for(i=0;i<100;i++)
	memWchar(i,i,i/256);
	memCS=0;
	for(i=101;i<200;i++)
	memWchar(i,i,i/256);
	memCS=1;
	while(1);

}

