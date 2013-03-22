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
	
        XMLNode();                       //interdit
        XMLNode(const XMLNode&);        //interdit

	
	/**
	 * \brief constructeur pour feuille contenant des données #PCDATA.
	 * \param textContent texte contenu. +\\n automatique.
	 */
	XMLNode(string textContent);
	
	/**
	 * \brief constructeur pour balises uniques (type "<balise/>").
	 * 	 * \param nodeName namespace de la balise.
	 * \param nodeName nom de la balise.
	 * \param attributeList liste des attributs. Peut être vide.
	 */
        XMLNode(string nodeNamespace, string nodeName, map<string, string> attributeList);
	
	/**
	 * \brief constructeur pour balises standard.
	 * \param nodeName namespace de la balise.
	 * \param nodeName nom de la balise.
	 * \param childrenList liste des noeuds fils. Si vide, les balises ouvrantes/fermantes seront quand même générées lors de l'appel à Affiche(). Voir le constructeur pour balises uniques.
	 * \param attributeList liste des attributs. Peut être vide.
	 */
	XMLNode(string nodeNamespace, string nodeName, map<string, string> attributeList, vector<XMLNode*> childrenList);
	
	
    virtual ~XMLNode();
	
	
	const string regexSerialize() const;
	
	string Affiche() const;
	
	/**
	 * \return namespace du noeud. vide si TEXT_NODE ou pas de namespace.
	 */
	string getNameSpace() const;

	/**
	 * \return nom du noeud. vide si TEXT_NODE.
	 */
	const string getNodeName() const;
	
	/**
	 * \return renvoie nom et namespace au format "namespace:nom". vide si TEXT_NODE.
	 */
	string getFullName() const;
	
	/**
	 * \return vrai si le noeud contient un attribut de nom name.
	 * \param name nom de l'attribut recherché.
	 */
	bool hasAttribute(string name) const;
	
	/**
	 * \return vrai si nodeType == TEXT_NODE.
	 */
	bool isTextNode() const;
	
	/**
	 * \return vrai si nodeType == ELEMENT_NODE.
	 */
	bool isElementNode() const;
	
	//string getAttribute(string name);
	
	/**
	 * \return référence constante sur une map<nom, valeur> des attributs du noeud.
	 */
	const map<string, string>& getAttributes() const;
	
	/**
	 * \return vrai si contient des fils de type TEXT_NODE (donc du #PCDATA).
	 */
	bool hasMixedContent() const;
	
	/**
	 * \return node racine du document XML représenté.
	 */
	XMLNode* getDocumentRoot() const;
	
	/**
	 * \return contenu texte d'un TEXT_NODE. vide si ELEMENT_NODE.
	 */
	string getTextContent() const;
	
	/**
	 * \return parent du noeud.
	 */
	XMLNode* getParent() const;
	
	/**
	 * \return vecteur des noeuds fils.
	 */
	vector<XMLNode*>& getChildren();
	

protected:
	
	string indent(string strToIndent) const;

	
//ATRIBUTES
	string elementNamespace;
	string elementName;
	string textContent;
	bool lonely;
	map<string, string> attributes;
	XMLNodeType nodeType;
	XMLNode* documentRoot;
	XMLNode* parent;
	vector<XMLNode*> children;
	
};

#endif // XMLNODE_H
