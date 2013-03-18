#include "dtdroot.h"

DTDRoot::DTDRoot(vector<DTDElement> elements, vector<DTDAttlist> attlists)
:elements(elements),
attlists(attlists)
{
}

const vector<DTDElement>& DTDRoot::getElements()
{
	return elements;
}

const vector<DTDAttlist>& DTDRoot::getAttlists()
{
	return attlists;
}