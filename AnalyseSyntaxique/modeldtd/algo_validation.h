#ifndef ALGO_VALIDATION_H
#define ALGO_VALIDATION_H

#include "DTDElement.h"
#include "DTDDefinition.h"

std::string dtdToRegex(DTDElement elem);
std::string dtdDefinitionToRegex(DTDDefinition elem);

#endif

