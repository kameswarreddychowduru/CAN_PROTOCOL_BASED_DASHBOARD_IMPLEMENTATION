#include"d_header.h"

void can1_init()
{
VPBDIV=1;
PINSEL1|=0X14000;
C2MOD=1;
AFMR=2;
C2BTR=0X001C001D;
C2MOD=0;

}
#define TCS ((C2GSR>>3)&1)
void can1_tx(can1 v)
{
C2TID1=v.id;
C2TFI1=(v.dlc<<16);
if(v.rtr==0)
{
C2TDA1=v.byteA;
C2TDB1=v.byteB;
}


C2CMR=1|(1<<5);
while(TCS==0);
}


