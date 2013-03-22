#include <iostream>
#include "XMLNode.h"

XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot);

XMLNode* applyXSLT(XMLNode *xmlDocumentRoot, XMLNode *xslStylesheetRoot)
{
    vector<XMLNode*> content;
    content.push_back(xmlDocumentRoot);
    map<string,string> mapvide;
    XMLNode container("","", mapvide, content);
    XMLNode* result = matchTemplates(container, xslStylesheetRoot);
    return (*(result->getChildren().begin()))
}

vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot)
{
    vector<XMLNode*> childrenVect;
    for (vector<XMLNode *>::iterator itXsl = xslTemplate->getChildren().begin() ; itXsl != xslTemplate->getChildren().end() ; itXsl++ )
         //pour tous les fils du template xsl trouvé
    {
        if ((*itXsl)->isTextNode() )
            // si c'est un texte on l'ajoute dans le vecteur resultat
        {
            childrenVect.push_back( new XMLNode((*itXsl)->getText()) );
        }
        else if ((*itXsl)->getFullName() == "xsl:apply-templates")
            // si c'est un apply on fait un match sur le xml (donc sur ses fils)
        {
            childrenVect.push_back(matchTemplates(xmlNode, xslRoot));
        }
        else
            // sinon, c'est une balise
            {
                
                childrenVect.push_back( new XMLNode((*itXsl)->getNameSpace(), (*itXsl)->getNodeName(), (*itXsl)->getAttributes(), applyTemplate(xmlNode, *itXsl, xslRoot)) );
            }
    }
    // END pour tous les fils du template xsl trouvé
    return childrenVect;
}


XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot)
{
    vector<XMLNode*> childVect;
    
    for (vector<XMLNode *>::iterator itXml = xmlNode->getChildren().begin() ; itXml != xmlNode->getChildren().end(); itXml++ )
    {
        if ((*itXml)->isTextNode())
        {
            childVect.push_back( new XMLNode((*itXml)->getText()) );
        }
        else
        {
            bool matchTemplate = false;
            for( vector<XMLNode *>::iterator itXsl = xslRoot->getChildren().begin() ; itXsl != xslRoot->getChildren().end() ; itXsl++ )
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


