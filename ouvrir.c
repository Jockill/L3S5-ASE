#include <errno.h>
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
        adebug(1, "Usage: %s <sieges> <medecins> <temps vax>\n", argv[0]);
        exit(1);
    }
	if (strtol(argv[1], NULL, 0) <= 0)
	{
		adebug(1, "Le nombre de sieges ne peut être <= 0\n");
		exit(1);
	}
	if (strtol(argv[2], NULL, 0) <= 0)
	{
		adebug(1, "Le nombre de médecins ne peut être <= 0\n");
		exit(1);
	}
	if (strtol(argv[3], NULL, 0) < 0)
	{
		adebug(1, "Le temps d'une vaccination ne peut être < 0\n");
		exit(1);
	}
}

void checkNettoyage(char* nom)
{
	shm_open(nom);
	if (errno != ENOENT)
	{
		adebug(1, "Le centre n'est pas propre.\n");
		exit(1);
	}
}

void* createMmap(char* nom)
{
	int fd = shm_open(nom, O_RDWR|O_CREAT, 0666);
	CHECK(fd, "createMmap, shm_open");

	CHECK(ftruncate(fd, sizeof(test)), "createMmap, ftruncate");

	void* map = mmap(NULL, sizeof(test), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		fprintf(stderr, "mmap\n");
		exit(1);
	}

	return map;
}

int main(int argc, char** argv)
{
	checkArgs(argc, argv);
	checkNettoyage(NOM_SHM);

	//Gestion des arguments
	int sieges = strtol(argv[1], NULL, 0);   //n
	int medecins = strtol(argv[2], NULL, 0); //m
	int tempsVax = strtol(argv[3], NULL, 0); //t


	//Creer semaphore "placesLibres" à sieges
	sem_t places;
	asem_t placesLibres;
	placesLibres->sem = places;
	placesLibres = asem_init(&placesLibres, "PLACES", 0, sieges);
	//Creer un tableau de sieges semaphores "VIDE" à 1
	sem_t* sem_box = (sem_t*)malloc(sizeof(sem_t) * sieges);
	asem_t* asem_box = (asem_t*)malloc(sizeof(asem_t) * sieges);
	for (int i=0; i<sieges; i++)
	{
		asem_box[i]->sem = *sem_box[i];
		asem_box[i] = asem_init(asem_box[i], "VIDE", 0, 1);
	}

	//Creer le segment partagé...
	void* map = createMmap(NOM_SHM);
	//... et le remplir
	segment* segment = (segment*)map;
	segment->estOuvert = 1;
	segment->placesLibres = placesLibres;
	segment->nbrSieges = sieges;
	segment->sieges = *asem_sieges;

	//Detruire le segment partagé
	CHECK(shm_unlink(NOM_SHM), "shm_unlink");

	return 0;
}
