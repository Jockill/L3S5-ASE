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
typedef struct segment
{
	int estOuvert;
	asem_t placesLibres;
	int nbrBox;
	asem_t box[];
}segment;
/****************************************/

/* Fonctions d'arret ********************/
void stopMe(char* msg);
void killMe(char* msg);
void closeMe(char* msg, int fdc, ...);
/****************************************/

#endif
