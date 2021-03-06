// DTDDefinition:
//         - type (SEQ | CHOICE | BALISE)
//         - children (List<DTDDefinition>) (absent si type == BALISE)
//         - quantifier ('?' | '*' | '+' | '')
//         - nom (string) (seulement si type == BALISE)

#ifndef DTDDEFINITION_H
#define DTDDEFINITION_H

#include <vector>
#include <string>

enum DTDDefinitionType {
    SEQ, /*!<Sequence d'éléments*/
    CHOICE, /*!<Choix d'éléments*/
    BALISE /*!<élément seul*/
};

class DTDDefinition {
    public:
        /**
        * \brief constructeur DTDElement standard
        * \param type type de la définition (séquence | choix | balise)
        * \param children sous-définitions (seulement si le type != BALISE)
        * \param nom nom de la balise (seulement si le type == BALISE)
        * \param quantifier quantifieur pour cette balise/séquence/choix. * | + | ? | RIEN
         */
        DTDDefinition(
            DTDDefinitionType type,
            std::vector<DTDDefinition> children,
            std::string nom="",
            std::string quantifier=""
        );
        
        /**
         * \return type de la définition (séquence | choix | balise)
         */
        DTDDefinitionType getType();
        
        /**
         * \return sous-définitions de la définition (seulement si le type != BALISE)
         */
        std::vector<DTDDefinition> getChildren();
        
        /**
         * \return quantifieur de la définition (* | + | ? | RIEN)
         */
        std::string getQuantifier();
        
        /**
         * \return nom de la balise (seulement si le type == BALISE)
         */
        std::string getNom();
        
    protected:
        DTDDefinitionType type;
        std::vector<DTDDefinition> children;
        std::string quantifier;
        std::string nom;
};

#endif

