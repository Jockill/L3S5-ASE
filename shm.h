#ifndef __SHM_H__
#define __SHM_H__

#include <stdarg.h>
#include <stdlib.h>

#define NOM_SHM "/vaxx"

/* Macros pours les retour de fonctions */
#define TEST(exp, msg) \
do { \
	if ((exp)==-1){ stopMe(#msg); } \
} while (0)

#define CHECK(exp, msg) \
do { \
    if((exp)==-1){ killMe(#msg); } \
} while (0)

#define CHECK0(exp, msg) \
do { \
    if((exp) >0){ killMe(#msg); } \
} while (0)

#define CHECKLOSE(exp, msg, fdn, ...) \
do { \
    if((exp) >0){ closeMe(#msg, fdn, __VA_ARGS__); } \
} while (0)
/****************************************/


/* Structures ***************************/
typedef struct place
{
	int libre;
	char nomPat[MAX_NOMSEM+1];
}place;

typedef struct box
{
	int libre;
	int numMedecin;
	int numSiegePatient;
	char nomPat[MAX_NOMSEM+1];
	asem_t* vaxMoi; //Entrée dans le box
	asem_t* vaxxed; //Sortie du box
}box;

typedef struct segment
{
	int estOuvert;
	int nbrBox;
	int nbrMedecins;
	int medecinsPresents;
	int patientsPresents;
	int tempsVax;
	asem_t* placesLibres;
	asem_t* cherchePlace;
	asem_t* chercheBox;
	asem_t* medecinDispo;
	asem_t* centreVide;
}segment;
/****************************************/

/* Fonctions d'arret ********************/
void stopMe(char* msg);
void killMe(char* msg);
void closeMe(char* msg, int fdc, ...);
/****************************************/

/* Gestion map **************************/
void* getSegment(char* nom);
size_t mapSize(segment* s);
/****************************************/


#endif
