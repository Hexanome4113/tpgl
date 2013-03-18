#include "DTDDefinition.h"

#include <string>

using namespace std;

DTDDefinition::DTDDefinition() : type(BALISE), nom(""), quantifier("")
{}

DTDDefinition::DTDDefinition(
    DTDDefinitionType type,
    vector<DTDDefinition> children,
    string nom,
    string quantifier
) : type(type), children(children), nom(nom), quantifier(quantifier)
{}

// Getters
DTDDefinitionType DTDDefinition::getType(){return type;}

void DTDDefinition::setType(DTDDefinitionType t)
{
	type = t;
}

std::vector<DTDDefinition> DTDDefinition::getChildren(){return children;}

void DTDDefinition::addChild(DTDDefinition def, string position)
{
    if (position == "back")
        children.push_back(def);
    else
        children.insert(children.begin(), def);
}

std::string DTDDefinition::getQuantifier(){return quantifier;}

void DTDDefinition::setQuantifier(string q){quantifier = q;}

std::string DTDDefinition::getNom(){return nom;}

void DTDDefinition::setNom(string n)
{
	nom = n;
}
