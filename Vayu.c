#include<stdio.h>

unsigned long int sbox(unsigned long int);
unsigned long int player(unsigned long int);
unsigned long int circ_right(unsigned long int,unsigned int );
unsigned long int circ_left(unsigned long int,unsigned int);
unsigned char s[16] = {6,3,0xA,5,0xC,8,1,0xB,0,0xD,9,0xE,0xF,2,7,4};
unsigned char p[32] = {24,8,0,19,23,28,12,4,9,25,18,1,13,5,22,29,17,2,10,26,6,14,30,21,3,16,27,11,31,20,7,15};

int main()

{
	unsigned int z=0;
	unsigned long int msb=0x00000000, lsb=0x00000000,j,i=0, F1=0x00, F2=0x00,lsb1,msb1;
	//x1=0x00, x2=0x00, x3=0x00, x4=0x00, s1=0x00, s2=0x00, p1=0x00, p2=0x00,c1=0x00,c2=0x00,c3=0x00,c4=0x00;
	unsigned long long int k[2]={0x0000000000000000,0x0000000000000000}, temp=0x00;
	for(j=0;j<31;j++)
	{
		printf("\nRound %d\n",j);
		printf("\n64 bit plain text: %lx, %lx",msb,lsb);
		printf("\nKey: %llx, %llx",k[0],k[1]);
		F1= sbox(msb);
		/*c1= circ_left(s1,7);
		c2= circ_left(s1,3);
		x1= (c1^c2);*/
		F1= (circ_left(F1,7))^(circ_left(F1,3));
		lsb=(F1^lsb);
		lsb1=player(lsb);
		F2= sbox(lsb);
		/*c3= circ_right(s2,7);
		c4= circ_right(s2,3);
		x3= (c3^c4);*/
		F2=(circ_right(F2,7))^(circ_right(F2,3));

		msb= (F2^msb^k[1]);
		msb1= player(msb);
		
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
		msb=lsb1;
		lsb=msb1;
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
 unsigned long int player(unsigned long int c)
 {
 	unsigned long int i, b=0;
	 
    for (i=0; i<32;i++)
     {
 		 b |= ((c>>i)&0x1)<<p[i];
	}
	return(b);
 }
 unsigned long int circ_right(unsigned long int a,unsigned int i)
{
	a=(((a>>i) | (a<<(32-i))) &0xffffffff);
	return(a);

}
unsigned long int circ_left(unsigned long int a,unsigned int i)
{
	a=(((a<<i)|(a>>(32-i)))&0xffffffff);
	return(a);

}

