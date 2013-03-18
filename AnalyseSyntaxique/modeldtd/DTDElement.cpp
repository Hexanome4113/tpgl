#include "DTDElement.h"

using namespace std;

DTDElement::DTDElement(
    std::string nom,
    ContentSpec contentSpec,
    DTDDefinition definition
) : contentSpec(contentSpec), definition(definition), nom(nom)
{}

// Getters
ContentSpec DTDElement::getContentSpec(){return contentSpec;}
DTDDefinition DTDElement::getDefinition(){return definition;}
std::string DTDElement::getNom(){return nom;}

std::string DTDElement::affiche()
{
	
}

