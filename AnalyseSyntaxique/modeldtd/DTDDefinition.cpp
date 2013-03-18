#include "DTDDefinition.h"

using namespace std;

DTDDefinition::DTDDefinition(
    DTDDefinitionType type,
    vector<DTDDefinition> children,
    string nom,
    string quantifier
) : type(type), children(children), nom(nom), quantifier(quantifier)
{}

// Getters
DTDDefinitionType DTDDefinition::getType(){return type;}
std::vector<DTDDefinition> DTDDefinition::getChildren(){return children;}
std::string DTDDefinition::getQuantifier(){return quantifier;}
std::string DTDDefinition::getNom(){return nom;}

