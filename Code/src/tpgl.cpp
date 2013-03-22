#include "DTDRoot.h"
#include "DTDParser.h"
#include "XMLNode.h"
#include "XMLParser.h"

void parsedtd(string xmlfile, bool restore) {
	DTDRoot *dtd(DTDParser::loadFromFile(xmlfile));

	if (dtd) {
		if (restore) {
			dtd->affiche();
		}
		DTDParser::destroy(dtd);
	}
}

void parsexml(string xmlfile, bool restore) {
	pair<XMLNode *, string*> *p(XMLParser::loadFromFile(xmlfile));

	if (p) {
		if (p->first && restore) {
			p->first->Affiche();
		}
		XMLParser::destroy(p);
	}
}

void validate(string xmlfile) {
	
//	bool match = match_xml_dtd(xmlRoot, dtdroot);
}

void applyxslt(string xmlfile, string xsltfile) {
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
