#include <iostream>
#include "../Code/src/XMLNode.h"
#include <string>

XMLNode* valueof(XMLNode *xmlNode, string select);
XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot);
vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot);


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

vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot)
{
    vector<XMLNode*> childrenVect;
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
            childrenVect.push_back(matchTemplates(xmlNode, xslRoot));
        }
        else if ((*itXsl)->getFullName() == "xsl:value-of")
            //si c'est un value-of
        {
            XMLNode* textNode = valueof(xmlNode, (*itXsl)->getAttributes().find("select")->second);
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




int main(){

     
     
     
     /*
      * map<string, string> mapvide, mapattr;
      *                mapattr.insert(make_pair<string, string>("match","papa"));
      *                
      *                XMLNode f1("blabla1\n"), f2("blabla2\n");
      *                XMLNode uniq("","fils",mapvide);                
      *                vector<XMLNode*> filsb;
      *                filsb.push_back(&f1);
      *                filsb.push_back(&uniq);
      *                filsb.push_back(&f1);
      *                
      *                XMLNode b("","papa",mapvide, filsb);
      *                
      *                cout << b.Affiche() << endl;
      * 
      *                XMLNode g1("root\n"), g2("root\n");
      *                XMLNode foo("xsl","apply-templates",mapvide);           
      *                vector<XMLNode*> fils;
      *                fils.push_back(&g1);
      *                fils.push_back(&foo);
      *                fils.push_back(&g1);
      *                XMLNode papa("xslt","template",mapattr,fils);
      *                vector<XMLNode*> filsdoc;
      *                filsdoc.push_back(&papa);
      *                XMLNode xslRoot("","doc",mapvide, filsdoc);
      *                cout << xslRoot.Affiche() << endl;
      */
     
     
     /*
      * 
      * XML a transformer
      * <doc>
      *        <papa>
      *                 <textcontent>
      *                 VALUEOF RECOPIE
      *                 </textcontent>
      *                 <papadeux>
      *                        <fils/>
      *                         un peu de texte
      * 
      *                </papadeux>
      *                 ici aussi
      * 
      *        </papa>
      * </doc>
      */
     
     map<string, string> mapvide;
     XMLNode unpeudetexte("un peu de texte"), iciaussi("iciaussi"), VALUEOFRECOPIE("VALUEOF RECOPIE"), fils("","fils",mapvide);
     
     vector<XMLNode*> filspapa2;
     filspapa2.push_back(&fils);
     filspapa2.push_back(&unpeudetexte);
     
     XMLNode papa2("","papadeux",mapvide, filspapa2);
     vector<XMLNode*> filstextcontent;
     filstextcontent.push_back(&VALUEOFRECOPIE);
     XMLNode textcontent("","textcontent",mapvide,filstextcontent);
     
     vector<XMLNode*> filspapa;
     filspapa.push_back(&textcontent);
     filspapa.push_back(&papa2);
     filspapa.push_back(&iciaussi);
     
     XMLNode papa("","papa",mapvide, filspapa);
     
     
     vector<XMLNode*> filsdoc;
     filsdoc.push_back(&papa);
     XMLNode doc ("","doc", mapvide, filsdoc);
     
     
     
     /* xslt simplifié
      * <xsl:stylesheet>
      *       <xsl:template match="papa">
      *               <xsl:value-of select="textcontent"/> 
      *               < root>
      *               rajoute du texte ici
      *               <xsl:apply-templates/>
      *               </root>
      *       </xsl:template>
      *       <xsl:template match="fils">
      *               < demi-fils>
      *               <xsl:apply-templates/>
      *               </demi-fils>
      *       </xsl:template>
      * </xsl:stylesheet>
      * 
      */
     
     XMLNode rajoutedutexteici("rajoute du texte ici");
     
     XMLNode apply("xsl","apply-templates",mapvide );
     
     vector<XMLNode*> filsroot;
     filsroot.push_back(&rajoutedutexteici);
     filsroot.push_back(&apply);
     
     XMLNode root("","root", mapvide,filsroot);
     
     map<string, string> attrvalueof;
     attrvalueof.insert(make_pair<string,string>("select","textcontent"));
     XMLNode valueof("xsl","value-of",attrvalueof);
     
     map<string, string> attrtemplate1;
     attrtemplate1.insert(make_pair<string,string>("match","papa"));
     vector<XMLNode*> filstemplate1;
     filstemplate1.push_back(&valueof);
     filstemplate1.push_back(&root);
     
     XMLNode template_papa("xsl","template", attrtemplate1,filstemplate1);
     
     vector<XMLNode*> filsdemifils;
     filsdemifils.push_back(&apply);
     XMLNode demifils("","demi-fils", mapvide,filsdemifils);
     
     map<string, string> attrtemplate2;
     attrtemplate2.insert(make_pair<string,string>("match","fils"));
     vector<XMLNode*> filstemplate2;
     filstemplate2.push_back(&demifils);
     
     XMLNode template_fils("xsl","template",attrtemplate2, filstemplate2);
     
     vector<XMLNode*> filsstylesheet;
     filsstylesheet.push_back(&template_papa);
     filsstylesheet.push_back(&template_fils);
     
     XMLNode stylesheet("xsl","stylesheet",mapvide,filsstylesheet);
     
     
     
     // et maintenant, le moment de vérité
     
     std::cout << "AFFICHE XML" << std::endl;
     std::cout << doc.Affiche()  << std::endl;
     
     std::cout << "AFFICHE XSLT" << std::endl;
     std::cout << stylesheet.Affiche()  << std::endl;
     
     
     XMLNode * formated = matchTemplates(&doc, &stylesheet);
     

     std::cout << "AFFICHE RESULTAT" << std::endl;
     std::cout << formated->Affiche()  << std::endl;
     
     
     
     
}

