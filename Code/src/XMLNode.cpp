#include "XMLNode.h"


XMLNode::XMLNode(string nodeNamespace, string nodeName, map<string, string> attributeList)
:elementNamespace(nodeNamespace),
elementName(nodeName),
attributes(attributeList),
nodeType(ELEMENT_NODE),
lonely(true)
{
}

XMLNode::XMLNode(string textContent)
:nodeType(TEXT_NODE),
lonely(false)
{
	if (!textContent.empty() && textContent[textContent.size()-1] != '\n')
	{
		textContent += "\n";
	}
	this->textContent = textContent;
}

XMLNode::XMLNode(string nodeNamespace, string nodeName, map<string, string> attributeList, vector<XMLNode*> childrenList)
:elementNamespace(nodeNamespace),
elementName(nodeName),
children(childrenList),
attributes(attributeList),
nodeType(ELEMENT_NODE),
lonely(false)
{
}


string XMLNode::regexSerialize()
{
	string returned;
	
	for (vector<XMLNode*>::iterator it = children.begin() ; it != children.end() ; it++)
	{
			
		if ((*it)->isTextNode())
			returned += "#PCDATA";
		else
			returned += (*it)->getNodeName();
		
		returned += " ";
	}
}

string XMLNode::indent(string strToIndent)
{
    bool first_indent = true;
    size_t lastPos = strToIndent.size();
    while ( (lastPos = strToIndent.rfind("\n", lastPos)) != string::npos )
	{
        if (first_indent)
		{
            first_indent = false;
            lastPos -=1;
        }
        else
		{
            strToIndent.replace(lastPos, 1, "\n\t");
            lastPos -=1;
        }
    }
    return strToIndent;
}


string XMLNode::Affiche()
{
	if ( isTextNode() )
	{
		return textContent;
	}
	else
	{
		string result = "<";
		if (elementNamespace != "")
		{
			result += elementNamespace + ":";
		}
		result += elementName;
		for (map<string, string>::const_iterator it = attributes.begin() ; it != attributes.end() ; it++)
		{
			result = result + " " + it->first + "=\"" + it->second + "\"";
		
		}
		
		if (lonely)
		{
			result += "/>\n";
		}
		else
		{
			result += ">\n";
			for (vector<XMLNode*>::iterator it = children.begin() ; it != children.end() ; it++)
			{
				result += (*it)->Affiche();
			}
			result=indent(result);
			result += "</";
			if (elementNamespace != "")
			{
				result += elementNamespace + ":";
			}
			result += elementName + ">\n";
		}
		return result;
	}
}

XMLNode::~XMLNode()
{

}

string XMLNode::getNameSpace()
{
	return elementNamespace;
}

string XMLNode::getNodeName()
{
	return elementName;
}

string XMLNode::getFullName()
{
	return (elementNamespace+":"+elementName);
}

bool XMLNode::hasAttribute(string name)
{
	return attributes.find(name) != attributes.end();
}


bool XMLNode::hasMixedContent()
{
	if (children.empty())
	{
		return false;
	}
	else
	{
		for (vector<XMLNode*>::iterator it = children.begin() ; it != children.end() ; it++)
		{
			if ((*it)->isTextNode())
				return true;
		}
		return false;
	}
	

	//ancienne version (contenu mixte balises ET pcdata)
	/*if (children.empty())
	{
		return false;
	}
	else
	{
		bool compareValue = (*children.begin())->isTextNode();
		for (vector<XMLNode*>::iterator it = children.begin() ; it != children.end() ; it++)
		{
			if ((*it)->isTextNode() != compareValue)
				return true;
		}
		return false;
	}*/
}


vector<XMLNode*> XMLNode::getChildren()
{
    return children;
}

XMLNode* XMLNode::getParent()
{
    return parent;
}

string XMLNode::getTextContent()
{
    return textContent;
}

XMLNode* XMLNode::getDocumentRoot()
{
    return documentRoot;
}

const map<string, string>& XMLNode::getAttributes()
{
    return attributes;
}

bool XMLNode::isTextNode()
{
    return ( nodeType == TEXT_NODE );
}

bool XMLNode::isElementNode()
{
    return ( nodeType == ELEMENT_NODE );
}

