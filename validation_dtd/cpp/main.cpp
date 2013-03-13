#include <iostream>
#include <string>
#include <vector>
#include "regex.h"
#include "DTDElement.h"
#include "DTDDefinition.h"
#include "algo_validation.h"

using namespace std;

// <!ELEMENT annnuaire (#PCDATA | personne)*>
// <!ELEMENT personne  (nom,prenom,email+)>
// <!ATTLIST personne type CDATA #IMPLIED>
// <!ELEMENT nom       (#PCDATA)>
// <!ELEMENT prenom    (#PCDATA)>
// <!ELEMENT email (#PCDATA)>

// <!DOCTYPE annuaire SYSTEM "annuaire.dtd">
// <annuaire>
//     Test de texte
//     <personne type="étudiant">
//         <nom>HEUTE</nom>
//         <prenom>Thomas</prenom>
//         <email>webmaster@xmlfacile.com</email>
//     </personne>
//     <personne type="chanteur">
//         <nom>CANTAT</nom>
//         <prenom>Bertrand</prenom>
//         <email>noir@desir.fr</email>
//     </personne>
//     Re-du texte...
// </annuaire>

int main()
{
    string chaine = "#PCDATA personne personne #PCDATA ";
    
    vector<DTDDefinition> v, v_vide;
    v.push_back(DTDDefinition(BALISE, v_vide, "#PCDATA"));
    v.push_back(DTDDefinition(BALISE, v_vide, "personne"));
    v.push_back(DTDDefinition(BALISE, v_vide, "truc"));
    DTDDefinition def(CHOICE, v, "", "*");
    DTDElement elem("elem", CHILDREN, def);
    
    cout << "La chaine est : " << chaine << endl;
    cout << "La regex est : " << dtdToRegex(elem) << endl;
    bool match = regex_match(chaine, dtdToRegex(elem));
    if (match)
        cout << "Match :-)" << endl;
    else
        cout << "Not match :'(" << endl;

    return 0;
}

