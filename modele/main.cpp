#include <iostream>
#include "xmlnode.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
	
	{
		map<string, string> mapvide, mapattr;
		mapattr.insert(make_pair<string, string>("toto","titi"));
		
		XMLNode f1("blabla1\n"), f2("blabla2\n");
		XMLNode uniq("unique",mapattr);
		
		vector<XMLNode*> fils;
		fils.push_back(&f1);
		fils.push_back(&uniq);
		fils.push_back(&f1);
		
		XMLNode b("b",mapvide, fils);
		
		cout << b.Affiche() << endl;
	}
	
	cout << "TEST 2" << endl;
	
	/*
	 * 	<doc titre="superbe document">
	 * 		<auteur>
	 * 			John Doe
	 * 		</auteur>
	 * 		Un peu de texte perdu au milieu
	 * 		<balse_toute_seule triste="oui"/>
	 * 		<paragraphe numero="1" interessant="oui">
	 * 			Le
	 * 			paragraphe
	 * 			avec
	 * 			des
	 * 			retours
	 * 			a
	 * 			la
	 * 			ligne
	 * 		</paragraphe>
	 * </doc>
	 */
	
	{

		
		XMLNode nom_auteur("John Doe\n");
		map<string, string> attr_auteur;
		vector<XMLNode*> fils_auteur;
		fils_auteur.push_back(&nom_auteur);
		XMLNode auteur("auteur",attr_auteur,fils_auteur);
		
		XMLNode texteperdu("Un peu de texte perdu au milieu.\n");
		
		map<string, string> attr_seule;
		attr_seule.insert(make_pair<string, string>("triste","oui"));
		XMLNode baliseSeule("balise_toute_seule",attr_seule);
		
		XMLNode texte("Le\nparagraphe\navec\ndes\nretours\na\nla\nligne\n");	
		map<string, string> attr_para;
		attr_para.insert(make_pair<string, string>("numero","1"));
		attr_para.insert(make_pair<string, string>("interessant","oui"));
		vector<XMLNode*> fils_para;
		fils_para.push_back(&texte);
		XMLNode paragraphe("paragraphe", attr_para, fils_para);
		
		map<string, string> attr_doc;
		attr_doc.insert(make_pair<string, string>("titre","superbe document"));
		vector<XMLNode*> fils_doc;
		fils_doc.push_back(&auteur);
		fils_doc.push_back(&texteperdu);
		fils_doc.push_back(&baliseSeule);
		fils_doc.push_back(&paragraphe);
		
		XMLNode doc("doc",attr_doc,fils_doc);
		
		cout << doc.Affiche() << endl;
		
	}
	
	
    return 0;
}
