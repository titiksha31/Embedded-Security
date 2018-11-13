//*******Perfect******//
#include<LPC21xx.h>
void txbyte(char rx1);
char rxbyte(void);
unsigned long long int sbox(unsigned long long int);
unsigned long long int player(unsigned long long int);
unsigned int P[64]={20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};
unsigned int s[16]= {2,9,7,0xe,1,0xc,0x0a,0,4,3,8,0xd,0x0f,6,5,0x0b};
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
 for(j1=0;j1<25;j1++)
	{
		lsb=(data[1]);
		msb=(data[0]);
		temp1=(msb<<3)|(msb>>29);//msb data left shifted by 3
	
		temp1=sbox(temp1);	//Sbox of data msb  left shifted by 3
		temp1=temp1^lsb;	  //XOR output
		
		temp2=(msb>>8)|(msb<<24);  //msb data right shifted by 8

		temp2=sbox(temp2); //Sbox of data msb right shifted by 8

		temp2=temp2^temp1^k[1];
		
		msb=player(msb); //		pl=player(pl)

		lsb=player(temp2);  //Pbox output 2
	
		data[0]=lsb;
		data[1]=msb;

			//key scheduling
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
	}
			 // Display Ciphertext after all rounds
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
unsigned long long int player(unsigned long long int b)
{
	unsigned long long int c=0,i;
	for(i=0;i<32;i++)
	{
		c |=((b>>i) & 0x1) << P[i];
	}
	return(c);
}
