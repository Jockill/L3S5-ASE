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

	int fd = shm_open("/segment", O_RDWR, 0666);
	CHECK(fd, "shm_open");

	

	CHECK(smh_unlink("/segment"), "shm_unlink");
	return 0;
}
