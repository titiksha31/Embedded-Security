#include<stdio.h>

unsigned int sbox(unsigned  int);
unsigned int circ_left(unsigned int,unsigned int);

unsigned int sb[16] = {6,5,0xC,0xA,1,0xE,7,9,0xB,0,3,0xD,8,0xF,4,2};

int main()
{
	unsigned int inpa=0x0000,inpb=0x0000,inpc=0x0000,inpd=0x0000,opa=0x0, opb=0x0,opc=0x0,opd=0x0,a=0x0,b=0x0,c=0x0,d=0x0,j,s;
	char i;
	for(j=0;j<25;j++)
	{

	for(i=15;i>-1;i--)
	{
		a=(inpa>>i)&0x01;
		b=((inpb>>i)&0x01)<<1;
		c=((inpc>>i)&0x01)<<2;
		d=((inpd>>i)&0x01)<<3;
		//printf("%x ",a);printf("%x ",b);printf("%x ",c);printf("%x ",d);
		s=sbox((((a|b)|c)|d));
		printf("%x",s);
		/*opd|=(((s>>3)&0x01)<<i);
		opc|=(((s>>2)&0x01)<<i);
		opb|=(((s>>1)&0x01)<<i);
		opa|=(((s>>0)&0x01)<<i);*/
		opa= (opa<<1)|(s&0x1);
		opb= (opb<<1)|((s>>1)&0x1);
		opc= (opc<<1)|((s>>2)&0x1);
		opd= (opd<<1)|((s>>3)&0x1);
		/*inpa=opa;
		inpb=opb;
		inpc=opc;
		inpd=opd;	*/	
	}
	inpa=opa&0xFFFF;
	inpb=circ_left(opb,1)&0xFFFF;
	inpc=circ_left(opc,12)&0xFFFF;
	inpd=circ_left(opd,13)&0xFFFF;
	
	opa=0;
	opb=0;
	opc=0;
	opd=0;
	printf("\nRound : %d", j);
	printf("\n %x  %x  %x  %x \n",inpa, inpb, inpc, inpd);
}
	printf("\n Cipher Text: %x  %x  %x  %x \n",inpa, inpb, inpc, inpd);

}
unsigned int sbox(unsigned int t)
{
	int z;
	z = sb[t & 0xf];

	return(z);
}
unsigned int circ_left(unsigned int msb,unsigned int i)
{
//	unsigned long int a,b,c;
//	a = msb<<i;
//	c= msb>>(16-i);
//	b = a|c;
//	return(b);
	msb= (((msb<<i) | (msb>>(16-i))) &0xffff);
	return msb;


}
