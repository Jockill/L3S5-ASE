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

#define MAX_NOMPAT 10+1

void checkArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		adebug(1, "Usage: %s <nom>\n", argv[0]);
		exit(1);
	}
	if (strlen(argv[1]) > MAX_NOMPAT || strlen(argv[1]) == 0)
	{
		adebug(1, "Le nom du patient doit avoir une taille comprise entre 0 \
et 10 caracteres\n");
		exit(1);
	}
}

int inscription(char* nom, segment* seg, place* places)
{
	int i=0;
	asem_wait(seg->cherchePlace);
	for (; i<seg->nbrBox; i++) //nbrBox <=> nbrSieges
	{
		if (places[i].libre == 1)
		{
			places[i].libre = 0;
			break;
		}
	}
	asem_post(seg->cherchePlace);
	strncpy(places[i].nomPat, nom, MAX_NOMPAT);

	printf("patient %s siege %d\n", nom, i);
	fflush(stdout);

	return i;
}

int chercheBox(segment* seg, box* boxs)
{
	int i = 0;
	asem_wait(seg->chercheBox);
	for (; i<seg->nbrMedecins; i++)
	{
		if (boxs[i].libre == 1)
		{
			boxs[i].libre = 0;
			break;
		}
		return -1;
	}
	asem_post(seg->chercheBox);
	return i;
}

int getVaxxed(char* nom, segment* seg, box box)
{
	asem_post(box.vaxMoi);
	asem_wait(box.vaxxed);
	printf("patient %s medecin %d\n", nom, i);
	fflush(stdout);

	box.libre = 1;
}

int main (int argc, char** argv)
{
	ainit(argv[0]);
	checkArgs(argc, argv);

	//Lire segment
	segment* seg = (segment*)getSegment(NOM_SHM);
	struct box* boxs = (struct box*)(seg + 1);
	place* places = (place*)(boxs + seg->nbrBox);
	int numPlace;
	int numBox;

	CHECK0((seg->estOuvert == 0), "Vaccinodrome fermé");

	//Attendre de la place
	asem_wait(seg->placesLibres);
	//Entrée et inscription
	(seg->patientsPresents)++;
	numPlace = inscription(argv[1], seg, places);
	//Attendre un médecin
	asem_wait(seg->medecinDispo);
	//Trouver un box
	numBox = chercheBox(seg, boxs);
	//Libérer la place
	places[numPlace].libre = 1;
	strncpy(places[numPlace].nomPat, "VIDE", MAX_NOMSEM+1);
	asem_post(seg->placesLibres);
	//Se faire vacciner
	getVaxxed(argv[1], seg, boxs[numBox]);
	//Sortie
	(seg->patientsPresents)--;

	return 0;
}
