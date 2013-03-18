#ifndef DTDPARSER_H
#define DTDPARSER_H

#include <string>

#include "DTDRoot.h"

using namespace std;


class DTDParser
{
public:
	static DTDRoot *loadFromFile(string filename);
	static DTDRoot *loadFromString(string xml);
};

#endif // DTDPARSER_H
