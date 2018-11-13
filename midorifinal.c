#include<stdio.h>

unsigned char sbox[16] = {0xC, 0xA, 0xD, 0x3, 0xE, 0xB, 0xF, 0x7, 0x8, 0x9, 0x1, 0x5, 0x0, 0x2, 0x4, 0x6};
unsigned char shuffle[16] = {0,10,5,15,14,4,11,1,9,3,12,6,7,13,2,8}; 

unsigned char alpha[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1},
{0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0},
{1,0,1,0,0,1,0,0,0,0,1,1,0,1,0,1},
{0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1},
{0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1},
{1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0},
{0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0},
{1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1},
{0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0},
{0,1,1,1,0,0,0,1,1,0,0,1,0,1,1,1},
{0,0,1,0,0,0,1,0,1,0,0,0,1,1,1,0},
{0,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0},
{1,1,1,1,1,0,0,0,1,1,0,0,1,0,1,0},
{1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0}};

void mix_col(unsigned char *temp1, unsigned char* temp2)
{
  unsigned char a,b,c;
  int i,j;

  for(i=0;i<4;i++)
  {
     j=4*i;
   
     a = temp1[j]^temp1[j+3];
     b = temp1[j+1]^temp1[j+2];

     temp2[j]=temp1[j+3]^b;
     temp2[j+1] = temp1[j+2]^a;
     temp2[j+2] = temp1[j+1]^a;
     temp2[j+3] = temp1[j]^b;

  }
}


int main()
{
	unsigned char pt[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char k1[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char k2[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char ct[16],temp1[16],temp2[16],*round_key;
	
	unsigned int count,i,j;
	for (i=0;i<16;i++)
	ct[i]=pt[i]^k1[i]^k2[i] ;
	
	for(count=1;count<16;count++)
	{
		printf("\nRound %d\n",count);
		printf("Plain Text : ");
		for(i=0;i<16;i++)
		printf("%x",ct[i]);
		printf("\n");
		
		for(i=0;i<16;i++)
		ct[i]=sbox[ct[i]];
		printf("Output of SBox : ");
		for(i=0;i<16;i++)
		printf("%x",ct[i]);
		printf("\n");
		
			for (i=0;i<16;i++)
			temp1[i]= ct[shuffle[i]];
			printf("Output of Shuffle Cell : ");
			for(i=0;i<16;i++)
			printf("%x",temp1[i]);
			printf("\n");
			
			mix_col(temp1,temp2);
			
			for (i=0;i<16;i++)
			ct[i]=temp2[i];
			printf("Output of Mix Column : ");
			for(i=0;i<16;i++)
			printf("%x",ct[i]);
			printf("\n");
			
			for(i=0;i<16;i++)
			ct[i]= ct[i]^(alpha[count][i]);
			
			if(count%2)
			round_key=k1;
			else
			round_key=k2;
			
			for (i=0;i<16;i++)
			ct[i]=ct[i]^round_key[i];
			
			printf("Cipher Text : ");
			for(i=0;i<16;i++)
			printf("%x",ct[i]);
			printf("\n");
			
	}
	
	for(i=0;i<16;i++)
	ct[i]=sbox[ct[i]];
	
	for (i=0;i<16;i++)
	ct[i]=ct[i]^k1[i]^k2[i] ;
	
	printf("\nFinal Cipher Text : ");
	for (i=0;i<16;i++) 
	printf("%x",ct[i]);
}
