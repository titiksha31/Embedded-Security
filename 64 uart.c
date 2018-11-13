#include<LPC21xx.h>
char receive(void);
void transmit(char);
unsigned char rx;
unsigned char r1;
unsigned char r2;
unsigned char i;
unsigned char m;
unsigned long long int data;
unsigned char temp;
void main()
{
		PINSEL0=0X00000005;
		U0LCR=0X9F;
		U0DLL=0X61;
		U0DLM=0X00;
		U0LCR=0X1F;
			transmit('P');
			transmit(' ');
			for(i=0;i<=15;i++)
			{
				m=receive();
				transmit(m);
				if(m>0x2F&&m<0x3A)
				{
					temp= m-0x30;
				}
				if(m>=0x61&&m<=0x66)
				{
					temp=m-87;
				}
				data+=((temp&0x0F)<<(15-i)*4);
			}			  
}

char receive()
{
	while(!(U0LSR&0X01));
	rx=U0RBR;
	return(rx);
}

void transmit(char rx)
{
	while(!(U0LSR&0X20));
	U0THR=rx;
}		
 