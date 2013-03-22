#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>

#include "XMLNode.h"

using namespace std;


class XMLParser
{
public:
	static pair<XMLNode *, string *> *loadFromFile(string xmlFile);
	static pair<XMLNode *, string *> *loadFromString(string xmlString);
	static void destroy(pair<XMLNode *, string *> *p);
};

#endif // XMLPARSER_H
