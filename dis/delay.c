#include <oled.h>

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