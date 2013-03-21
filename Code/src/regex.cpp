#include <iostream>
#include <string>
#include <pcre.h>
#include "regex.h"

using namespace std;

bool regex_match(const string str, const string regex)
{
cout << "xml : " << str << endl;
cout << "dtd : " << regex << endl; 
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
cout << "bouh" << endl;
    int match_ok = pcre_exec(re, 0, str.c_str(), len, 0, 0, ovector, 100);
cout << "fin regexmatch" << endl;
    return (match_ok == 1);
}

<<<<<<< HEAD
bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
	const DTDElement *goodWay;
	goodWay = dtdRoot->getElement(xmlNode->getNodeName());
cout << goodWay->getNom() << " goodWay name" << endl;
	if ( goodWay )
	{
		if (!(regex_match(xmlNode->regexSerialize(), goodWay->toRegex())))
		{
cout << "faux regex" << endl;
			return false;
		}
	}
	else
	{
cout << "goodWay null" << endl;
		return false;
	}
cout << "test regex ok" << endl;
	return true;

/*
				//attributs du noeud xml
				if ( (xmlNode->getAttributes()).size() != 0 )
				{
					for(xmlNode->getAttributes()::iterator it=xmlNode->getAttributes().begin() ; it!=xmlNode->getAttributes().end() ; ++it)
					{
						bool findAtt = false;
						for (std::list<string>::iterator itList = dtdRoot->getAttlist(xmlNode->getNodeName())->list.begin(); itList != dtdRoot->getAttlist(xmlNode->getNodeName())->list.end(); itList++)
						{
							if (*itList.compare(it->first) == 0)
							{
								findAtt = true;
							}
						}
						if (!findAtt)
						{
							match = false;
						}
					}
				}
				*/

}

bool match_xml_dtd (const XMLNode *xmlNode, const DTDRoot *dtdRoot)
{
	if (!(test_regex (xmlNode, dtdRoot)))
	{
cout << "test himself" << endl;
		return false;
	}
	int nbChildren = (xmlNode->getChildren()).size();
cout << (xmlNode->getChildren()).size() << endl;
=======
bool match_xml_dtd (XMLNode *xmlNode, DTDRoot *dtdRoot)
{
	bool match = true;
	int nbChildren = xmlNode->getChildren().size();
>>>>>>> 8581df3982f8d6104b7bb471a8e49b4bf8e9787f
	for (int i = 0; i < nbChildren; i++)
	{
		if ( (((xmlNode->getChildren()).at(i))->getChildren()).size() == 0)
		{
			if(!(match_xml_dtd((xmlNode->getChildren()).at(i), dtdRoot)))
			{
cout << "test child of child" << endl;
				return false;
			}
		}
		else
		{
<<<<<<< HEAD
			if (!(test_regex ((xmlNode->getChildren()).at(i), dtdRoot)))
			{
cout << "test child" << endl;
				return false;
=======
			DTDElement goodWay;
			try
			{
				goodWay = dtdRoot->getElement(xmlNode->getNodeName());
				if (!(regex_match(xmlNode->regexSerialize(), goodWay.toRegex())))
				{
					match = false;
				}
			} 
			catch (int e) 
			{
				match = false;
>>>>>>> 8581df3982f8d6104b7bb471a8e49b4bf8e9787f
			}
		}
	}
	return true;
}
