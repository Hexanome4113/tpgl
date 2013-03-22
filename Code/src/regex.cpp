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
//cout << "+++ debut regex_match" << endl;
//cout << "+++ xml : " << str << endl;
//cout << "+++ dtd : " << regex << endl; 
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
//cout << "+++ fin regex_match" << endl;
    return (match_ok == 1);
}

bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
//cout << "++ debut test_regex " << xmlNode->getNodeName() << endl;
	const DTDElement *goodWay;
	goodWay = dtdRoot->getElement(xmlNode->getNodeName());
	if ( goodWay )
	{
		if (!(regex_match(xmlNode->regexSerialize(), goodWay->toRegex())))
		{
//cout << "++ faux regex" << endl;
//cout << "++ fin test_regex " << xmlNode->getNodeName() << endl;
			return false;
		}
	}
	else
	{
//cout << "++ goodWay null" << endl;
//cout << "++ fin test_regex " << xmlNode->getNodeName() << endl;
		return false;
	}
//cout << "++ test regex ok" << endl;
//cout << "++ fin test_regex " << xmlNode->getNodeName() << endl;
	return true;
}


bool match_xml_dtd (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
//cout << "+ debut match_xml_dtd " << xmlNode->getNodeName() << endl;
	if (!(test_regex (xmlNode, dtdRoot)))
	{
//cout << "+ test himself" << endl;
//cout << "+ fin match_xml_dtd " << xmlNode->getNodeName() << endl;
		return false;
	}
	
	/*
	//attributs du noeud xml
	if ( (xmlNode->getAttributes()).size() != 0 )
	{
cout << "there are attributes" << endl;
		for(std::map<string, string>::iterator it=xmlNode->getAttributes().begin() ; 
						it!=xmlNode->getAttributes().end() ;
						++it)
		{
			bool findAtt = false;
			for (std::list<string>::iterator itList = (dtdRoot->getAttList(xmlNode->getNodeName())).list.begin(); 
						itList!=(dtdRoot->getAttList(xmlNode->getNodeName())).list.end(); 
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
//cout << "+ nombre de fils de " << xmlNode->getNodeName() << ": " << (xmlNode->getChildren()).size() << endl;
	for (int i = 0; i < nbChildren; i++)
	{
		if (!((xmlNode->getChildren()).at(i)->isTextNode()))
		{
			if(!(match_xml_dtd((xmlNode->getChildren()).at(i), dtdRoot)))
			{
//cout << "+ test child " << i << endl;
//cout << "+ fin match_xml_dtd " << xmlNode->getNodeName() << endl;
			return false;
			}
		}
	}
//cout << "+ fin match_xml_dtd JUSTE : " << xmlNode->getNodeName() << endl;
	return true;
}
