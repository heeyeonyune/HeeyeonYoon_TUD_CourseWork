#include <stdio.h>
#include <stdint.h>
#include <prbs.h>

uint32_t my_random(uint32_t lower,uint32_t upper)
{
    return (prbs()%(upper-lower))+lower;
}


uint32_t prbs()
{
	uint32_t shift_register=1234;
	// This is an unverified 31 bit PRBS generator
	// It should be maximum length but this has not been verified 
	unsigned long new_bit=0;
	static int busy=0; // need to prevent re-entrancy here
	if (!busy)
	{
		busy=1;
		new_bit= ((shift_register & (1<<27))>>27) ^ ((shift_register & (1<<30))>>30);
		new_bit= ~new_bit;
		new_bit = new_bit & 1;
		shift_register=shift_register << 1;
		shift_register=shift_register | (new_bit);
		busy=0;
	}
	return shift_register & 0x7fffffff; // return 31 LSB's 
}
/*int lol()
{
	for(int i=0;i<100;i++)
		printf("%ld\n",prbs());
}*/