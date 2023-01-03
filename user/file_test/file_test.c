#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
//#include "libdemo.h"

#define DEV_BBL_NAME "/dev/bbl"
#define OP_NUM	32
#define MODE_0  0
#define MODE_1  1

static void	err_ret(const char *, ...);

int main(int argc, char *argv[])
{
#if MODE_1
	int			i;
	struct stat	buf;
	char		*ptr;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
	exit(0);	
#endif	
	
#if MODE_0
	printf("hello word!!!\n");
	//demo_show("hello word!!!");
	
	int fd;
	char data2[256] = {0};
	int ret, iRet;

	if (argc != 2) {
		printf("argc is not equal 2.\r\n");
		return -2;
	}

	fd = open(DEV_BBL_NAME, O_RDWR);
	if (fd < 0) {
		printf("fd=%d %s errno=%d\r\n", fd, strerror(errno), errno);
		printf("open file %s failed!\r\n", DEV_BBL_NAME);
		return -1;
 	}
	printf("open ok --->fd=%d\r\n", fd);
	
	lseek(fd, 0, SEEK_SET);
	ret = read(fd, data2, OP_NUM);
	if (ret <  0) {
		printf("user read error\r\n");
		printf("fd=%d %s errno=%d\r\n", fd, strerror(errno), errno);
		printf("read file %s failed!\r\n", DEV_BBL_NAME);
		return -1;		
	}
	
	printf("read ok. \r\n");
	printf("\r\n");

	close(fd);
#endif

	return 0;
}