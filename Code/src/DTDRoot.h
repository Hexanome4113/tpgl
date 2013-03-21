#ifndef DTDROOT_H
#define DTDROOT_H

using namespace std;

#include <vector>
#include <string>
#include "DTDElement.h"

struct DTDAttlist
{
	string elementName;
	vector<string> list;
};

class DTDRoot
{
	//METHODS
public:
	DTDRoot();
	DTDRoot(vector<DTDElement> elements, vector<DTDAttlist> attlists);
	
	const vector<DTDElement>& getElements();
	void addElement(DTDElement element);
	const vector<DTDAttlist>& getAttlists();
	void addAttlist(std::string nom, std::string attr);
	void enbref();
	string affiche();
	string attlistAffiche(DTDAttlist attlist);
	const DTDElement getElement(const string elementName);
	
protected:
	
	//ATTRIBUTES
	vector<DTDElement> elements;
	vector<DTDAttlist> attlists;
};

#endif // DTDROOT_H
