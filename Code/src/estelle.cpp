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
	err = xmlparse(&dtd, &xmlRoot);
	fclose(xmlin);
	if (err != 0)
		printf("XML parse ended with %d error(s)\n", err);
	else printf("XML parse ended with success\n", err);
	
	DTDRoot *dtdroot;
	dtdin = fopen(dtd, "r");
	err = dtdparse(&dtdroot, new string() );
	fclose(dtdin);
	if (err != 0) printf("DTD parse ended with %d error(s)\n", err);
	else printf("DTD parse ended with success\n", err);
	
	bool match = match_xml_dtd (xmlRoot, dtdroot);
	if (match)
		cout << "file XML matches his DTD" << endl;
	else cout << "file XML doesn't match his DTD" << endl;
	delete dtdroot;
	return 0;
}
