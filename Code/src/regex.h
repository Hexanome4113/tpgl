#ifndef REGEX_H
#define REGEX_H

#include <string>
#include "XMLNode.h"
#include "DTDRoot.h"

bool regex_match(const std::string str, const std::string regex);

bool match_xml_dtd (XMLNode *xmlRoot, DTDRoot *dtdRoot);

#endif

