#include <oled.h>

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

void memInit()
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
	memDelay();
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