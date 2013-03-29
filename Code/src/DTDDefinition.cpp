#include "DTDDefinition.h"

#include <string>
#include <iostream>

#include <sstream>
#include "regex.h"

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

std::string DTDDefinition::toRegex()
{
    if (getType() == BALISE) {
        return "(?:" + getNom() + " )" + getQuantifier();
    } else {
        // si c'est une sequence ou un choix, on va appliquer récursivement dtdDefinitionToRegex
        // sur les children, ce qui va nous donner un ensemble de string, jointes ensemble par un séparateur.
        string separator;
        if (getType() == SEQ)
            separator = "";
        else
            separator = "|";
        stringstream ss;
        for(int i = 0; i < getChildren().size(); ++i) {
            if(i != 0)
                ss << separator;
            ss << getChildren()[i].toRegex();
        }
        return "(?:" + ss.str() + ")" + getQuantifier();
    }
}

std::string DTDDefinition::afficheDefinition()
{
	if (getType() == BALISE)
	{
        return getNom() + getQuantifier();
    }
    else
    {
		string separator;
        if (getType() == SEQ)
            separator = ", ";
        else
            separator = "|";
        stringstream ss;
        for(int i = 0; i < getChildren().size(); ++i) {
            if(i != 0)
                ss << separator;
            ss << getChildren()[i].afficheDefinition();
        }
        return "(" + ss.str() + ")" + getQuantifier();
    }
}
