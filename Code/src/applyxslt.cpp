#include <iostream>
#include "XMLNode.h"

XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot);

vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot)
{
    vector<XMLNode*> childrenVect;
    for (vector<XMLNode *>::iterator itXsl = xslTemplate->getChildren().begin() ;
         itXsl != xslTemplate->getChildren().end();
    itXsl++ )
         //pour tous les fils du template xsl trouvé
    {
        if ((*itXsl)->isTextNode() )
            // si c'est un texte on l'ajoute direct dans le vecteur resultat
        {
            childrenVect.push_back(*itXsl);
        }
        else if ((*itXsl)->getFullName() == "xsl:apply-templates")
            // si c'est un apply on fait un match sur le xml (donc sur ses fils)
        {
            childrenVect.push_back(matchTemplates(xmlNode, xslRoot));
        }
        /*else if ((*itXsl)->getFullName() == "xsl:value-of")           On ne fait pas value of?? :'(
         *                {       
         *                        string value_of =(*itXsl)->getAttributes().find("select")->second;
         *                        if (value_of.at(0) == "@")
         *                        //si c'est un attribut, recherche de l'att correspondant
         *                        {
         *                                string textValue = xmlNode->getAttributes().find(value_of.substr(1,(value_of.size()-1))->second;
         *                                childrenVect.push_back( new XmlNode* (textValue) );
         }
         else
             //sinon il faut récupérér les fils de la balise fille portant le nom "value_of"
             {
                 for (vector<XMLNode *>::iterator itXml = xmlNode->getChildren().begin() ;
                 itXml != xmlNode->getChildren().end();
                 itXml++ )
                 {
                     if (*itXml->getNodeName == value_of)
                     {
                         
         }
         }
         }
         }*/
        else
            // sinon, c'est une balise
            {
                
                vector<XMLNode*>  nextChildren = applyTemplate(xmlNode, *itXsl, xslRoot);
                childrenVect.insert( childrenVect.end(), nextChildren.begin(), nextChildren.end() ); //concat les 2 vect
            }
         }
         // END pour tous les fils du template xsl trouvé
         return childrenVect;
         }
         XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot)
         {
             XMLNode* returned;
             xmlNode->Affiche();
             
             vector<XMLNode*> childVect;
             
             for (vector<XMLNode *>::iterator itXml = xmlNode->getChildren().begin() ;
                  itXml != xmlNode->getChildren().end();
             itXml++ )
                  //pour tous les fils du noeud xml
             {       
                 bool matchTemplate = false;
                 for(    vector<XMLNode *>::iterator itXsl = xslRoot->getChildren().begin() ;
                     itXsl != xslRoot->getChildren().end();
                 itXsl++ )
                     //pour tous les templates du xsl
                 {
                     if ( (*itXsl)->getFullName() == "xsl:template" && (*itXsl)->getAttributes().find("match")->second == (*itXml)->getNodeName())
                         //est ce que un xml et un xsl matchent
                         {
                             matchTemplate = true;
                             
                             vector<XMLNode*> returnedVect = applyTemplate(xmlNode,(*itXsl),xslRoot);
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
             
             return new XMLNode(xmlNode->getNameSpace(),xmlNode->getNodeName(), xmlNode->getAttributes(), childVect);
             
             // END pour tous les fils du noeud xml          
         }
         
         
         
         int main(){
             /* Algorithme :
              *   /*
              *   /* Partir de la racine de l'arbre XML
              *   /* Pour chaque élément :
              *   /* - Parcourir le XSLT à la recherche d'un template à utiliser
              *   /* # Si on en trouve un :
              *   /*   - Ecrire le texte se trouvant AVANT la balise <apply-templates/>
              *   /*   - Faire la récursivité (voir ci-dessous)
              *   /*   - Ecrire le texte se trouvant APRES la balise <apply-templates/>
              *   /* # Si on en trouve pas :
              *   /*   - Faire seulement la récursivité
              *   /*
              *   /* Pour la récursivité, on parcourt le noeud. Pour chaque enfant :
              *   /* # Si c'est un texte, on l'écrit
              *   /* # Si c'est un noeud non-textuel, on répète les étapes précédentes
              *   /**/
              
              
              
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
              
              map<string, string> mapvide, mapattr;
              
              
              
         }
         
         