#ifndef REGEX_H
#define REGEX_H

#include <string>
#include "XMLNode.h"
#include "DTDRoot.h"

bool regex_match(const std::string str, const std::string regex);

bool test_regex (const XMLNode *xmlNode, const DTDRoot *dtdRoot);

bool match_xml_dtd (const XMLNode *xmlRoot, const DTDRoot *dtdRoot);

#endif

