#include "DTDElement.h"

using namespace std;

DTDElement::DTDElement()
{}

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

void DTDElement::setNom(string n)
{
	nom = n;
}

void DTDElement::setContentSpec(ContentSpec cs)
{
	contentSpec = cs;
}

void DTDElement::setDefinition(DTDDefinition def)
{
	definition = def;
}

std::string DTDElement::affiche()
{
	
}

