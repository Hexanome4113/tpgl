#ifndef DTDROOT_H
#define DTDROOT_H

using namespace std;

#include <vector>
#include <string>
#include "DTDElement.h"

struct DTDAttlist
{
	string elementName;
	vector<string> list;
};

class DTDRoot
{
	//METHODS
public:
   /**
	* \brief Constructeur de DTDRoot
	*/ 
	DTDRoot();
	
   /**
	* \brief Constructeur de DTDRoot
	* \param elements	vecteur contenant des éléments à insérer dans le nouveau DTDRoot
	* \param attlists	vecteur contenant des attributs à insérer dans le nouveau DTDRoot
	*/ 
	DTDRoot(vector<DTDElement> elements, vector<DTDAttlist> attlists);
	
   /**
	* \brief Récupérer la lite des éléments
	*/ 
	const vector<DTDElement>& getElements() const;

   /**
	* \brief Ajouter un élément
	* \param element	élément à ajouter
	*/ 
	void addElement(DTDElement element);
	
   /**
	* \brief Récupérer la liste des règles sur les attributs
	*/ 
	const vector<DTDAttlist>& getAttlists() const;
	
   /**
	* \brief Ajouter une règle sur les attributs
	* \param nom	nom de l'élément auquel va s'appliquer cet attribut
	* \param attr	nom de l'attribut
	*/ 
	void addAttlist(std::string nom, std::string attr);

	
   /**
	* \brief Reconstitution de tout le document DTD
	* \return string contenant le document DTD original
	*/ 
	string affiche() const;
	
   /**
	* \brief Reconstitution des règles d'attributs d'un élément
	* \return string contenant les règles d'attributs d'un élément telle qu'elles seraient dans un document DTD
	*/ 
	string attlistAffiche(DTDAttlist attlist) const;
	
   /**
	* \brief Récupérer un élément en particulier
	* \param elementName	nom de l'élément recherché
	*/ 
	const DTDElement* getElement(const string elementName) const;
	
   /**
	* \brief Récupérer une liste d'attribut d'un élément en particulier
	* \param elementName	nom de l'élément dont on souhaite les attributs
	*/ 
	const DTDAttlist* getAttList(const string elementName) const;
	
protected:
	
	//ATTRIBUTES
	vector<DTDElement> elements;
	vector<DTDAttlist> attlists;
};

#endif // DTDROOT_H
