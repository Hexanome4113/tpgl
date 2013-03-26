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

const vector<DTDElement>& DTDRoot::getElements() const
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

const vector<DTDAttlist>& DTDRoot::getAttlists() const
{
	return attlists;
}

std::string DTDRoot::affiche() const
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

string DTDRoot::attlistAffiche(DTDAttlist attlist) const
{
	string result = "";
	for (int i = 0; i < attlist.list.size(); i++)
	{
		result = result + ATTLIST_OBALISE + SPACE + attlist.elementName + SPACE + attlist.list.at(i) + SPACE + ATTLIST_OPTIONS + CBALISE + EOL;
	}

	return result;
}

const DTDElement* DTDRoot::getElement(const string elementNom) const
{
	for (int i = 0; i < getElements().size(); i++)
	{
		if ( getElements().at(i).getNom().compare(elementNom) == 0 )
		{
			return &(getElements().at(i));
		}
	}
	return NULL;
}

const DTDAttlist* DTDRoot::getAttList(const string elementName) const
{
	for (int i = 0; i < getAttlists().size(); i++)
	{
		if ( getAttlists().at(i).elementName.compare(elementName) == 0 )
		{
			return &(getAttlists().at(i));
		}
	}
	return NULL;
}
