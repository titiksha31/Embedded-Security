//*******Perfect******//
#include<LPC21xx.h>
void txbyte(char rx1);
char rxbyte(void);
unsigned long long int sbox(unsigned long long int);
unsigned int s[16]= {3,0x0f,0x0e,1,0,0x0a,5,8,0x0c,4,0x0b,2,9,7,6,0x0d};
int main()
{
	unsigned long long int k[2],temp2,temp=0;
	unsigned long int msb=0,lsb=0,temp1=0;
	unsigned int i,j,m,data[2],j1=0,i1=0;;

 
	PINSEL0=0x05;
	U0LCR=0x9A;
	U0DLL=0x61;
	U0DLM=0x00;
	U0LCR=0x1A;

	// Take Plaintext input     Data[0] = MSB Plaintext             Data[1] = LSB Plaintext
	txbyte('P');
	txbyte('-');
	for (j=0;j<2;j++)
	{
		data[j]=0;
		for (i=0;i<32;i+=4)
		{
			m=rxbyte();
			txbyte(m);
			if (m>0x2f && m<0x3a)
			{
				temp2=m-0x30;
			}
			if(m>=97 && m<=102)
			{
				temp2=m-87;
			}
			data[j]+=(temp2 & 0xf)<<(28-i); 
		}	
	}

	// Take Key as Input (128 bit)

	txbyte(' ');
	txbyte('K');
	txbyte('-');
	for(i=0;i<2;i++)
	{
		//k[i]=0;
		for(j=0;j<64;j+=4)
		{
			m=rxbyte();
			txbyte(m);
			if(m>0x2F&&m<0x3A)
			{
				temp2=m-0x30;
			}
			if(m>=97&&m<=102)
			{
				temp2=m-87;
			}
			k[i]+=(temp2&0xF)<<((60-j));
		}
	}


// Cipher Code
 	for(j1=0;j1<31;j1++)
	{
		msb=(data[0]);
		lsb=(data[1]);
	
		msb=sbox(msb);
		temp1=msb;
		
		lsb=lsb^temp1^(k[1]&0x00000000ffffffff);
		lsb=((lsb<<3)|(lsb>>29)&0xffffffff);   //lsb xor with key and msd left shifted by 3
	
		temp2=k[1];
		temp2=temp2>>32;
		msb=msb^lsb^(temp2&0x00000000ffffffff);
		msb=((msb>>7)|(msb<<25)&0xffffffff);  //XOR output right shifted by 7
		
		data[0]=lsb;
		data[1]=msb;
		
		temp=k[1];
			k[1]=(temp<<13)|k[0]>>(64-13);
			k[0]=(k[0]<<13)|(temp>>(64-13));
			
			m=0;
			for(i1=0;i1<2;i1++)
			{
				m|=(s[(k[1]>>(i1*4))&0x0f]<<i1*4)&0xff;	
			}	
			k[1]&=(0xffffffffffffff00);
			k[1]|=(m&0xff);
			
			
			temp=(((k[1]&0xf800000000000000)>>(64-5))^(0x1f&j1));
			k[1]&=0x07ffffffffffffff;
			k[1]|=temp<<(64-5);
		
		
	
		temp=0;
	}			 // Display Ciphertext after all rounds
	txbyte(' ');
	txbyte('C');		
	txbyte('-');
	for(j=0; j<2; j++)
	{
		for (i=0; i<32; i+=4)
		{
			temp2=(data[j]>>(28-i))&0xf;	
			if(temp2<10)
			txbyte(0x30+temp2);
			else
			txbyte(87+temp2);
		}
	}
	
	return 0;
}

	void txbyte(char rx1)
	{
		while(!(U0LSR & 0x20));
		U0THR=rx1;
	}
	
	char rxbyte()
	{
		unsigned char rx;
		while(!(U0LSR & 0x01));
		rx=U0RBR;
		return(rx);
	}


unsigned long long int sbox(unsigned long long int c)
{
	unsigned long long int i,z=0,z1=0,z2=0;
	for (i=0;i<8;i++)
	{
		z1 |= s[((c>>(i*4))&0xf)]<<(i*4);
		z2 |= s[(c>>((i+8)*4)&0xf)]<<(i*4);
		
	}
	z = ((z2<<32)&0xffffffff00000000)|(z1 & 0xffffffff);
	 return (z);
}
