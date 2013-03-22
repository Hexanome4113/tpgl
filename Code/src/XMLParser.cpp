#include "XMLParser.h"
#include "XMLNode.h"

#include "commun.h"

#include <cstdio>
#include <cstdlib>
#include <utility>

using namespace std;


pair<XMLNode *, string *> *XMLParser::loadFromFile(string xmlFile)
{
	xmlin = fopen(xmlFile.c_str(), "r");
	if (!xmlin)
	{
		return NULL;
	} else
	{
		char *dtd;
		XMLNode *xml;

		int err = xmlparse(&dtd, &xml);

		fclose(xmlin);

		if (err > 0) {
			return NULL;
		} else {
			string *s = new string(dtd);
			free(dtd);
			return new pair<XMLNode *, string *>(xml, s);
		}
	}
}

pair<XMLNode *, string *> *XMLParser::loadFromString(string xmlString)
{
	XML_BUFFER_STATE xmlbuf(xml_scan_string(xmlString.c_str()));
	char *dtd;
	XMLNode *xml;
	int err = xmlparse(&dtd, &xml);

	xml_delete_buffer(xmlbuf);

	if (err > 0) {
		return NULL;
	} else {
		string *s = new string(dtd);
		free(dtd);
		return new pair<XMLNode *, string *>(xml, s);
	}
}

void XMLParser::destroy(pair<XMLNode *, string *> *p)
{
	if (p)
	{
		if (p->first) delete p->first;
		if (p->second) delete p->second;
		delete p;
	}
}
