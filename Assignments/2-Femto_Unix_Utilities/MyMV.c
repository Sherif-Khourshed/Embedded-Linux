// mv utility
// argc = 3
// open 2 files
// read file 1
// create and write file 2

#include <stdio.h>
#include <sys/types.h>	// headers to open and possibly create a file
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	// header to read and write from a file descriptor

#define SIZE 100

int main(int argc, char* argv[])
{
	int fd1, fd2, r_count, w_count;
	char buf[SIZE];	
	if(argc != 3)
	{
		printf("Error occurred, Invalid number of arguments\n");
		return -1;
	}

	// int open(const char *pathname, int flags, mode_t mode);
	//fd1 = open(argv[1], O_TMPFILE);
	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1)
	{
		printf("Error occurred, The file 1 can't be opened, May be it needs permission or not exist\n");
		return -1;		
	}
	fd2 = open(argv[2], O_WRONLY|O_CREAT, 0644);
	if(fd2 == -1)
        {
                printf("Error occurred, The file 2 can't be opened or created\n");     
		return -1;
        }

	//ssize_t read(int fd, void *buf, size_t count);
	//ssize_t write(int fd, const void *buf, size_t count);	
	while((r_count = read(fd1, buf, SIZE)) != 0)
	{
		write(fd2, buf, r_count);		
	} 

	remove(argv[1]);
	close(fd2);
	return 0;
}
