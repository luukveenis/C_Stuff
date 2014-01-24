#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Gets the bit representation of an unsigned char (byte) as a string
 * Inputs:
 * byte - the character to get the representation for (generally 1 byte)
 * bit_length - the bit length of a character (machine dependent)
 */
char* byte_get_bits(unsigned char byte, int bit_length)
{
	/* intialize the array */
	int array_size = (bit_length * sizeof(char)) + 1;
	char *bit_array = malloc(array_size);
	unsigned char mask = pow(2, bit_length-1);
	
	/* find individual bit values */
	int i;
	for (i=0; i<bit_length; i++, byte = byte << 1)
	{
		bit_array[i] = (mask == (byte & mask)) ? '1' : '0';
	}
	/* null terminate the string */
	bit_array[array_size - 1] = '\0';

	return bit_array;
}

/* Gets the bit representation of an integer as a string 
 * Inputs: 
 * input - the integer to get the bits for
 * int_length - the bit length of an integer (machine dependent) */
char* int_get_bits(int input, int int_length)
{
	/* Initialize the array */
	int array_size = int_length*sizeof(char) + 1;
	char *bit_array = malloc(array_size);
	unsigned int mask = pow(2, int_length-1);

	/* Find the bit values at each position */
	int i;
	for (i=0; i<int_length; i++, input = input << 1)
	{
		bit_array[i] = (0 != (input & mask)) ? '1' : '0';
	}
	/* null terminate the string */
	bit_array[array_size-1] = '\0';
	
return bit_array;
}

int main(void)
{
	/* local bit lengths of types */
	int c_bitlength = 8*sizeof(char);
	int i_bitlength = 8*sizeof(int);

	/* sample inputs */
	unsigned char byte = 8;
	int regular_int = 12;
	int unsigned_int = 10;
	int regular_neg_int = -4;

	/* calculate the output */
	char *output1 = byte_get_bits(byte, c_bitlength);	
	char *output2 = int_get_bits(regular_int, i_bitlength);
	char *output3 = int_get_bits(unsigned_int, i_bitlength);
	char *output4 = int_get_bits(regular_neg_int, i_bitlength);
	
	/* display results */
	printf("Unsigned char 8 = %s\n", output1);
	printf("Regular int 12 = %s\n", output2);
	printf("Unsigned int 10 = %s\n", output3);
	printf("Regular int -4 = %s\n", output4);

	return 0;
}