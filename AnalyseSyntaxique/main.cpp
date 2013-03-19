using namespace std;

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "modeldtd/DTDRoot.h"
#include "modeldtd/DTDDefinition.h"
#include "modeldtd/DTDElement.h"

#include "commun.h"


int main(int argc, char **argv) {
	int err;
	char *dtd;

//	xmldebug = 1; // Pour enlever l'affichage de l'exécution du parser XML, commenter cette ligne
//	dtddebug = 1; // Pour enlever l'affichage de l'exécution du parser DTD, commenter cette ligne

	if (argc != 2) {
		printf("usage: analyseur <fichier XML>\n");
		return 1;
	}

	xmlin = fopen(argv[1], "r");
	err = xmlparse(&dtd);
	fclose(xmlin);
	if (err != 0) printf("XML parse ended with %d error(s)\n", err);
	else  printf("XML parse ended with success\n", err);

    DTDRoot *dtdroot;
	dtdin = fopen(dtd, "r");
	err = dtdparse(&dtdroot);
	fclose(dtdin);
	if (err != 0) printf("DTD parse ended with %d error(s)\n", err);
	else  printf("DTD parse ended with success\n", err);

	dtdroot->enbref();
	delete dtdroot;
	return 0;
}
