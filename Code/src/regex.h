#ifndef REGEX_H
#define REGEX_H

#include <string>

bool regex_match(const std::string str, const std::string regex);

bool match_xml_dtd (const XMLNode *xmlRoot, const DTDRoot *dtdRoot);

#endif

