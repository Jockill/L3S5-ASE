#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "asem.h"
#include "shm.h"


void checkArgs(int argc, char** argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <sieges> <medecins> <temps vax>\n", argv[0]);
        exit(1);
    }
	if (strtol(argv[1], NULL, 0) <= 0)
	{
		fprintf(stderr, "Le nombre de sieges ne peut être <= 0\n");
		exit(1);
	}
	if (strtol(argv[2], NULL, 0) <= 0)
	{
		fprintf(stderr, "Le nombre de médecins ne peut être <= 0\n");
		exit(1);
	}
	if (strtol(argv[3], NULL, 0) < 0)
	{
		fprintf(stderr, "Le temps d'une vaccination ne peut être < 0\n");
		exit(1);
	}
}

void checkNettoyage()
{
	// CHECK0(shm_open(segment));
/***********/
	printf("Centre propre, ouverture.\n");
/***********/
}

int main (int argc, char** argv)
{
    checkArgs(argc, argv);
	checkNettoyage();

	int sieges = strtol(argv[1], NULL, 0);
	int medecins = strtol(argv[2], NULL, 0);
	int tempsVax = strtol(argv[3], NULL, 0);


	//Creer semaphore "place_disponible" à sieges
	sem_t semPlaces;
	asem_t dispo = asem_init(&dispo, "PLACES", 0, sieges);
	//Creer un tableau de sieges semaphores "VIDE" à 1
	sem_t nbrSieges[sieges];
	asem_t aSieges[sieges]
	for (int i=0; i<sieges; i++)
		aSieges[i] = asem_init(aSieges[i], "VIDE", 0, 0);

	return 0;
}
