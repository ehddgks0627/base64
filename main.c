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
	int len_in, len_out;
	buffer_in = (char*)malloc(ALIGN_MEM);
	len_in = 0;

	printf("input : ");
	fflush(stdout);
	do
	{
		if(!(len_in % ALIGN_MEM) && len_in)
			buffer_in = (char*)realloc(buffer_in, len_in + ALIGN_MEM);
		read(0, &buffer_in[len_in], 1);
	}while(buffer_in[len_in++] != '\n');
	buffer_in[--len_in] = '\x00';

	len_out = (len_in + 2 - ((len_in + 2) % 3)) / 3 * 4;
	buffer_out = (char*)malloc(len_out);

	free(buffer_in);
	free(buffer_out);
}

void Decoding()
{
	
}
