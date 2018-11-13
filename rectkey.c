#include<stdio.h>
unsigned int sbox(unsigned  int);

unsigned long int RC[25]={1,2,4,9,12,5,0x0B,16,0x0C,19,13,7,0x0F,0x1F,0x1E,0x1C,18,11,3,6,0x0D,0x1B,17,0x0E,0x1D};
unsigned int sb[16] = {6,5,0xC,0xA,1,0xE,7,9,0xB,0,3,0xD,8,0xF,4,2};
int main()
{
		unsigned long int ka=0x00,kb=0x00,kc=0x00,kd=0x00,keya=0x00,keyb=0x00,keyc=0x00,keyd=0x00,opka=0x00,opkb=0x00,opkc=0x00,opkd=0x00,ks,keya1;
		int i,j;
		for(j=0;j<25;j++)
		{
			keya1=keya;
			for(i=7;i>-1;i--)
			{
				ka=(keya>>i)&0x01;
				kb=((keyb>>i)&0x01)<<1;
				kc=((keyc>>i)&0x01)<<2;
				kd=((keyd>>i)&0x01)<<3;
				ks=sbox((((ka|kb)|kc)|kd));
				//printf("\n%x",ks);
				opka= (opka<<1)|(ks&0x1);
				opkb= (opkb<<1)|((ks>>1)&0x1);
				opkc= (opkc<<1)|((ks>>2)&0x1);
				opkd= (opkd<<1)|((ks>>3)&0x1);
			}
			keya=((((opka<<8)|(opka>>(32-8)))&0xffffffff))^opkb;
			keyb=opkc;
			keyc=((((opkc<<16)|(opkc>>(32-16)))&0xffffffff))^opkd;
			keyd=opka;
			keya1=((keya&0x1f)^(0x1f&RC[j]));
			keya= keya&0xffffffe0;
			keya=keya|keya1;
//	temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&j));
//	k[1] &= 0X07FFFFFFFFFFFFFF;
//	k[1] |= temp<<(64-5);
			printf("\nKey after round %d : %lx %lx %lx %lx ",j,keya, keyb,keyc,keyd);
		}
}
unsigned int sbox(unsigned int t)
{
	int z;
	z = sb[t & 0xf];
	return(z);
}
