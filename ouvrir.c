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
	shm_open(nom, O_RDWR, 0666);
	if (errno != ENOENT)
	{
		adebug(1, "Le centre n'est pas propre.\n");
		exit(1);
	}
}

void* createMmap(char* nom, size_t taille)
{

	int fd = shm_open(nom, O_RDWR|O_CREAT, 0666);
	CHECK(fd, "createMmap, shm_open");

	CHECK(ftruncate(fd, taille), "createMmap, ftruncate");

	void* map = mmap(NULL, taille, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		adebug(1, "createMmap, mmap\n");
		exit(1);
	}

	return map;
}

int main(int argc, char** argv)
{
	ainit(argv[0]);
	checkArgs(argc, argv);
	checkNettoyage(NOM_SHM);

	//Gestion des arguments
	int box = strtol(argv[1], NULL, 0);   //n
	int medecins = strtol(argv[2], NULL, 0); //m
	int tempsVax = strtol(argv[3], NULL, 0); //t

	//Initialiser les semaphores
	asem_t placesLibres;
	CHECK(asem_init(&placesLibres, "PLACES", 0, box), "main, asem_init");
	asem_t* asem_boxIN = (asem_t*)malloc(sizeof(asem_t) * box);
	asem_t* asem_boxOUT = (asem_t*)malloc(sizeof(asem_t) * box);
	for (int i=0; i<box; i++)
	{
		CHECK(asem_init(&asem_boxIN[i], "IN", 0, 0), "main, asem_init IN");
		CHECK(asem_init(&asem_boxOUT[i], "OUT", 0, 0), "main, asem_init OUT");
	}
	asem_t* cherchePlace;
	CHECK(asem_init(cherchePlace, "ChercheP", 0, 0), "main, asem_init CHP");
	asem_t* chercheBox;
	CHECK(asem_init(chercheBox, "ChercheB", 0, 0), "main, asem_init CHB");
	asem_t* medecinDispo;
	CHECK(asem_init(medecinDispo, "MedDispo", 0, 0));


	//Creer les objets
	int taille = sizeof(segment) + medecins*sizeof(struct box)
				+ box*sizeof(struct place);
	segment* seg = (segment*)createMmap(NOM_SHM, taille);
	struct box* boxs = (struct box*)(seg + 1);
	place* places = (place*)(boxs + box);

	//Initialiser segment
	seg->estOuvert = 1;
	seg->nbrBox = box;
	seg->nbrMedecins = medecins;
	seg->medecinsPresents = 0;
	seg->patientsPresents = 0;
	seg->tempsVax = tempsVax;
	seg->placesLibres = &placesLibres;
	seg->cherchePlace = &cherchePlace;
	seg->chercheBox = &chercheBox;
	seg->medecinDispo = &medecinDispo;
	seg->centreVide = &centreVide;

	//Initialiser boxs et places
	for (int i=0; i<box; i++)
	{
		boxs[i].libre = 1;
		boxs[i].numMedecin = i;
		boxs[i].numSiegePatient = -1;
		strncpy(boxs[i].nomPat, "VIDE", MAX_NOMSEM+1);
		boxs[i].vaxMoi = &asem_boxIN[i];
		boxs[i].vaxxed = &asem_boxOUT[i];
		/**/
		places[i].libre = 1;
		strncpy(places[i].nomPat, "VIDE", MAX_NOMSEM+1);
	}

	munmap(seg, mapSize(seg));

	return 0;
}
