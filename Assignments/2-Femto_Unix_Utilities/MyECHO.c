#include <stdio.h>
#include <string.h>
#define SIZE 1000

int main(int argc, char* argv[])
{
//	char str[SIZE];
//	gets(argv[1]);
	if(!strcmp(argv[1], "-n"))
	{
		printf("%s", argv[2]);
	}
	else
	{
		puts(argv[1]);
	}
	//	gets(str);
//	if(argv[1] == "-n")
//	{
//		printf("%s", str);
//	}
//	{
//		puts(str);
//	}
	return 0;
}
