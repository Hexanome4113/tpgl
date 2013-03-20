#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "DTDRoot.h"
#include "DTDElement.h"

using namespace std;

/*
<!ELEMENT rapport (titre, auteur+, resume, chapitre+)>
<!ELEMENT auteur (prenom, nom)>
<!ELEMENT nom (#PCDATA)>
<!ELEMENT prenom (#PCDATA)>
<!ELEMENT resume (#PCDATA)>
<!ELEMENT chapitre (titre, (p | section)+)>
<!ELEMENT section (titre, p+)>
<!ELEMENT p (#PCDATA)>
<!ELEMENT titre (#PCDATA)>
* 
<!ATTLIST rapport editor CDATA #IMPLIED>
<!ATTLIST rapport date CDATA #IMPLIED>
<!ATTLIST rapport edition CDATA #IMPLIED>
*/

int main()
{
	DTDElement elementVide;
	DTDRoot dtdroot;
	dtdroot.addElement(elementVide);
	dtdroot.addAttlist("rapport", "editor");
	dtdroot.addAttlist("rapport", "date");
	dtdroot.addAttlist("rapport", "edition");

	cout << dtdroot.affiche() << '\n';
	
	return 0;
}
