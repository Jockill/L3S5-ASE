#ifndef __SHM_H__
#define __SHM_H__

#include <stdlib.h>

/* Fonctions d'arret ********************/
void stopMe(char* msg);
void killMe(char* msg);
void closeMe(char* msg, int fdc, ...);
/****************************************/

#endif
