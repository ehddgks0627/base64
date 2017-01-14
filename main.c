#include <stdio.h>

char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

void Encoding();
void Decoding();

int main(void)
{
	int choice;
	do
	{
		printf("1. Encoding\n");
		printf("2. Decoding\n");
		printf("3. Exit\n");
		printf(">>> ");
		scanf("%d",&choice);
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

}

void Decoding()
{

}
