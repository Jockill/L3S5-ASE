#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_NOM_MAX 10

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

int main (int argc, char** argv)
{
	checkArgs(argc, argv);
}
