#include <iostream>
#include "XMLNode.h"
#include "applyxslt.h"
#include <string>


//Wrapper a appeller pour lancer l'algorithme récursif
XMLNode* applyXSLT(XMLNode *xmlDocumentRoot, XMLNode *xslStylesheetRoot)
{
    vector<XMLNode*> content;
    content.push_back(xmlDocumentRoot);
    map<string,string> mapvide;
    XMLNode container("","", mapvide, content);
    XMLNode* result = matchTemplates(&container, xslStylesheetRoot);
    return (*(result->getChildren().begin()));
}
//LLA

//LAA
//LAAA

vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot)
{
    vector<XMLNode*> childrenVect;
	for (vector<XMLNode *>::const_iterator itXml = xmlNode->getChildren().begin() ; itXml != xmlNode->getChildren().end(); itXml++ )
	{
		for (vector<XMLNode *>::const_iterator itXsl = xslTemplate->getChildren().begin() ; itXsl != xslTemplate->getChildren().end() ; itXsl++ )
			//pour tous les fils du template xsl trouvé
		{
			if ((*itXsl)->isTextNode() )
				// si c'est un texte on l'ajoute dans le vecteur resultat
			{
				childrenVect.push_back( new XMLNode((*itXsl)->getTextContent()) );
			}
			else if ((*itXsl)->getFullName() == "xsl:apply-templates")
				// si c'est un apply on fait un match sur le xml (donc sur ses fils)
			{
				childrenVect.push_back(matchTemplates(*itXml, xslRoot));
			}
			else if ((*itXsl)->getFullName() == "xsl:value-of")
				//si c'est un value-of
			{
				XMLNode* textNode = valueof(*itXml, (*itXsl)->getAttributes().find("select")->second);
				if (textNode)
					childrenVect.push_back(textNode);
			}
			else if ((*itXsl)->getNameSpace() == "xsl")
				//échappement des balises XSLT non gerées
			{}
			else
				// sinon, c'est une balise
				{
					
					childrenVect.push_back( new XMLNode((*itXsl)->getNameSpace(), (*itXsl)->getNodeName(), (*itXsl)->getAttributes(), applyTemplate(xmlNode, *itXsl, xslRoot)) );
				}
		}
	}
    // END pour tous les fils du template xsl trouvé
    return childrenVect;
}


XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot)
{
    vector<XMLNode*> childVect;
    
    for (vector<XMLNode *>::const_iterator itXml = xmlNode->getChildren().begin() ; itXml != xmlNode->getChildren().end(); itXml++ )
    {
        if ((*itXml)->isTextNode())
        {
            childVect.push_back( new XMLNode((*itXml)->getTextContent()) );
        }
        else
        {
            bool matchTemplate = false;
            for( vector<XMLNode *>::const_iterator itXsl = xslRoot->getChildren().begin() ; itXsl != xslRoot->getChildren().end() ; itXsl++ )
            {
                if ( (*itXsl)->getFullName() == "xsl:template" && (*itXsl)->getAttributes().find("match")->second == (*itXml)->getNodeName())
                    //est ce que un xml et un xsl matchent
                {
                    matchTemplate = true;
                    
                    vector<XMLNode*> returnedVect = applyTemplate(*itXml,*itXsl,xslRoot);
                    childVect.insert( childVect.end(), returnedVect.begin(), returnedVect.end() );
                    
                }
            }
            // END pour tous les templates du xsl
            
            if (matchTemplate == false)
                // Si le noeud xml ne match avec aucun xsl template on le recopie sans modif
            {
                childVect.push_back( matchTemplates(*itXml, xslRoot) );
            }
        }
    }
    
    return new XMLNode(xmlNode->getNameSpace(),xmlNode->getNodeName(), xmlNode->getAttributes(), childVect);
    
    // END pour tous les fils du noeud xml
}

XMLNode* valueof(XMLNode *xmlNode, string select)
{
    string returned;
    //recherche des fils qui matchent le select
    for (vector<XMLNode *>::const_iterator itXml = xmlNode->getChildren().begin() ; itXml != xmlNode->getChildren().end(); itXml++ )
    {
        if ((*itXml)->getNodeName() == select)
        {
            //recherche des noeuds texte, concaténation au résultat
            for (vector<XMLNode *>::const_iterator itXmltext = (*itXml)->getChildren().begin() ; itXmltext != (*itXml)->getChildren().end(); itXmltext++ )
            {
                if ((*itXmltext)->isTextNode())
                {
                    returned += (*itXmltext)->getTextContent();
                }
            }
        }
    }
    if (returned.empty())
    {
        return NULL;
    }
    else
    {
        return new XMLNode(returned);
    }
}
