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

//	dtddebug = 1; // Pour enlever l'affichage de l'exécution du parser DTD, commenter cette ligne

    DTDRoot *dtdroot;
	dtdin = fopen(argv[1], "r");
	err = dtdparse(&dtdroot);
	fclose(dtdin);
	if (err != 0) printf("DTD parse ended with %d error(s)\n", err);
	else  printf("DTD parse ended with success\n", err);
	
	cout << dtdroot->affiche() << endl;
	
	delete dtdroot;
	return 0;
}
