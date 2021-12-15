#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "asem.h"
#include "shm.h"

/* Fonctions d'arret ********************/
void stopMe(char* msg)
{
	adebug(1, "%s\n", msg);
	exit(1);
}

void killMe(char* msg)
{
	adebug(1, "%s\nErrno = %d", msg, errno);
	exit(1);
}

void closeMe(char* msg, int fdc, ...)
{
	va_list fdv;
	va_start(fdv, fdc);

	adebug(1, "%s\nErrno = %d", msg, errno);
	for (int i=0; i<fdc; i++)
		close(va_arg(fdv, int));
	exit(1);
}
/****************************************/

/* Gestion map **************************/

void* getSegment(char* nom)
{
	int fd = shm_open(nom, O_RDWR, 0666);
	CHECK(fd, "getMmap, shm_open");
	segment* tmp = (segment*)mmap(NULL, sizeof(segment),
								  PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (tmp == MAP_FAILED)
	{
		fprintf(stderr, "getMmap, mmap\n");
		exit(1);
	}

	size_t taille = (sizeof(segment) + tmp->nbrBox*sizeof(struct box)
					+ tmp->nbrBox*sizeof(struct place));
	void* map = mmap(NULL, taille, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		fprintf(stderr, "getMmap, mmap\n");
		exit(1);
	}

	munmap(tmp, sizeof(segment));
	CHECK(close(fd), "getSegment, close");
	return map;
}

size_t mapSize(segment* s)
{
	return (sizeof(segment) + s->nbrBox*sizeof(struct box)
			+ s->nbrBox*sizeof(struct place));
}
/****************************************/
