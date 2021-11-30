#include <stdio.h>
#include <stdlib.h>
#include <semaphores.h>
#include <pthread.h>

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

int main (int argc, char** argv)
{
    checkArgs(argc, argv);

	//Sémaphores
	//if (sem != NULL)
	//		Err
	//sem_init()

	//Mémoire partagée
	//if (mem != NULL)
	//		Err
	//mem_init()
}
