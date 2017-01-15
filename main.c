#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define ALIGN_MEM 512

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char table_encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char table_decode[] = {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
    52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
    -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
}; 

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
			return;
			break;

		deafult:
			break;
	}
}

void Encoding()
{
	char *buffer_in, *buffer_out;
	unsigned int len_in, len_out, index_in, index_out;

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
		buffer_out[index_out + 0] = table_encode[(buffer_in[index_in + 0]&0b11111100) >> 2];
		buffer_out[index_out + 1] = table_encode[(buffer_in[index_in + 0]&0b00000011) << 4 | (buffer_in[index_in + 1]&0b11110000) >> 4];
		buffer_out[index_out + 2] = table_encode[(buffer_in[index_in + 1]&0b00001111) << 2 | (buffer_in[index_in + 2]&0b11000000) >> 6];
		buffer_out[index_out + 3] = table_encode[(buffer_in[index_in + 2]&0b00111111)];
		index_out += 4;
	}

	switch(len_in%3)
	{
		case 1:
			buffer_out[index_out + 0] = table_encode[(buffer_in[index_in + 0]&0b11111100) >> 2];
			buffer_out[index_out + 1] = table_encode[(buffer_in[index_in + 0]&0b00000011) << 4];
			buffer_out[index_out + 2] = '=';
			buffer_out[index_out + 3] = '=';
			index_out += 4;
			break;
			
		case 2:
			buffer_out[index_out + 0] = table_encode[(buffer_in[index_in + 0]&0b11111100) >> 2];
			buffer_out[index_out + 1] = table_encode[(buffer_in[index_in + 0]&0b00000011) << 4 | (buffer_in[index_in + 1]&0b11110000) >> 4];
			buffer_out[index_out + 2] = table_encode[(buffer_in[index_in + 1]&0b00001111) << 2];
			buffer_out[index_out + 3] = '=';	
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
	
	if(strlen(buffer_in) % 4)
	{
		printf("Padding Error...\n");
		free(buffer_in);
		return;
	}

	len_out = strlen(buffer_in)/4 * 3;
	if(buffer_in[len_in-1] == '=')
		len_out--;
	if(buffer_in[len_in-2] == '=')
		len_out--;
	buffer_out = (char*)malloc(len_out);

	for(index_in = 0; index_in < len_in; index_in += 4)
	{
		buffer_out[index_out + 0] = (table_decode[buffer_in[index_in + 0]]&0b00111111) << 2 | (table_decode[buffer_in[index_in + 1]]&0b00110000) >> 4;
		buffer_out[index_out + 1] = (table_decode[buffer_in[index_in + 1]]&0b00001111) << 4 | (table_decode[buffer_in[index_in + 2]]&0b00111100) >> 2;
		buffer_out[index_out + 2] = (table_decode[buffer_in[index_in + 2]]&0b00000011) << 6 | (table_decode[buffer_in[index_in + 3]]&0b00111111);
		index_out += 3;
	}

	write(STDOUT, buffer_out, len_out);
	putchar('\n');
	free(buffer_in);
	free(buffer_out);
}
