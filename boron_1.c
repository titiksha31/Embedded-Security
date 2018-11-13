#include<stdio.h>

unsigned long long int sbox(unsigned long long int);
unsigned int circ_left(unsigned int,unsigned int);

unsigned char s[16] = {0xE,4,0xB,1,7,9,0xC,0xA,0xD,2,0,0xF,8,5,3,6};

int main()
{
	unsigned int z=0,j=0,i=0, pt1=0,pt2=0,pt3=0,pt4=0;
	unsigned long long int k[2]={0x0000000000000000,0x0000000000000000}, pt=0x0123456789abcdef, x1=0x00, temp=0x00,ct=0x00;
	for(j=0;j<25;j++)
	{
	printf("\nRound %d\n",j);
	printf("\n64 bit plain text: %llx",pt);
	printf("\nKey: %llx, %llx",k[0],k[1]);
	
	pt= pt^k[1];
	pt= sbox(pt);
	printf("\nS-box output %llx",pt);
		
	temp=k[1];
	z=0;
	k[1]= (temp<<13)|(k[0]>>(64-13));
	k[0]= (k[0]<<13)|(temp>>(64-13));
	for (i=0;i<2;i++)
	{
		z|= (s[((k[1]>>(i*4))&0xF)]<<(i*4))&0xFF;
	}
	k[1] &= (0XFFFFFFFFFFFFFF00);
	k[1] |= (z&0xFF);

	
	temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&j));
	k[1] &= 0X07FFFFFFFFFFFFFF;
	k[1] |= temp<<(64-5);
	
	pt1=(pt>>48)&0xFFFF;
	pt2=(pt>>32)&0xFFFF;
	pt3=(pt>>16)&0xFFFF;
	pt4=(pt&0xFFFF);
	
/*	pt1|=(pt1<<8&0xFF00)|(pt1>>8&0x00FF);
	pt2|=(pt2<<8&0xFF00)|(pt2>>8&0x00FF);
	pt3|=(pt3<<8&0xFF00)|(pt3>>8&0x00FF);
	pt4|=(pt4<<8&0xFF00)|(pt4>>8&0x00FF);*/
	
	pt1= circ_left(pt1,8);
	pt2= circ_left(pt2,8);
	pt3= circ_left(pt3,8);
	pt4= circ_left(pt4,8);
	
	pt1= circ_left(pt1,9);
	pt2= circ_left(pt2,7);
	pt3= circ_left(pt3,4);
	pt4= circ_left(pt4,1);
	
	pt2= pt2^pt4;
	pt3= pt3^pt1;
	pt1= pt1^pt2;
	pt4= pt4^pt3;
	
	printf("\n%x %x %x %x ",pt1,pt2,pt3,pt4);


	pt=0x0000000000000000;
	pt=((((((pt|pt1)<<16)|pt2)<<16)|pt3)<<16)|pt4;	
	
	}	
	
	pt= pt^k[1];
	printf("\nCipher text: %llx",pt);
}
unsigned long long int sbox(unsigned long long int c)
{
	unsigned long long int z=0,z1=0,z2=0;
	unsigned int i;
	for (i=0;i<8;i++)
	{
		z1 |= s[((c>>(i*4))&0xf)]<<(i*4);
		z2 |= s[(c>>((i+8)*4)&0xf)]<<(i*4);
	}
	z = ((z2<<32)&0xffffffff00000000)|(z1 & 0xffffffff);
	return (z);
}
unsigned int circ_left(unsigned int a,unsigned int i)
{
	a= (((a<<i) | (a>>(16-i))) &0xffff);
	return a;

}
