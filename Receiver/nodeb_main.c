#include"d_header.h"
#define HL_LED (1<<17)
#define RI (1<<18)
#define LI (1<<19)
can1 m1;
unsigned char flag;
unsigned char h,s,m,k;
unsigned char T_F;
main()
{
float vout,temperature;
u32 battery;
unsigned char temp;
lcd_init();
can1_init();
adc_init();
i2c_init();
config_vic_for_can1();
config_can1();
config_vic_for_timer1();
config_t1(250);
IODIR0|=HL_LED|RI|LI;
IOSET0|=HL_LED|RI|LI;
i2c_byte_write_frame(0xd0,0x0,0x55);
i2c_byte_write_frame(0xd0,0x1,0x59);
i2c_byte_write_frame(0xd0,0x2,0x72);
//i2c_byte_write_frame(0xd0,0x2,0x52);


while(1)
{

if(flag==1)

{

flag=0;
	s=i2c_byte_read_frame(0xd0,0x0);

	m=i2c_byte_read_frame(0xd0,0x1);

	h=i2c_byte_read_frame(0xd0,0x2);	
	h=h&0x1f;
	k=(h>>5)&1;
	if(k)
	{
		lcd_cmd(0xc8);
		lcd_string("pm");
		}
		else
		{
		lcd_cmd(0xc8);
		lcd_string("am");
		}
		lcd_cmd(0xc0);
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);


		lcd_data(':');


		lcd_data((m/0x10)+48);


		lcd_data((m%0x10)+48);


		lcd_data(':');


		lcd_data((s/0x10)+48);


		lcd_data((s%0x10)+48);






switch((m1.byteA)&0xff)

{	 


case 0x10:

		IOCLR0=HL_LED;

		lcd_cgram5();

		lcd_cmd(0x89);

   		lcd_data(5);

		break;

case 0x11:IOSET0=HL_LED;

			lcd_cmd(0x89);

   		    lcd_data(' ');

			break;

case 0x12: temp=m1.byteA;

           IOSET0=RI;IOCLR0=LI;

			lcd_cgram6();

			lcd_cmd(0x87);

			lcd_data(6);

			break;

case 0x13:	 temp=m1.byteA;

             IOSET0=LI;

			lcd_cmd(0x87);

			lcd_data(' ');

			break;

case 0x14:	temp=m1.byteA;

            IOSET0=LI;IOCLR0=RI;

				lcd_cgram6();

			lcd_cmd(0x8b);

			lcd_data(7);

			break;

case 0x15:	temp=m1.byteA;

           IOSET0=RI;

		    lcd_cmd(0x8b);

			lcd_data(' ');

			break;	

} 


      }

if((m1.id==0x314))

 {

//T_F=0;
vout=((float)((m1.byteA)&0x3ff)*3.3)/(float)1023;


temperature=(vout-0.5)/0.01;


lcd_cmd(0x80);


lcd_float(temperature);


lcd_data('c');


battery=((m1.byteB));

 if(battery==0)


{


lcd_cgram();


lcd_cmd(0x85);


   lcd_data(0);


  }


   else if(battery>=1 && battery<=250)


   {	


   lcd_cgram1();


   	lcd_cmd(0x85);


   lcd_data(1);


   } 


   else if(battery>=251&&battery<=500)


   {
   lcd_cgram2();


   lcd_cmd(0x85);


   lcd_data(2);


   } 


   else if(battery>=501&&battery<=750)


   {


   


   lcd_cgram3();


   lcd_cmd(0x85);


   lcd_data(3);


   } 


   else if(battery>=751&&battery<=1023)


   {


   lcd_cgram4();


   lcd_cmd(0x85);


   lcd_data(4);


   } 

  }

if((temp==0x12)&&(T_F==1))

{  	 

IOCLR0=LI;

  lcd_cgram6();

  lcd_cmd(0x87);

   lcd_data(6);

  lcd_data(' '); 


}

else if (temp==0x14&& T_F==1)

{	  //T_F=0;

IOCLR0=RI;

	lcd_cgram6();

	lcd_cmd(0X8b);

	lcd_data(7);

	 lcd_data(' ');

}

else

{						  

   IOSET0=LI;

   IOSET0=RI;

   lcd_cmd(0x87);

    lcd_data(' ');

   lcd_cmd(0x8b);


   lcd_data(' ');

} 


}
}
