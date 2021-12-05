#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asem.h"
#include "shm.h"

#define MAX_NOMPAT 10+1
#define EXIT_VAX_FERME 2

void checkArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <nom>\n", argv[0]);
		exit(1);
	}
	if (strlen(argv[1]) > TAILLE_NOM_MAX || strlen(argv[1]) == 0)
	{
		fprintf(stderr, "Le nom du patient a une taille comprise entre 0 et 10\
\	\	\	\	\	\	caracteres\n");
		exit(1);
	}
}

void inscription(char* nom, /*segment*/)
{
	int i=0
	for (; i<segment.nbrSieges; i++)
	{
		//On sait qu'il y a au moins un siege de libre grace au semaphore
		if (strncmp(segement.sieges[i].nom, "VIDE", MAX_NOMPAT) == 0)
		//OU asem_init()
			break;
	}
	strncpy(segment.sieges[i].nom, nom, MAX_NOMPAT);
	//OU asem_init()
}

int main (int argc, char** argv)
{
	checkArgs(argc, argv);

	int assis = 0;
	int vax = 0;
	//Lire segment

	if (segment.estOuvert == 0)
	{
		fprintf(stderr, "Le vaccinodrome est fermé.\n");
		exit(EXIT_VAX_FERME);
	}

	while (assis == 0)
	{
		//wait("place_disponible")
		//P("place_disponible")
		assis = 1;
	}
		//inscription(nom, segment)
	while (vax == 0)
	{
		//wait("vax")
		//P("vax")
		vax = 1;
	}
		//depart(segment)
		//V("place_disponible")
		//V("vax")

	return 0;
}
