#include"d_header.h"
extern unsigned char T_F;
int t;
void timer1_Handler(void)__irq
{
t++;
T_F^=1;
T1IR=1;
VICVectAddr=0;
}
void config_vic_for_timer1(void)
{

VICIntSelect=0;
VICVectCntl1=5|(1<<5);
VICVectAddr1=(unsigned int)timer1_Handler;
VICIntEnable|=(1<<5);
}
void config_t1(int d)
{
int a[]={15,60,30,15,15};
unsigned int pclk;
pclk=a[VPBDIV]*1000;
T1PC=0;
T1PR=pclk-1;
T1TC=0;
T1MR0=d;
T1MCR=3;
T1TCR=1;
}
