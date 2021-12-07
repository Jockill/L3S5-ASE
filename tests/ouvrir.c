#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void stopMe(char* msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

typedef struct test
{
	int a;
	int b;
} test;

int main()
{
	int fd = shm_open("/test", O_RDWR|O_CREAT, 0666);
	if (fd == -1)
		stopMe("open");

	if(ftruncate(fd, sizeof(test)) == -1)
		stopMe("open");

	void* map = mmap(NULL, sizeof(test), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	test* s = (test*)map;
	s->a = 10;
	s->b = 20;

	printf("a=%d\nb=%d", s->a, s->b);

	getchar();

	printf("a=%d\nb=%d", s->a, s->b);
	munmap(map, sizeof(test));
	return 0;
}
