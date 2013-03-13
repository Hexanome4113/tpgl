#include <iostream>
#include <string>
#include <sstream>
#include "regex.h"
#include "algo_validation.h"
#include "DTDElement.h"
#include "DTDDefinition.h"

using namespace std;

string dtdToRegex(DTDElement elem)
{
    switch(elem.getContentSpec()) {
        case ANY: // ANY | EMPTY | MIXED | CHILDREN)
            return ".*";
            break;
            
        case EMPTY:
            return "^$";
            break;
            
        case MIXED:
            // peut etre pas un cas particulier
            break;
            
        case CHILDREN:
            return "^" + dtdDefinitionToRegex(elem.getDefinition()) + "$";
            break;
    }
}

string dtdDefinitionToRegex(DTDDefinition elem)
{
    if (elem.getType() == BALISE) {
        return "(?:" + elem.getNom() + " )" + elem.getQuantifier();
    } else {
        // si c'est une sequence ou un choix, on va appliquer récursivement dtdDefinitionToRegex
        // sur les children, ce qui va nous donner un ensemble de string, jointes ensemble par un séparateur.
        string separator;
        if (elem.getType() == SEQ)
            separator = "";
        else
            separator = "|";
        stringstream ss;
        for(int i = 0; i < elem.getChildren().size(); ++i) {
            if(i != 0)
                ss << separator;
            ss << dtdDefinitionToRegex(elem.getChildren()[i]);
        }
        return "(?:" + ss.str() + ")" + elem.getQuantifier();
    }
}

