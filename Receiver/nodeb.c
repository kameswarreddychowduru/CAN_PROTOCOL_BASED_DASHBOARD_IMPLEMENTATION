#include"d_header.h"
extern unsigned int flag;
extern can1 m1;
void can1_rx_Handler()__irq
{
m1.id=C2RID;
m1.dlc=(C2RFS>>16)&0XF;
m1.rtr=(C2RFS>>30)&1;
if(m1.rtr==0)
{
m1.byteA=C2RDA;
m1.byteB=C2RDB;	 
}
C2CMR=(1<<2);
flag=1;
VICVectAddr=0;

}
void config_can1()
{
C2IER=1;

}
void config_vic_for_can1()
{
VICIntSelect=0;								  
VICVectCntl0=27|(1<<5);
VICVectAddr0=(unsigned int) can1_rx_Handler;
VICIntEnable|=(1<<27);
}
