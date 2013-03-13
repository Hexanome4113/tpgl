using namespace std;

#include <cstdio>
#include <cstdlib>

#include "commun.h"


int main(int argc, char **argv) {
	int err;

	xmldebug = 1; // Pour enlever l'affichage de l'exécution du parser XML, commenter cette ligne
	dtddebug = 1; // Pour enlever l'affichage de l'exécution du parser DTD, commenter cette ligne

	err = xmlparse();
	if (err != 0) printf("Parse ended with %d error(s)\n", err);
	else  printf("Parse ended with success\n", err);

	return 0;
}
