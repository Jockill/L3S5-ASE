#include <stdlib.h>

int main (int argc, char** argv)
{
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s", argv[0]);
		exit(1);
	}

	//Bloquer l'acces en écriture à la mémoire partagée
	//exec('./nettoyer');
}
