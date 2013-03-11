#include "xmlnode.h"

XMLNode::XMLNode()
{
	
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
		bool compareValue = (*children.begin()).isTextNode();
		for (map<string, string>::iterator it = attributes.begin() ; it != attributes.end() ; it++)
		{
			if (*it.isTextNode() != compareValue)
				return true;
		}
		return false;
	}
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
