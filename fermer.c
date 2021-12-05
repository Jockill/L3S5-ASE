#include <stdlib.h>
#include "asem.h"
#include "shm.h"

int main (int argc, char** argv)
{
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s", argv[0]);
		exit(1);
	}

	//Lire segment
	//segment.estOuvert = 0;

	return 0;
}
