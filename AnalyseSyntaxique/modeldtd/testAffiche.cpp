#include <iostream>
#include <string>
#include <vector>
#include "regex.h"
#include "DTDElement.h"
#include "DTDDefinition.h"
#include "DTDRoot.h"
#include "algo_validation.h"


using namespace std;

/*
<!ATTLIST ARTICLE EDITOR CDATA #IMPLIED>
<!ATTLIST ARTICLE DATE CDATA #IMPLIED>
<!ATTLIST ARTICLE EDITION CDATA #IMPLIED>
*/

int main()
{
	DTDElement elementVide;
	DTDRoot root;
	root.addElement(elementVide);
	root.addAttlist("ARTICLE", "EDITOR");
	root.addAttlist("ARTICLE", "DATE");
	root.addAttlist("ARTICLE", "EDITION");

	cout << root.affiche() << '\n';
	
	return 0;
}
