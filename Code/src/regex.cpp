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
			cout << "file XML doesn't match his DTD : " << "the element "<< xmlNode->getNodeName() << "doesn't match his DTD rule" << endl;
			return false;
		}
		//attributs du noeud xml
		if ( (xmlNode->getAttributes()).size() != 0 )
		{
			std::map<string, string> mapAtt = xmlNode->getAttributes();

			for(map<string, string>::iterator it=mapAtt.begin(); 
							it!=mapAtt.end();
							++it)
			{
				bool findAtt = false;
				if (dtdRoot->getAttList(xmlNode->getNodeName()))
				{
					vector<string> dtdListAtt = (dtdRoot->getAttList(xmlNode->getNodeName()))->list;
					for (vector<string>::iterator itList = dtdListAtt.begin(); 
								itList!=dtdListAtt.end(); 
								++itList)
					{
						if (itList->compare(it->first) == 0)
						{
							findAtt = true;
						}
					}
					if (!findAtt)
					{
						cout << "file XML doesn't match his DTD : " << "the element "<< xmlNode->getNodeName() << " doesn't have a DTD rule for the attribute " << it->first << endl;
						return false;
					}	
				}
				else
				{
					cout << "file XML doesn't match his DTD : " << "the element "<< xmlNode->getNodeName() << " doesn't have any attribute in his DTD rule" << endl;
					return false;
				}
			}
		}
	}
	else
	{
		cout << "file XML doesn't match his DTD : " << "the element "<< xmlNode->getNodeName() << " doesn't have a DTD rule" << endl;
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
