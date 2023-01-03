#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stddef.h>
#include <execinfo.h>
#include <unistd.h>
#include <link.h>
#include <ucontext.h>

#define MODE_0          1
#define MODE_1          0
#define MODE_2          0
#define MODE_3          0
#define MODE_4          0

#define PRINT_DEBUG     0

#define BTSIZE 100

static void make_segment_fault(void);
static void print_reason(int sig, siginfo_t * info, void *secret);

static void print_reason(int sig, siginfo_t * info, void *secret)
{
	void *array[10];
	size_t size;
#ifdef PRINT_DEBUG
	char **strings;
	size_t i;
	
	size = backtrace(array, 10);
	strings = backtrace_symbols(array, size);
	printf("Obtained %zd stack frames.\n", size);
	
	for (i = 0; i < size; i++)
		printf("%s\n", strings[i]);
	
	free(strings);
#else
	int fd = open("err.log", O_CREAT | O_WRONLY);
	size = backtrace(array, 10);
	backtrace_symbols_fd(array, size, fd);
	close(fd);
#endif
	exit(0);
}

static void *getMcontextEip(ucontext_t * uc)
{
#if defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_6)
	/* OSX < 10.6 */
#if defined(__x86_64__)
	return (void *)uc->uc_mcontext->__ss.__rip;
#elif defined(__i386__)
	return (void *)uc->uc_mcontext->__ss.__eip;
#else
	return (void *)uc->uc_mcontext->__ss.__srr0;
#endif
#elif defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
	/* OSX >= 10.6 */
#if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
	return (void *)uc->uc_mcontext->__ss.__rip;
#else
	return (void *)uc->uc_mcontext->__ss.__eip;
#endif
#elif defined(__linux__)
	/* Linux */
#if defined(__i386__)
	return (void *)uc->uc_mcontext.gregs[14];	/* Linux 32 */
#elif defined(__X86_64__) || defined(__x86_64__)
	return (void *)uc->uc_mcontext.gregs[16];	/* Linux 64 */
#elif defined(__ia64__)		/* Linux IA64 */
	return (void *)uc->uc_mcontext.sc_ip;
#endif
#else
	return NULL;
#endif

}

static void sig_handler(int sig, siginfo_t * info, void *secret)
{
	ucontext_t *uc = (ucontext_t *) secret;

	void *buffer[BTSIZE];
	char **strings;
	int nptrs = 0;

	printf("in sig_handler\n");
	printf("sig is %d, SIGSEGV is %d\n", sig, SIGSEGV);
	printf("info.si_signo is %d, info.si_addr is %p\n",
	       info->si_signo, info->si_addr);

	if (sig == SIGSEGV) {
		nptrs = backtrace(buffer, BTSIZE);
		printf("backtrace() returned %d addresses\n", nptrs);

		if (getMcontextEip(uc) != NULL)
			buffer[1] = getMcontextEip(uc);

		strings = backtrace_symbols(buffer, nptrs);
		if (strings == NULL) {
			perror("backtrace_symbols");
			exit(EXIT_FAILURE);

		}

		printf("backtrace: \n");
		int j;
		for (j = 0; j < nptrs; j++) {
			printf("[%d]%s\n", j, strings[j]);

		}
		free(strings);

		exit(0);

	}

}

static int callback(struct dl_phdr_info *info, size_t size, void *data)
{
	int j;

	printf("name=%s (%d segments)\n", info->dlpi_name, info->dlpi_phnum);

	for (j = 0; j < info->dlpi_phnum; j++)
		printf("\t\t header %2d: address=%10p\n", j,
		       (void *)(info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
	return 0;

}

void call_dump(int signo)
{
	void *buffer[30] = { 0 };
	size_t size;
	char **strings = NULL;
	size_t i = 0;

	size = backtrace(buffer, 30);
	fprintf(stdout, "Obtained %zd stack frames.nm\n", size);

	strings = backtrace_symbols(buffer, size);
	if (!strings) {
		perror("backtrace_symbols.");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < size; i++) {
		fprintf(stdout, "%s\n", strings[i]);
	}

	free(strings);
	strings = NULL;
	exit(0);
}

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
	make_segment_fault();
}

void make_segment_fault(void)
{
	int *ptr = NULL;
	
	*ptr = 0;
}

void my_func2(int sig)
{
	dl_iterate_phdr(callback, NULL);
	exit(0);
}

int main(int argc, char **argv)
{
	int i = 0;

#if MODE_0
	if (signal(SIGSEGV, call_dump) == SIG_ERR)
		perror("Can't catch the SIGSEGV.");
#endif

#if MODE_1
	if (signal(SIGSEGV, my_func) == SIG_ERR)
		perror("Can't catch the SIGSEGV.");
#endif

#if MODE_2
	if (signal(SIGSEGV, my_func2) == SIG_ERR)
		perror("Can't catch the SIGSEGV.");
#endif

#if MODE_3
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGSEGV, &act, NULL);

#endif

#if MODE_4
	struct sigaction myAction;
	myAction.sa_sigaction = print_reason;
	sigemptyset(&myAction.sa_mask);
	myAction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGSEGV, &myAction, NULL);
	sigaction(SIGUSR1, &myAction, NULL);
	sigaction(SIGFPE, &myAction, NULL);
	sigaction(SIGILL, &myAction, NULL);
	sigaction(SIGBUS, &myAction, NULL);
	sigaction(SIGABRT, &myAction, NULL);
	sigaction(SIGSYS, &myAction, NULL);
#endif

	i += 2;
	printf("i=%d \r\n", i);
	run();
	//make_double_free();
	printf("sky is a smart man. \r\n");

	return 0;
}
