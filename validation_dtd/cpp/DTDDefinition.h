// DTDDefinition:
//         - type (SEQ | CHOICE | BALISE)
//         - children (List<DTDDefinition>) (absent si type == BALISE)
//         - quantifier ('?' | '*' | '+' | '')
//         - nom (string) (seulement si type == BALISE)

#ifndef DTDDEFINITION_H
#define DTDDEFINITION_H

#include <vector>
#include <string>

enum DTDDefinitionType { SEQ, CHOICE, BALISE };

class DTDDefinition {
    public:
        DTDDefinition(
            DTDDefinitionType type,
            std::vector<DTDDefinition> children,
            std::string nom="",
            std::string quantifier=""
        );
        DTDDefinitionType getType();
        std::vector<DTDDefinition> getChildren();
        std::string getQuantifier();
        std::string getNom();
        
    protected:
        DTDDefinitionType type;
        std::vector<DTDDefinition> children;
        std::string quantifier;
        std::string nom;
};

#endif

