#include "DTDRoot.h"
#include "DTDParser.h"
#include "XMLNode.h"
#include "XMLParser.h"
#include "applyxslt.h"
#include "regex.h"

using namespace std;

#include <cstdlib> // pour exit();

#include <iostream>
#include <string>

DTDRoot *parsedtd(string dtdfile, bool restore) {
	DTDRoot *dtd(DTDParser::loadFromFile(dtdfile));

	if (dtd) {
		if (restore) {
			cout << dtd->affiche();
		}
		return dtd;
    } else {
        exit(102);
    }
}

pair<XMLNode *, string*> *parsexml(string xmlfile, bool restore) {
	pair<XMLNode *, string*> *p(XMLParser::loadFromFile(xmlfile));

	if (p) {
		if (p->first && restore) {
			cout << p->first->Affiche();
		}
		return p;
    } else {
        exit(102);
    }
}

void validate(pair<XMLNode *, string*> *pXml, DTDRoot *dtd) {
	bool match(match_xml_dtd(pXml->first, dtd));

	if (!match) {
		exit(103);
	}
}

void applyxslt(pair<XMLNode *, string*> *pXml, pair<XMLNode *, string*> *pXslt) {
	XMLNode* xmlTransfo(applyXSLT(pXml->first, pXslt->first));

	bool result = (xmlTransfo != NULL);
	if (result) {
		cout << xmlTransfo->Affiche();
	}

	if (!result) {
		exit(104);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		return 1;
	}

	if (string("parsedtd").compare(string(argv[1])) == 0)
	{
		if (argc < 4)
		{
			return 1;
		}
		bool restore = (string("restore").compare(string(argv[3])) == 0);
		DTDRoot *dtd(parsedtd(string(argv[2]), restore));
		DTDParser::destroy(dtd);
	}
	else if (string("validate").compare(string(argv[1])) == 0)
	{
		pair<XMLNode *, string*> *pXml(parsexml(string(argv[2]), false));
		DTDRoot *dtd(parsedtd(*(pXml->second), false));
		validate(pXml, dtd);
		XMLParser::destroy(pXml);
		DTDParser::destroy(dtd);
	}
	else if (string("applyxslt").compare(string(argv[1])) == 0)
	{
		if (argc < 4)
		{
			return 1;
		}
		pair<XMLNode *, string*> *pXml(parsexml(string(argv[2]), false));
		pair<XMLNode *, string*> *pXslt(parsexml(string(argv[3]), false));
		applyxslt(pXml, pXslt);
		XMLParser::destroy(pXml);
		XMLParser::destroy(pXslt);		
	}
	else if (string("parsexml").compare(string(argv[1])) == 0)
	{
		if (argc < 6)
		{
			return 1;
		}
		bool restore = (string("restore").compare(string(argv[3])) == 0);
		bool validateBool = (string("validate").compare(string(argv[4])) == 0);
		string xslt;
		if (argv[5][0] == 'a') {
			while (*(++argv[5]) != '=') {
				/* vide */
			}
			argv[5]++;
			xslt.assign(argv[5]);
		}

		pair<XMLNode *, string*> *pXml(parsexml(string(argv[2]), restore));
		if (validateBool) {
			DTDRoot *dtd(parsedtd(*(pXml->second), false));
			validate(pXml, dtd);
			DTDParser::destroy(dtd);
		}
		if (!xslt.empty()) {
			pair<XMLNode *, string*> *pXslt(parsexml(xslt, false));
			applyxslt(pXml, pXslt);
			XMLParser::destroy(pXslt);		
		}
		XMLParser::destroy(pXml);
	}
	else
	{
		return 2;
	}

	return 0;
}
