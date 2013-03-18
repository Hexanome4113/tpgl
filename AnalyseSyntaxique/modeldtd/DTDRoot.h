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
	DTDRoot(vector<DTDElement> elements, vector<DTDAttlist> attlists);
	
	const vector<DTDElement>& getElements();
	const vector<DTDAttlist>& getAttlists();
	
protected:
	
	//ATTRIBUTES
	vector<DTDElement> elements;
	vector<DTDAttlist> attlists;
};

#endif // DTDROOT_H
