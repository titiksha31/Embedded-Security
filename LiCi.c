#include<stdio.h>

unsigned long int sbox(unsigned long int);
unsigned long int circ_right(unsigned long int);
unsigned long int circ_left(unsigned long int);
unsigned char s[16] = {3,0xF,0xE,1,0,0xA,5,8,0xC,4,0xB,2,9,7,6,0xD};
int main()
{
	unsigned int z;
	unsigned long int msb=0x00000000, lsb=0x00000000,x1=0x00,x2=0x00,x3=0x00,x4=0x00,s1=0x00,j,i, temp1=0x00;
	unsigned long long int k[2]={0x0000000000000000,0x0000000000000000}, temp=0x00;
	for(j=0;j<31;j++)
	{
	printf("\nRound %d\n",j);
	printf("\n64 bit plain text: %lx, %lx",msb,lsb);
	printf("\nKey: %llx, %llx",k[0],k[1]);
	s1 = sbox(msb);
	printf("\nOutput of 1st sbox: %lx", s1);
	x1= (lsb^s1^(k[1]/*&0x00000000FFFFFFFF*/));
	printf("\nLSB Output after xor: %lx",x1);
	x2= circ_left(x1);
 	printf("\nLSB output after left shifting by 3: %lx",x2);
 	x3= (s1^x2^((k[1]>>32)/*&0xFFFFFFFF*/));
	//x3= (s1^x2^(k[1]&0x000000000FFFFFFFF));

	printf("\nMSB output after xor: %lx",x3);
	x4= circ_right(x3);
	printf("\nMSB output after right shifting by 7: %lx", x4);
	 	
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
	msb=x2;
	lsb=x4;
	printf("\n Cipher Text is: %lx %lx\n",msb,lsb);
	
}
}
unsigned long int sbox(unsigned long int t)
{
	unsigned long int a=0,i;
	for( i=0;i<32;i=i+4)
	{
		a|=s[((t>>(28-i))&0xf)]<<(28-i); 		
	}
	return(a);
}

 unsigned long int circ_right(unsigned long int lsb)
{
	lsb= (((lsb>>7) | (lsb<<(32-7))) &0xffffffff);
	return(lsb);
	/*unsigned long int a,b,c;
	a = msb>>7;
	c = msb<<(32-7);
	b = a|c;
	return(b);*/

}
unsigned long int circ_left(unsigned long int msb)
{
	msb= (((msb<<3) | (msb>>(32-3))) &0xffffffff);
	return msb;
	/*unsigned long int a,b,c;
	a = msb<<3;
	c= msb>>(32-3);
	b = a|c;
	return(b)*/;

}

 	

