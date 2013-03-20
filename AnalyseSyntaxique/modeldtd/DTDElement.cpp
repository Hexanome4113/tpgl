#include "DTDElement.h"

using namespace std;

#include <string>
#include <iostream>
#include <sstream>
#include "regex.h"
#include "DTDDefinition.h"

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

void DTDElement::affiche()
{
    cout << "====>> Affichage d'un DTDElement" << endl;
    cout << "  Nom : " << nom << endl;
    cout << "  ContentSpec : " << contentSpec << endl;
    cout << "  Définition : " << endl;
    definition.affiche("  ");
    cout << "<<==== Affichage d'un DTDElement" << endl;
}

std::string DTDElement::toRegex()
{
    switch(getContentSpec()) {
        case CS_ANY:
        {
            return ".*";
        }
        break;
            
        case CS_EMPTY:
        {
            return "^$";
        }
        break;
            
        case CS_MIXED:
        {
            DTDDefinition def = getDefinition();
            DTDDefinition pcdata(BALISE, vector<DTDDefinition>(), "#PCDATA");
            def.addChild(pcdata, "before");
            return "^" + def.toRegex() + "$";
        }
        break;

        case CS_CHILDREN:
        {
            return "^" + getDefinition().toRegex() + "$";
        }
        break;
    }
}

std::string DTDElement::afficheElement()
{
	
}

