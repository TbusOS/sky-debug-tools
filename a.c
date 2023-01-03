#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>

void my_func(void)
{
	int j, nptrs;
#define SIZE 100
	void *buffer[100];
	char **strings;

	nptrs = backtrace(buffer, SIZE);
	printf("backtrace() returned %d addresses \r\n", nptrs);

	backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO);

}

void run(void)
{
	my_func();

}

int main(int argc, char **argv)
{
//	run();
	int *data;

	data = malloc(3);
	free(data);
	free(data);


	return 0;

}
