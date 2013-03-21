#include "DTDParser.h"
#include "DTDRoot.h"

#include "commun.h"

using namespace std;


DTDRoot *DTDParser::loadFromFile(string dtdFile)
{
	dtdin = fopen(dtdFile.c_str(), "r");
	if (!dtdin)
	{
		return NULL;
	} else
	{
		DTDRoot *dtd;
        string s;
		int err = dtdparse(&dtd, &s);

		fclose(dtdin);

		if (err > 0) {
			return NULL;
		} else {
			return dtd;
		}
	}
}

DTDRoot *DTDParser::loadFromString(string dtdString)
{
	DTD_BUFFER_STATE dtdbuf(dtd_scan_string(dtdString.c_str()));
	DTDRoot *dtd;
    string s;
	int err = dtdparse(&dtd, &s);

	dtd_delete_buffer(dtdbuf);

	if (err > 0) {
		return NULL;
	} else {
		return dtd;
	}
}

void DTDParser::destroy(DTDRoot *dtd) {
	delete dtd;
}
