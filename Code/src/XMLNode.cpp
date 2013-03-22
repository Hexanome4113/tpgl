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
:textContent(textContent+"\n"),
nodeType(TEXT_NODE),
lonely(false)
{
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


const string XMLNode::regexSerialize() const
{
	string returned;
	
	for (vector<XMLNode*>::const_iterator it = children.begin() ; it != children.end() ; it++)
	{
			
		if ((*it)->isTextNode())
			returned += "#PCDATA";
		else
			returned += (*it)->getNodeName();
		
		returned += " ";
	}
	return returned;
}

string XMLNode::indent(string strToIndent) const
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


string XMLNode::Affiche() const
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
			for (vector<XMLNode*>::const_iterator it = children.begin() ; it != children.end() ; it++)
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

string XMLNode::getNameSpace() const
{
	return elementNamespace;
}

const string XMLNode::getNodeName() const
{
	return elementName;
}

string XMLNode::getFullName() const
{
	return (elementNamespace+":"+elementName);
}

bool XMLNode::hasAttribute(string name) const
{
	return attributes.find(name) != attributes.end();
}


bool XMLNode::hasMixedContent() const
{
	if (children.empty())
	{
		return false;
	}
	else
	{
		for (vector<XMLNode*>::const_iterator it = children.begin() ; it != children.end() ; it++)
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


const vector<XMLNode*>& XMLNode::getChildren() const
{
    return children;
}

XMLNode* XMLNode::getParent() const
{
    return parent;
}

string XMLNode::getTextContent() const
{
    return textContent;
}

XMLNode* XMLNode::getDocumentRoot() const
{
    return documentRoot;
}

const map<string, string>& XMLNode::getAttributes() const
{
    return attributes;
}

bool XMLNode::isTextNode() const
{
    return ( nodeType == TEXT_NODE );
}

bool XMLNode::isElementNode() const
{
    return ( nodeType == ELEMENT_NODE );
}

