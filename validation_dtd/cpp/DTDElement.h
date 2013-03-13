// DTDElement:
//         - contentspec (ANY | EMPTY | MIXED | CHILDREN)
//         - definition (DTDDefinition)
//         - nom (string)

#ifndef DTDELEMENT_H
#define DTDELEMENT_H

#include "DTDDefinition.h"
#include <string>

enum ContentSpec { ANY, EMPTY, MIXED, CHILDREN };

class DTDElement {
    public:
        DTDElement(
            std::string nom,
            ContentSpec contentSpec,
            DTDDefinition definition
        );
        ContentSpec getContentSpec();
        DTDDefinition getDefinition();
        std::string getNom();
        
    protected:
        ContentSpec contentSpec;
        DTDDefinition definition;
        std::string nom;
};

#endif

