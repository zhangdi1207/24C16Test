#include<reg52.h>
#include<intrins.h>
#ifndef _OLED_H_
#define	_OLED_H_

#define uchar unsigned char
#define uint unsigned int


#define Brightness 0xCF
#define X_WIDTH 128
#define Y_WIDTH 64

#define D1;   {_nop_();_nop_();_nop_();_nop_();} //>=4.7us



sbit sck=P3^0;
sbit sda=P3^1;
sbit memCS=P3^2;
sbit disCS=P3^3;



sbit test1=P3^5;

void delayMs(uint z);
void memDelay();
void start();
void stop();
void ack();
void memInit();
void write8(uchar dat);
void memWchar(uchar add,uchar dat,uchar page);	  //page in(0-7)
uchar memRead(uchar add,uchar page);
void disW(uchar dat,uchar com);




#endif