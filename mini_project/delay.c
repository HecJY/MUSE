#include "stm32f0xx.h"
#include "stm32f0_discovery.h"


void delay_us(unsigned int);
void delay_ms(unsigned int);


void delay_us(unsigned int n)
{
	n = 10*n;
	while(n>0)
	{
		n--;
	}
}

void delay_ms(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
	{
	  for(j=0;j<6000;j++)
	  ;
	}
}
