#include "DTDParser.h"
#include "DTDRoot.h"

#include "commun.h"

using namespace std;


DTDRoot *DTDParser::loadFromFile(string filename)
{
	dtdin = fopen(filename, "r");
	if (!dtdin)
	{
		return NULL;
	} else
	{
		DTDRoot *dtd;
		int err = dtdparse(dtd);
		if (err > 0) {
			return NULL;
		} else {
			return dtd;
		}
	}
}

DTDRoot DTDParser::loadFromString(string dtd)
{
	dtd_scan_buffer(dtd.c_str());

	DTDRoot *dtd;
	int err = dtdparse(dtd);
	if (err > 0) {
		return NULL;
	} else {
		return dtd;
	}
}
