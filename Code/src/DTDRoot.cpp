#include "DTDRoot.h"

#include <iostream>
#include <sstream> 
#include <vector>
#include <string>

#include "DTDElement.h"

#define SPACE " "
#define CBALISE ">"
#define EOL '\n'

#define ELEMENT_OBALISE "<!ELEMENT"

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

vector<DTDElement>& DTDRoot::getElements()
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

vector<DTDAttlist>& DTDRoot::getAttlists()
{
	return attlists;
}

std::string DTDRoot::affiche()
{
	std::string buffer;
 
	//write all elements
	for (int i = 0; i < elements.size(); i++)
	{
		buffer += elements.at(i).affiche();
		buffer += EOL;
	}

	//write all attributes
	for (int i = 0; i < attlists.size(); i++)
	{
		buffer += attlistAffiche(attlists.at(i));
	}

	return buffer;

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
		cout << ELEMENT_OBALISE << SPACE
			<< elements[i].getNom() << SPACE
			<< elements[i].toRegex()
			<< CBALISE << endl;
	}

	cout << "==== ATTLISTS ====" << endl;
	for (int i = 0; i < attlists.size(); i++) {
		cout << attlistAffiche(attlists[i]) << endl;
	}

}

DTDElement DTDRoot::getElement(string elementName)
{
	for (int i = 0; i < getElements().size(); i++)
	{
		if ( getElements().at(i).getNom().compare(elementName) == 0 )
		{
			return getElements().at(i);
		}
	}
	throw 666;
}
