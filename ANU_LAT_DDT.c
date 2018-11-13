#include<stdio.h>

unsigned long long int sbox_key(long long int data)
{
//	unsigned int sbox[]={2,9,7,0xe,1,0xc,0xa,0,4,3,8,0xd,0xf,6,5,0xb};
	unsigned int sbox[]={0,5,5,9,0xa,1,4,1,7,2,2,7,2,5,5,2};//LAT
	//unsigned int sbox[]={0,9,0xC,1,5,8,8,2,0xa,1,4,0xa,2,8,8,1};//DDT
	int a,b=0,i;
	a=data&0xFF;
	for(i=0;i<2;i++)
		{
			b|=sbox[(a>>(i*4))&0xF]<<(i*4);
		}
	data&=0xFFFFFFFFFFFFFF00;
	data|=b;
	return data;
}

unsigned long int sbox_data(long int data)
{
	unsigned int sbox[]={2,9,7,0xe,1,0xc,0xa,0,4,3,8,0xd,0xf,6,5,0xb},i;
	unsigned long int b=0;
	for(i=0;i<16;i++)
		{
			b|=sbox[(data>>(i*4))&0xF]<<(i*4);
		}
		return b;
}

unsigned long long int exor(long long int data,int count)
{
	unsigned long long int temp=0;
	temp=((((data&0xF800000000000000)>>(64-5))^(0x1f&count)));
	data&=0x07FFFFFFFFFFFFFF;
	data|=temp<<(64-5);
	return data;
}

unsigned long int p_layer(unsigned long int data)
{
	int p_layer[]={20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};
	int b=0,i;
	for(i=0;i<32;i++)
	{
		b|=((data>>i)&0x1)<<p_layer[i];
	}
	return b;
}

int main()
{
	unsigned long long int k_lsb=0x1234567890abcdef,k_msb=0x1234567890abcdef,temp=0;
	unsigned long int f1=0x0,f2=0x0,f3=0x0,p_lsb=0x00000000,p_msb=0x00000000,temp1=0,pt=0;
	unsigned long long int count=0,i,total_count,count1=0,j1,z,x2,x1,r1;
	for(i=1;i<16;i++)
	{
		p_msb=0x00;
		p_lsb=i<<0;
		total_count=0;
		count1=0;
		
		for(j1=0;j1<4;j1++)
		{
		

	//	printf("Round %d\n",count);
	//	printf("64-bit plain text : %lx %lx\n",p_msb,p_lsb);
		temp1=p_lsb;
		f1=((p_msb<<3)&0xFFFFFFFFFFFFFFF8)|(((p_msb)>>(32-3))&0x7);
	//	printf("Output of left circular shift by 3 : %lx\n",f1);
		f1=sbox_data(f1);
		x1=f1;
  		for(z=0;z<32;z=z+4)
  			{
  				r1=0;
  				r1=(x1>>(28-z))&0xF;
  				if(r1 !=0)
  				{
  					count1=count1+1;
		  		}
	  		}
	//	printf("SBox of left circular shift by 3 : %lx\n",f1);
		f3=f1^p_lsb;
	//	printf("Output of 1st EX-OR : %lx\n",f3);
		f2=((p_msb>>8)&0x00FFFFFFFFFFFFFF)|(((p_msb)<<(32-8))/*&0xFF00000000000000*/);
	//	printf("Output of right circular shift by 8 : %lx\n",f2);
		f2=sbox_data(f2);
		x2=f2;
  		for(z=0;z<32;z=z+4)
  			{
  				r1=0;
  				r1=(x2>>(28-z))&0xF;
  				if(r1 !=0)
  				{
  					count1=count1+1;
		  		}
	  		}
	//	printf("SBox of right circular shift by 8 : %lx\n",f2);
		pt=f3^f2;//^k_lsb;
	
	/*	temp=k_lsb;
		k_lsb=((temp<<13)&0xFFFFFFFFFFFFE000)|(((k_msb)>>(64-13))&0x1FFF);
		k_msb=((k_msb<<13)&0xFFFFFFFFFFFFE000)|((temp)>>(64-13)&0x1FFF);
		k_lsb=sbox_key(k_lsb);
		k_lsb=exor(k_lsb,count);
		printf("128-bit key text : %llx %llx\n",k_msb,k_lsb);
	
		
		printf("Output of 2nd EX-OR : %lx\n",pt); */
		temp=p_msb;
		p_msb=p_layer(pt);
	//	printf("P-Box of LSB : %lx\n",p_msb);
		p_lsb=p_layer(temp);
	//	printf("P-Box of MSB : %lx\n",p_lsb);
	//	printf("64 bit cipher text %lx %lx\n\n",p_msb,p_lsb);
	//	total_count+=count1;
		printf("\n %d",count1);
	}
		printf("\nActive S-Box for %x = %d",i,count1);
}
}
