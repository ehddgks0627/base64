#include <stdio.h>

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
