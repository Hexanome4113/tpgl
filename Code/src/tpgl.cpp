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

void parsedtd(string dtdfile, bool restore) {
	DTDRoot *dtd(DTDParser::loadFromFile(dtdfile));

	if (dtd) {
		if (restore) {
			cout << dtd->affiche() << endl;
		}
		DTDParser::destroy(dtd);
    } else {
        exit(102);
    }
}

void parsexml(string xmlfile, bool restore) {
	pair<XMLNode *, string*> *p(XMLParser::loadFromFile(xmlfile));

	if (p) {
		if (p->first && restore) {
			cout << p->first->Affiche() << endl;
		}
		XMLParser::destroy(p);
    } else {
        exit(102);
    }
}

void validate(string xmlfile) {
	pair<XMLNode *, string*> *p(XMLParser::loadFromFile(xmlfile));

	if (!p) {
		exit(102);
    }

	DTDRoot *dtd(DTDParser::loadFromFile(*(p->second)));

	if (!dtd) {
		XMLParser::destroy(p);
		exit(102);
    }

	bool match(match_xml_dtd(p->first, dtd));

	XMLParser::destroy(p);
	DTDParser::destroy(dtd);

	if (!match) {
		exit(103);
	}
}

void applyxslt(string xmlfile, string xsltfile) {
	pair<XMLNode *, string*> *pXml(XMLParser::loadFromFile(xmlfile));

	if (!pXml) {
		exit(102);
    }

	pair<XMLNode *, string*> *pXslt(XMLParser::loadFromFile(xsltfile));
	if (!pXml) {
		XMLParser::destroy(pXml);
		exit(102);
    }

	XMLNode* xmlTransfo(applyXSLT(pXml->first, pXslt->first));

	bool result = (xmlTransfo != NULL);
	if (result) {
		cout << xmlTransfo->Affiche() << endl;
	}

	XMLParser::destroy(pXml);
	XMLParser::destroy(pXslt);

	if (!result) {
		exit(104);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		return 1;
	}

	if (string("parsedtd").compare(string(argv[1])) == 0)
	{
		bool restore = (string("restore").compare(string(argv[3])) == 0);
		parsedtd(string(argv[2]), restore);
	}
	else if (string("validate").compare(string(argv[1])) == 0)
	{
		validate(string(argv[2]));
	}
	else if (string("applyxslt").compare(string(argv[1])) == 0)
	{
		applyxslt(string(argv[2]), string(argv[3]));
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

		parsexml(string(argv[2]), restore);
		if (validateBool) {
			validate(string(argv[2]));
		}
		if (!xslt.empty()) {
			applyxslt(string(argv[2]), xslt);
		}
	}
	else
	{
		return 2;
	}

	return 0;
}
