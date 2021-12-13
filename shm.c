#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
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
