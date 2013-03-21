#ifndef REGEX_H
#define REGEX_H

#include <string>
#include "XMLNode.h"
#include "DTDRoot.h"

bool regex_match(const std::string str, const std::string regex);

<<<<<<< HEAD
bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot);

bool match_xml_dtd (const XMLNode *xmlRoot, const DTDRoot *dtdRoot);
=======
bool match_xml_dtd (XMLNode *xmlRoot, DTDRoot *dtdRoot);
>>>>>>> 8581df3982f8d6104b7bb471a8e49b4bf8e9787f

#endif

