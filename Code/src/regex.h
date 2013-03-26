#ifndef REGEX_H
#define REGEX_H

#include <string>
#include "XMLNode.h"
#include "DTDRoot.h"

/**
 * \brief Vérifie si le paramètre str correspond à l'expression régulière regex
 * \param str	chaîne de caractères à tester
 * \param regex	expression régulière de la règle à vérifier
 * \return	bool	true si str correspond à regex, false sinon
 */
bool regex_match(const std::string str, const std::string regex);

/**
 * \brief Teste si le noeud XML xmlNode possède et vérifie une règle définie dans dtdRoot
 * \param xmlNode	pointeur sur la structure contenant le noeud XML
 * \param dtdRoot	pointeur sur la structure contenant le document DTD
 * \return	bool	true si xmlNode a et vérifie une règle dans DTD, false sinon (pas de règle ou mauvaise implémentation)
 */
bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot);

/**
 * \brief Teste si le noeud XML xmlNode et tous ses children suivent la DTD dtdRoot
 * \param xmlRoot	pointeur sur la structure contenant le premier noeud XML
 * \param dtdRoor	pointeur sur la structure contenant le document DTD
 * \return bool	true si tous les noeuds suivent la DTD, false sinon
 */
bool match_xml_dtd (const XMLNode *xmlRoot, const DTDRoot *dtdRoot);


#endif

