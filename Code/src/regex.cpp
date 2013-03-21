#include <iostream>
#include <string>
#include <pcre.h>
#include "regex.h"

using namespace std;

bool regex_match(const string str, const string regex)
{
    // pcre_compile :
    const char *err;
    int errOffset;
    pcre *re = pcre_compile(regex.c_str(), PCRE_MULTILINE, &err, &errOffset, 0);
    if (!re)
    {
        cout << "pcre_compile failed (offset: " << errOffset << "), " << err << endl;
        return false;
    }

    // pcre_exec :
    int ovector[100];
    unsigned int len = str.length();
    int match_ok = pcre_exec(re, 0, str.c_str(), len, 0, 0, ovector, 100);
    return (match_ok == 1);
}

bool match_xml_dtd (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
	bool match = true;
	int nbChildren = (xmlNode->getChildren()).size();
	for (int i = 0; i < nbChildren; i++)
	{
		if ( (((xmlNode->getChildren()).at(i))->getChildren()).size() == 0)
		{
			if(!(match_xml_dtd((xmlNode->getChildren()).at(i), dtdRoot)))
			{
				match = false;
			}
		}
		else
		{
			DTDElement goodWay;
			goodWay = dtdRoot->getElement(xmlNode->getNodeName());
			if ( goodWay != null )
			{
				if (!(regex_match(xmlNode->regexSerialize(), goodWay->toRegex())))
				{
					match = false;
				}
			}
			else
			{
				match = false;
			}
		}
	}
	return match;
}