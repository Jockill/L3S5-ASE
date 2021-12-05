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


/* Fonctions d'arret ********************/
void stopMe(char* msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void killMe(char* msg)
{
	perror(msg);
	exit(1);
}

void closeMe(char* msg, int fdc, ...)
{
	va_list fdv;
	va_start(fdv, fdc);

	perror(msg);
	for (int i=0; i<fdc; i++)
		close(va_arg(fdv, int));
	exit(1);
}
/****************************************/
