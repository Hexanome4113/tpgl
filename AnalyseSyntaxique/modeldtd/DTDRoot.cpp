#include "DTDRoot.h"

#include <sstream> 
#include <vector>
#include <string>
#include <iostream>
#include "DTDElement.h"
#include "algo_validation.h"

#define SPACE " "
#define CBALISE ">"
#define EOL '\n'

#define ATTLIST_OBALISE "<!ATTLIST"
#define ATTLIST_OPTIONS "CDATA #IMPLIED"



using namespace std;

DTDRoot::DTDRoot()
{
}

DTDRoot::DTDRoot(vector<DTDElement> elements, vector<DTDAttlist> attlists)
:elements(elements),
attlists(attlists)
{
}

const vector<DTDElement>& DTDRoot::getElements()
{
	return elements;
}

void DTDRoot::addElement(DTDElement element)
{
	elements.push_back(element);
}

void DTDRoot::addAttlist(string nom, string attr)
{
	bool found = false;
	for (int i=0 ; i < attlists.size() ; i++) {
		if (attlists[i].elementName == nom) {
			attlists[i].list.push_back(attr);
			found = true;
			break;
		}
	}
	if (not found) {
		DTDAttlist attlist;
		attlist.elementName = nom;
		attlist.list.push_back(attr);
		attlists.push_back(attlist);
	}
}

const vector<DTDAttlist>& DTDRoot::getAttlists()
{
	return attlists;
}

string DTDRoot::affiche()
{
	std::ostringstream buffer (std::ostringstream::ate); //add at the end of the buffer
 /*
	//write all elements
	for (int i = 0; i < elements.size(); i++)
	{
		buffer << elements.at(i).affiche();
		buffer << '\n';
	}
*/
	//write all attributes
	for (int i = 0; i < attlists.size(); i++)
	{
		buffer << attlistAffiche(attlists.at(i));
	}

	return buffer.str();

}

string DTDRoot::attlistAffiche(DTDAttlist attlist)
{
	string result = "";
	for (int i = 0; i < attlist.list.size(); i++)
	{
		result = result + ATTLIST_OBALISE + SPACE + attlist.elementName + SPACE + attlist.list.at(i) + SPACE + ATTLIST_OPTIONS + CBALISE + EOL;
	}

	return result;
}

void DTDRoot::enbref()
{
	cout << "==== ELEMENTS ====" << endl;
	for (int i = 0; i < elements.size(); i++) {
		cout << "<!ELEMENT "
			<< elements[i].getNom() << " "
			<< dtdToRegex(elements[i]) << " "
			<< elements[i].getContentSpec()
			<< ">" << endl;
	}

	cout << "==== ATTLISTS ====" << endl;
	for (int i = 0; i < attlists.size(); i++) {
		cout << attlistAffiche(attlists[i]) << endl;
	}

}
