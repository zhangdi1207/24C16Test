#include <oled.h>

void delayMs(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}


void memDelay()//д���ݹ�������ʱ����Լ��Ҫi=1100ģ����ʱ�ɹ���ȡ2��
{
	uint i=2000;
	while(i--)
	D1;
}