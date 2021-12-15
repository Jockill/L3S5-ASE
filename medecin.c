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
	struct box* boxs = (struct box*)(seg + 1);

	int num = seg->medecinsPresents;

	//S'enregistrer
	(seg->medecinsPresents)++;
	asem_post(seg->medecinDispo);

	//Mauvaise condition, a remplacer par un semaphore
	while (seg->estOuvert && seg->patientsPresents > 0)
	{
		asem_wait(boxs[num].vaxMoi);
		asem_wait(seg->medecinDispo);
		sleep(seg->tempsVax);
		printf("medecin %d vaccine %s\n", num, boxs[num].nomPat);
		fflush(stdout);
		asem_post(boxs[num].vaxxed);
		asem_post(seg->medecinDispo);
	}

	//Partir
	(seg->medecinsPresents)--;
	asem_wait(seg->MedDispo);
	if (seg->medecinsPresents == 0)
		//Debloquer fermer pour finir la fermeture
		asem_post(seg->centreVide);

	munmap(seg, mapSize(seg));
	return 0;
}
