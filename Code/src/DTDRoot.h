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
	
<<<<<<< HEAD
	const vector<DTDElement>& getElements() const;
	void addElement(DTDElement element);
	const vector<DTDAttlist>& getAttlists() const;
	void addAttlist(std::string nom, std::string attr);
	void enbref() const;
	string affiche() const;
	string attlistAffiche(DTDAttlist attlist) const;
	const DTDElement* getElement(const string elementName) const;
	const DTDAttlist* getAttList(const string elementName) const;
=======
	vector<DTDElement>& getElements();
	void addElement(DTDElement element);
	vector<DTDAttlist>& getAttlists();
	void addAttlist(std::string nom, std::string attr);
	void enbref();
	string affiche();
	string attlistAffiche(DTDAttlist attlist);
	DTDElement getElement(string elementName);
>>>>>>> 8581df3982f8d6104b7bb471a8e49b4bf8e9787f
	
protected:
	
	//ATTRIBUTES
	vector<DTDElement> elements;
	vector<DTDAttlist> attlists;
};

#endif // DTDROOT_H
