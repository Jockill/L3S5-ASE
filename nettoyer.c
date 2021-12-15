#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "asem.h"
#include "shm.h"

int main (int argc, char** argv)
{
	ainit(argv[0]);
	if (argc > 1)
	{
		adebug(1, "Usage: %s", argv[0]);
		exit(1);
	}

	segment* seg = (segment*)getSegment(NOM_SHM);
	struct box* boxs = (struct box*)(seg + sizeof(segment));

	//Destruction des objets
	for (int i=0; i<seg->nbrBox; i++)
	{
		CHECK(asem_destroy(boxs[i]->vaxMoi), "destroy vaxMoi");
		CHECK(asem_destroy(boxs[i]->vaxxed), "destroy vaxxed");
	}

	CHECK(asem_destroy(seg->placesLibres), "destroy placesLibres");
	CHECK(asem_destroy(seg->cherchePlace), "destroy cherchePlace");
	CHECK(asem_destroy(seg->chercheBox), "destroy chercheBox");
	CHECK(asem_destroy(seg->medecinDispo), "destroy medecinDispo");
	CHECK(asem_destroy(seg->centreVide), "destroy centreVide");

	munmap(seg, sizeof(&seg));
	shm_unlink(NOM_SHM);

	return 0;
}
