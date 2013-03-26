#include <iostream>
#include <string>
#include <pcre.h>
#include <map>
#include <list>
#include <string>
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

bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
	const DTDElement *goodWay;
	goodWay = dtdRoot->getElement(xmlNode->getNodeName());
	if ( goodWay )
	{
		if (!(regex_match(xmlNode->regexSerialize(), goodWay->toRegex())))
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}


bool match_xml_dtd (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
	if (!(test_regex (xmlNode, dtdRoot)))
	{
		return false;
	}
	/*
	//attributs du noeud xml
	if ( (xmlNode->getAttributes()).size() != 0 )
	{
cout << "there are attributes" << endl;
		for(map<string, string>::iterator it=xmlNode->getAttributes().begin() ; 
						it!=xmlNode->getAttributes().end() ;
						++it)
		{
			bool findAtt = false;
			for (list<string>::iterator itList = ((dtdRoot->getAttList(xmlNode->getNodeName()))->list).begin(); 
						itList!=((dtdRoot->getAttList(xmlNode->getNodeName()))->list).end(); 
						++itList)
			{
				if (itList->compare(it->first) == 0)
				{
cout << "find attribute" << endl;
					findAtt = true;
				}
			}
			if (!findAtt)
			{
cout << "not find attribute" << endl;
				return false;
			}
		}
	}
	*/
	
	int nbChildren = (xmlNode->getChildren()).size();
	for (int i = 0; i < nbChildren; i++)
	{
		if (!((xmlNode->getChildren()).at(i)->isTextNode()))
		{
			if(!(match_xml_dtd((xmlNode->getChildren()).at(i), dtdRoot)))
			{
			return false;
			}
		}
	}
	return true;
}
