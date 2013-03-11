#ifndef XMLNODE_H
#define XMLNODE_H


using namespace std;
#include <vector>
#include <string>
#include <map>

enum XMLNodeType {
	ELEMENT_NODE,	/*!<si simple noeud*/
	TEXT_NODE		/*!<si contenu*/
};

class XMLNode
{


	
//METHODS
public:
    XMLNode();
    virtual ~XMLNode();
	
	/**
	 * \return namespace du noeud. vide si TEXT_NODE ou pas de namespace.
	 */
	string getNameSpace();

	/**
	 * \return nom du noeud. vide si TEXT_NODE.
	 */
	string getNodeName();
	
	/**
	 * \return renvoie nom et namespace au format "namespace:nom". vide si TEXT_NODE.
	 */
	string getFullName();
	
	/**
	 * \return vrai si le noeud contient un attribut de nom name.
	 * \param name nom de l'attribut recherché.
	 */
	bool hasAttribute(string name);
	
	/**
	 * \return vrai si nodeType == TEXT_NODE.
	 */
	bool isTextNode();
	
	/**
	 * \return vrai si nodeType == ELEMENT_NODE.
	 */
	bool isElementNode();
	
	//string getAttribute(string name);
	
	/**
	 * \return référence constante sur une map<nom, valeur> des attributs du noeud.
	 */
	const map<string, string>& getAttributes();
	
	/**
	 * \return vrai si contient des fils TEXT_NODE et ELEMENT_NODE.
	 */
	bool hasMixedContent();
	
	/**
	 * \return node racine du document XML représenté.
	 */
	XMLNode* getDocumentRoot();
	
	/**
	 * \return contenu texte d'un TEXT_NODE. vide si ELEMENT_NODE.
	 */
	string getTextContent();
	
	/**
	 * \return parent du noeud.
	 */
	XMLNode* getParent();
	
	/**
	 * \return vecteur des noeuds fils.
	 */
	vector<XMLNode*> getChildren();
	
	
	
		
//ATRIBUTES

	
protected:
	string elementNamespace;
	string elementName;
	string textContent;
	map<string, string> attributes;
	XMLNodeType nodeType;
	XMLNode* documentRoot;
	XMLNode* parent;
	vector<XMLNode*> children;
	
};

#endif // XMLNODE_H
