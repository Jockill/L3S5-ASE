#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "asem.h"
#include "shm.h"

int main (int argc, char** argv)
{
	if (argc > 1)
	{
		adebug(1, "Usage: %s", argv[0]);
		exit(1);
	}

	int fd = shm_open(NOM_SHM, O_RDWR, 0666);
	CHECK(fd, "shm_open");

	//seg->estOuvert = 0;
	//wait while (seg->placesLibres > 0)
	//munmap(NOM_SHM)

	CHECK(shm_unlink(NOM_SHM), "shm_unlink");
	return 0;
}
