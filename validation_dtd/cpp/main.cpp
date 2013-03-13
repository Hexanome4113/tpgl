#include <iostream>
#include <string>
#include <vector>
#include "regex.h"
#include "DTDElement.h"
#include "DTDDefinition.h"
#include "algo_validation.h"

using namespace std;

int main()
{
    string chaine = "p ";
    
    vector<DTDDefinition> v, v_vide;
    v.push_back(DTDDefinition(BALISE, v_vide, "p"));
    v.push_back(DTDDefinition(BALISE, v_vide, "q"));
    DTDDefinition def(CHOICE, v, "p");
    DTDElement elem("elem", CHILDREN, def);
    
    cout << "La chaine est : " << chaine << endl;
    cout << "La regex est : " << dtdToRegex(elem) << endl;
    bool match = regex_match(chaine, dtdToRegex(elem));
    if (match)
        cout << "Match :)" << endl;
    else
        cout << "Not match :(" << endl;

    return 0;
}

