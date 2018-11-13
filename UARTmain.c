#include <LPC21XX.h>

unsigned char rx;
char rxbyte();
void txbyte(char);

void main()
{
	PINSEL0=0x05;
	U0LCR=0x9F;
	U0DLL=0x61;
	U0DLM=0x00;
	U0LCR=0x1F;
	while(1)
	{
		rx= rxbyte();
		txbyte(rx);
	}
}
char rxbyte()
{
	while(!(U0LSR & 0x01));
	rx=U0RBR;
	return(rx);
}
void txbyte(char rx)
{
	while(!(U0LSR & 0x20));
	U0THR= rx;
}