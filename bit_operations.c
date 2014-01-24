#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Gets the bit representation of an unsigned char (byte) as an integer array */
char* byte_get_bits(unsigned char byte)
{
	int length = 8*sizeof(char);
	char* bit_array = malloc(length);
	unsigned char mask = 128;

	int i;
	for (i=0; i<length; i++, byte = byte << 1)
	{
		bit_array[i] = (128 == (byte & mask)) ? '1' : '0';
	}
	return bit_array;
}

int main(void)
{
	unsigned char byte = 8;
	char *output = byte_get_bits(byte);	
	
	int i;
	for(i=0; i<8; i++)
	{
		printf("%c", output[i]);
	}
	printf("\n");

	return 0;
}