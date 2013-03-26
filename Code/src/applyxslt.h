#ifndef APPLYXSLT_H
#define APPLYXSLT_H


/**
 * \brief applique la feuille de style xslStylesheetRoot au document xmlDocumentRoot. La mémoire de l'arbre renvoyé est indépendante des arbres passés en paramètres.
 * \param xslStylesheetRoot feuille de style XSLT à appliquer.
 * \param xmlDocumentRoot document XML à transformer.
 * \return Document après transformation. 
 */
XMLNode* applyXSLT(XMLNode *xmlDocumentRoot, XMLNode *xslStylesheetRoot);

XMLNode* valueof(XMLNode *xmlNode, String select);
XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot);
vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot);

#endif // APPLYXSLT_H
