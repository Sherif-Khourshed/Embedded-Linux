/*
 * Will add more test cases for set built-in command
 * Will update it soon with more test cases and enhancement
 * */

#include <stdio.h>
#include <string.h>
#include <sys/types.h> // fork
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 1000

void shellInit();
void parentFun();
void childFun();
void localVar();
void setFun();
void exportFun();

char buf[SIZE];
char local_var[SIZE][SIZE];	// Will use array of pointers
int exec_ret;
int var_count = 0;

int main(void)
{
	int ret_pid = 0;
	char s[] = {'='};
	char s2[] = {"export"};
	while(1)
	{
		/* Init the shell*/
		shellInit();
		/* Exit the failed process and shell */
		if(!strcmp(buf, "exit"))
		{
			if(exec_ret == -1)
				printf("You left the failed process, run exit again to leave the shell\n");
			else
				printf("You left the shell, Good Bye :)\n");
			break;
		}
		/* Local Variables */
		else if(strstr(buf, s))
		{
			localVar();
		}
		/* set built-in command */
		else if(!strcmp(buf, "set"))
		{
			setFun();
		}
		/* export built-in command */
		else if(strstr(buf, s2))
		{
			exportFun();
		}
		/* Fork */
		else
		{
			ret_pid = fork();

			if(ret_pid < 0)
			{
				printf("Fork failed\n");
			}
			else if(ret_pid > 0)
			{
				parentFun();
			}
			else
			{
				childFun();
			}
		}
	}
	return 0;
}


void shellInit()
{
	int i;
	do{
		printf("Enter Your Command > ");
		fgets(buf, SIZE, stdin);
	}while(buf[0] == '\n');

	int len = strlen(buf);
	buf[len-1] = 0;
}
void parentFun()
{
	int status;
	//printf("I am the parent, My ID is %d and my child ID is %d\n", getpid(), ret_pid);
	wait(&status);
}
void childFun()
{
	//printf("I am the child, My ID is %d and my parent ID is %d\n", getpid(), getppid());
	char *newargv[SIZE];
	char **next = newargv;
	char *temp = NULL;

	temp = strtok(buf, " ");
	while (temp != NULL)
	{
		*next++ = temp;
		temp = strtok(NULL, " ");
	}

	exec_ret = execvp(newargv[0], newargv);
	printf("Exec function failed\n");
}
void localVar()
{
	int i = 0, j = 0;
	for(i = 0; buf[i] != '\0'; i++)
	{
		if(buf[i] != ' ')
		{
			local_var[var_count][i] = buf[i];
		}
		else
		{
			printf("command not found, variables shouldn't contain space\n");
			var_count--;
			break;
		}
	}
	var_count++;
}
void setFun()
{
	int i;
	for(i = 0; i < var_count; i++)
	{
		printf("local_var[%d]: %s\n", i, local_var[i]);
	}
}

void exportFun()
{
	char tmp[SIZE];
	char tmp2[SIZE];
	char tmp3[SIZE];
	int counter = 0, i, j, z;
	while(buf[counter] != ' ')
	{
		counter++;
	}
	for(i = 0; buf[i] != '\0'; i++)
	{
		tmp[i] = buf[counter+1];
		counter++;
	}

	for(i = 0; i < var_count; i++)
	{
		for(j = 0; local_var[i][j] != '='; j++)
		{
			tmp2[j] = local_var[i][j];
			if(!strcmp(tmp, tmp2))
			{
				setenv(&tmp, &local_var[i][j+2], 1);
				break;
			}
		}
		if(!strcmp(tmp, tmp2))
		{
			break;
		}
		for(z = 0; z < j; z++)
		{
			tmp3[z] = tmp2[z];
			tmp2[z] = 0;
		}
	}
}

