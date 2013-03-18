#include "DTDRoot.h"

#include <sstream> 

#include <vector>
#include "DTDElement.h"

#define SPACE " "
#define CBALISE ">"
#define EOL '\n'

#define ATTLIST_OBALISE "<!ATTLIST"
#define ATTLIST_OPTIONS "CDATA #IMPLIED"



using namespace std;

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

