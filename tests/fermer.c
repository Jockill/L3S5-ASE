#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

/* Fonctions d'arret ********************/
void stopMe(char* msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}
/****************************************/

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
		stopMe("truncate");


	void* map = mmap(NULL, sizeof(test), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	test* s = (test*)map;

	printf("a=%d\nb=%d", s->a, s->b);

	s->a = 30;
	s->b = 40;

	munmap(map, sizeof(test));
	return 0;
}
