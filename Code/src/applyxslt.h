#ifndef APPLYXSLT_H
#define APPLYXSLT_H

XMLNode* matchTemplates(XMLNode *xmlNode, XMLNode *xslRoot);
vector<XMLNode*> applyTemplate(XMLNode *xmlNode, XMLNode *xslTemplate, XMLNode *xslRoot);
XMLNode* applyXSLT(XMLNode *xmlDocumentRoot, XMLNode *xslStylesheetRoot);

#endif // APPLYXSLT_H
