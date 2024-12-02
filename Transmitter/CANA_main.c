#include"d_header.h"

#define SW1 ((IOPIN0>>14)&1)

#define SW2 ((IOPIN0>>15)&1)

#define SW3 ((IOPIN0>>16)&1)

unsigned char H_F;

unsigned char L_F;

unsigned char R_F;

unsigned char F;

can1 v1,v2,v3,v4,m1;

int main()

{

config_vic_for_timer1();

config_t1(1);

can1_init();

adc_init();

v1.dlc=1;

v1.rtr=0;

	v1.byteA=0;

	v1.byteB=0;


	v2.dlc=1;

	v2.rtr=0;

	v2.byteA=0;

	v2.byteB=0;


	v3.dlc=1;

	v3.rtr=0;

	v3.byteA=0;

	v3.byteB=0;

	v4.dlc=8;

	v4.rtr=0;

	v4.byteA=0;

	v4.byteB=0;





while(1)

{

  if(F==1)

  {

  	  F=0;

	  v4.id=0x314;

	  v4.byteA=adc_read(1);

	  v4.byteB=adc_read(2);

  	  can1_tx(v4);

  }

if(SW1==0)

{

while(SW1==0);

	v1.id=0x310;

H_F^=1;




if(H_F==1)

{

v1.byteA=0x10;

can1_tx(v1);

}

else if(H_F==0)

{

v1.byteA=0X11;

can1_tx(v1);

}

}

if(SW2==0)

{

while(SW2==0);

	v2.id=0x311;

L_F^=1;




if(L_F==1)

{




v2.byteA=0x12;

can1_tx(v2);

R_F=0;

}

else if(L_F==0)

{

v2.byteA=0X13;

can1_tx(v2);									   

}

}

if(SW3==0)

{

while(SW3==0);

	v3.id=0x312;

R_F^=1;




if(R_F==1)

{


v3.byteA=0x14;

can1_tx(v3);

L_F=0;

}

else if(R_F==0)

{

v3.byteA=0X15;

can1_tx(v3);

}

}

}

}













