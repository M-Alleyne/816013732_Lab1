//Michael Alleyne
//816013732

#include "sam.h"

int main(void)
{
	
	int i;
	
	SystemInit();
	
	REG_PORT_DIR0 |= 1ULL<<32;
	
	while (1)
	{
		
		REG_PORT_OUT0 |= 1 << 21;
		for(i=0;i<100000;i++){}
		
		REG_PORT_OUT0 &= (~(1<<21));
		for (i=0;i<100000;i++){}
		
	}
}