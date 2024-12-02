 #include<LPC21XX.H>
#include"d_header.h"
void lcd_data(unsigned char data)
{
	IOCLR1=0XFE<<16;
	IOSET1=((data&0XF0)<<16);
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

	IOCLR1=0XFE<<16;
	IOSET1=((data&0x0f)<<20);
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

}
void lcd_cmd(unsigned char cmd)
{
IOCLR1=0XFE<<16;
IOSET1=((cmd&0xf0)<<16)	;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0XFE<<16;
IOSET1=((cmd&0X0F)<<20);
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
void lcd_string(char* p)
{
 while(*p)
 {
 lcd_data(*p);
 p++;
 
	 }
 }
	 void lcd_init(void)
	 {
	 	IODIR1=0XFE<<16;
		PINSEL2=0X0;
		IOCLR1=1<<19;
		//lcd_cmd(0x03);
		lcd_cmd(0x02);
		lcd_cmd(0x28);
	//	lcd_cmd(0x0e);
		lcd_cmd(0x01);

	 
	 
	 
	 }
		void lcd_integer(int num)
{
/*char arr[10];
sprintf(arr,"%d",num);
uart0_tx_string(arr) ; */
char arr[10];
int i=0;
if(num==0)
{
lcd_data('0');
}
if(num<0)
{
//num=-num;
lcd_data('-');
}
for(;num;num=num/10)
arr[i++]=(num%10)+48;
for(i=i-1;i>=0;i--)
lcd_data(arr[i]);
}
void lcd_float(float f)
{
u32 i=f;
 lcd_integer(i);
lcd_data('.');
i=(f-i)*10;
lcd_integer(i);


}
void lcd_cgram(void)
{
	u32 i;

u8 b[]={0x4,0x1b,0x11,0x11,0x11,0x11,0x1f,0x0};
lcd_cmd(0x40);
for(i=0;i<8;i++)
lcd_data(b[i]);

								    
}
void lcd_cgram1(void)
{
	u32 i;

u8 b[10]={0x4,0x1b,0x11,0x11,0x11,0x1f,0x1f,0x0};
lcd_cmd(0x48);
for(i=0;i<8;i++)
lcd_data(b[i]);

								    
}
void lcd_cgram2(void)
{
	u32 i;

u8 b[10]={0x4,0x1b,0x11,0x11,0x1f,0x1f,0x1f,0x0};
lcd_cmd(0x50);
for(i=0;i<8;i++)
lcd_data(b[i]);

								    
} 
void lcd_cgram3(void)
{
	u32 i;

u8 b[10]={0x4,0x1b,0x11,0x1f,0x1f,0x1f,0x1f,0x0};
lcd_cmd(0x58);
for(i=0;i<8;i++)
lcd_data(b[i]);

								    
} 
void lcd_cgram4(void)
{
	u32 i;
u8 b[10]={0x4,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0};
lcd_cmd(0x60);
for(i=0;i<8;i++)
lcd_data(b[i]);
								    
} 
void lcd_cgram5(void)
{

u32 i;

u8 b[10]={0x0,0x4,0x16,0x15,0x15,0x16,0x4,0x0};
lcd_cmd(0x68) ;
for(i=0;i<8;i++)
{
lcd_data(b[i]);
}

}
void lcd_cgram6(void)
{
u32 i;
u32 b[20]={0x0,0x4,0x8,0x1F,0x8,0x4,0x0,0x0,0x0,0x4,0x2,0x1F,0x2,0x4,0x0,0x0};
lcd_cmd(0x70);
for(i=0;i<16;i++)
{
lcd_data(b[i]);
}


}





