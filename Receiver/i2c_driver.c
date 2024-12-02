#include<lpc21xx.h>
#include"header.h"
void i2c_init(void)
{
PINSEL0|=0X50;
I2SCLH=I2SCLL=75;
I2CONSET=(1<<6);
}
#define SI ((I2CONSET>>3)&1)
void i2c_byte_write_frame(u8 sa,u8 mr,u8 data)
{
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
//if(I2STAT!=0X08)
//{
//uart0_tx_string("ERR:start\r\n");
//goto exit;
//}
I2DAT=sa;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X20)
//{
//uart0_tx_string("ERR:sa+r\r\n");
//goto exit;
//}
I2DAT=mr;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X30)
//{
//uart0_tx_string("ERR:mr+\r\n");
//goto exit;
//}
I2DAT=data;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X30)
//{
//uart0_tx_string("ERR:data\r\n");
//goto exit;
//}
//exit:
I2CONCLR=(1<<3);
I2CONSET=(1<<4);
}
////////////////////////I2C_BYTE_READ_FRAME////////////////
u8 i2c_byte_read_frame(u8 sa,u8 mr)
{
u8 temp;
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
//if(I2STAT!=0X08)
//{
//uart0_tx_string("ERR:start\r\n");
//goto exit;
//}
I2DAT=sa;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X20)
//{
//uart0_tx_string("ERR:sa+r\r\n");
//goto exit;
//}
I2DAT=mr;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X30)
//{
//uart0_tx_string("ERR:mr+\r\n");
//goto exit;
//}
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
//if(I2STAT==0X10)
//{
//uart0_tx_string("ERR:RESTART\r\n");
//goto exit;
//}
I2DAT=sa|1;
I2CONCLR=(1<<3);
while(SI==0);
//if(I2STAT==0X48)
//{
//uart0_tx_string("ERR:s/a+r/r/n");
//goto exit;
//}
I2CONCLR=(1<<3);
while(SI==0);
temp=I2DAT;
//exit:
I2CONCLR=(1<<3);
I2CONSET=(1<<4);
return temp;
}

