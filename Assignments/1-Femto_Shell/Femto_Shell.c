#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100];
	while(1)
	{
		printf("Enter a string to echo it > ");
		gets(str);
		if(!strcmp(str, "exit"))
		{
			printf("Good Bye :)\n");
			break;
		}
		else
		{
			printf("You Said: ");
			puts(str);
		}
	}
	return 0;
}
