// DTDElement:
//         - contentspec (ANY | EMPTY | MIXED | CHILDREN)
//         - definition (DTDDefinition)
//         - nom (string)

#ifndef DTDELEMENT_H
#define DTDELEMENT_H

#include "DTDDefinition.h"
#include <string>

enum ContentSpec { 
    CS_ANY, /*!<Contient n'importe quoi*/
    CS_EMPTY, /*!<Ne contient rien*/
    CS_MIXED, /*!<Contient du contenu mixte (texte et xml)*/
    CS_CHILDREN /*!<Contient des éléments XML*/
};

class DTDElement {
    public:
        /**
        * \brief constructeur DTDElement standard
        * \param nom nom de l'élément xml qu'on va définir
        * \param contentSpec type du contenu (ContentSpec)
        * \param definition définition DTD de l'élément
         */
        DTDElement(
            std::string nom,
            ContentSpec contentSpec,
            DTDDefinition definition
        );
        
        /**
         * \return ContentSpec de l'élément
         */
        ContentSpec getContentSpec();
        
        /**
         * \return Définition DTD de l'élément
         */
        DTDDefinition getDefinition();
        
        /**
         * \return nom de l'élement
         */
        std::string getNom();
        
	/**
	 * \return affichage de l'élément
	 */
	std::string affiche();


    protected:
        ContentSpec contentSpec;
        DTDDefinition definition;
        std::string nom;
};

#endif

