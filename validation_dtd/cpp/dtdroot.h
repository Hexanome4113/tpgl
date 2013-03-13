#ifndef DTDROOT_H
#define DTDROOT_H

using namespace std;

#include <vector>

typedef struct
{
	string elementName;
	vector<string> list;
} AttList;

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
