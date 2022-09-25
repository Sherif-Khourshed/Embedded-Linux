#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000

int main(void)
{
	char* ptr;
	char* str;
	
	ptr = (char*)malloc(1000 * sizeof(char));
	str =  getcwd(ptr, 1000 * sizeof(char));
	if(strcmp(str, ptr))
	{
		printf("Error Occurred while getting the currunt directory\n");
		return -1;
	}
	puts(str);	
	free(ptr);
#if 0
	char buf[SIZE];
        char* str;
	//char *getcwd(char *buf, size_t size);
	str = getcwd(buf, SIZE);
        if(strcmp(str, buf))
	{
		printf("Error Occurred while getting the currunt directory\n");
		return -1;
	}
	puts(str);	
#endif
	return 0;
}
