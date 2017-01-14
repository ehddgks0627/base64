#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define ALIGN_MEM 512

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

void Encoding();
void Decoding();

int main(void)
{
	int choice;
	char dummy;
	do
	{
		printf("1. Encoding\n");
		printf("2. Decoding\n");
		printf("3. Exit\n");
		printf(">>> ");
		scanf("%d%c",&choice, &dummy);
	}while(choice & ~0b11);

	switch(choice)
	{
		case 1:
			Encoding();
			break;

		case 2:
			Decoding();
			break;

		case 3:
			return 0;
			break;

		deafult:
			break;
	}
}

void Encoding()
{
	char *buffer_in, *buffer_out;
	int len_in, len_out, index_in, index_out;

	buffer_in = (char*)malloc(ALIGN_MEM);
	len_in = 0;
	index_out = 0;

	printf("input : ");
	fflush(stdout);
	do
	{
		if(!(len_in % ALIGN_MEM) && len_in)
			buffer_in = (char*)realloc(buffer_in, len_in + ALIGN_MEM);
		read(STDIN, &buffer_in[len_in], 1);
	}while(buffer_in[len_in++] != '\n');
	buffer_in[--len_in] = '\x00';

	len_out = (len_in + 2 - ((len_in + 2) % 3)) / 3 * 4;
	buffer_out = (char*)malloc(len_out);

	for(index_in = 0; index_in < len_in - len_in % 3; index_in += 3)
	{
		buffer_out[index_out + 0] = table[(buffer_in[index_in + 0]&0b11111100) >> 2];
		buffer_out[index_out + 1] = table[(buffer_in[index_in + 0]&0b00000011) << 4 | (buffer_in[index_in + 1]&0b11110000) >> 4];
		buffer_out[index_out + 2] = table[(buffer_in[index_in + 1]&0b00001111) << 2 | (buffer_in[index_in + 2]&0b11000000) >> 6];
		buffer_out[index_out + 3] = table[(buffer_in[index_in + 2]&0b00111111)];
		index_out += 4;
	}
	switch(len_in%3)
	{
		case 1:

			break;
			
		case 2:

			break;

		default:
			break;
	}
	write(STDOUT, buffer_out, len_out);
	putchar('\n');
	free(buffer_in);
	free(buffer_out);
}

void Decoding()
{
	
}
