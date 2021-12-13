#include <stdlib.h>
#include "asem.h"
#include "shm.h"

int main (int argc, char** argv)
{
	if (argc > 1)
	{
		adebug(1, "Usage: %s", argv[0]);
		exit(1);
	}

	//if (sem != NULL)
	//		sem_destroy()

	//if (mem != NULL)
	//		mem_destroy()
	return 0;
}
