using namespace std;

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "XMLNode.h"
#include "DTDRoot.h"
#include "DTDDefinition.h"
#include "DTDElement.h"
#include "commun.h"
#include "regex.h"

int main(int argc, char **argv) {
	int err;
	char *dtd;
	
	if (argc != 2) {
		printf("usage: analyseur <fichier XML>\n");
		return 1;
	}

	XMLNode *xmlRoot;
	xmlin = fopen(argv[1], "r");
	printf("%x", xmlin);
	err = xmlparse(&dtd, &xmlRoot);
	printf("Coucou !");
	fclose(xmlin);
	if (err != 0)
		printf("XML parse ended with %d error(s)\n", err);
	else printf("XML parse ended with success\n", err);
	
	DTDRoot *dtdroot;
	dtdin = fopen(dtd, "r");
	err = dtdparse(&dtdroot);
	fclose(dtdin);
	if (err != 0) printf("DTD parse ended with %d error(s)\n", err);
	else printf("DTD parse ended with success\n", err);
	
	//cout << xmlRoot->Affiche() << endl;
	bool match = match_xml_dtd (xmlRoot, dtdroot);
	cout << boolalpha << match << endl;
	delete dtdroot;
	return 0;
}
