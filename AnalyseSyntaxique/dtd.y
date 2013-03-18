%{

using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "modeldtd/DTDRoot.h"
#include "modeldtd/DTDDefinition.h"
#include "modeldtd/DTDElement.h"
#include "modeldtd/mytypes.h"

#include "commun.h"

%}

%union {
    string *str;
	char *s;
    DTDDefinition *def;
    DTDElement *elem;
    vector<string> *vs;
    VsAndStr *vs_str;
    CspecAndVsstr *c_vsstr;
    int i;
}

%token ELEMENT ATTLIST SUP OUVREPAR FERMEPAR VIRGULE BARRE FIXED EMPTY ANY PCDATA AST PTINT PLUS CDATA
%token <s> NOM TOKENTYPE DECLARATION VALEUR

%type <i> elt_content
%type <vs> contenu_elt_mixed_opt
%type <str> ast_elt_mixed_opt cond_elt_children_opt
%type <vs_str> elt_mixed
%type <def> name_or_choice_or_seq_elt_children seq_elt_children choice_elt_children cp_elt_children elt_children contenu_seq_elt_children_opt contenu_choice_elt_children

/* notre parseur prend en parametre un DTDRoot */
%parse-param {DTDRoot *dtdroot}

%%

main: dtd_list_opt { cout << "main found" << endl; }
{
    // DTDRoot = new ...
}
;

dtd_list_opt
: dtd_list_opt ELEMENT NOM elt_content SUP
    {
        vector<DTDDefinition> v_vide;
        DTDDefinition def(BALISE, v_vide, "personne");
        DTDElement *e = new DTDElement($3, CS_EMPTY, def);
        cout << "new dtdelement " << $3 << " of cspec " << $4 << endl; 
    }
| dtd_list_opt ATTLIST NOM att_definition_opt SUP { cout << "attlist found" << endl; }
| /* vide */
;

elt_content
: EMPTY { cout << "elt empty found" << endl; }
| ANY { cout << "elt any found" << endl; }
| elt_mixed { cout << "elt mixed found" << endl; }
    {
        $$ = 1;
    }
| elt_children { cout << "elt children found" << endl; }
    {
        $$ = 2;
    }
;

elt_mixed
: OUVREPAR PCDATA contenu_elt_mixed_opt FERMEPAR ast_elt_mixed_opt
    {
        $$ = new VsAndStr();
        $$->vs = *$3;
        $$->str = *$5;
    }
;

contenu_elt_mixed_opt
: contenu_elt_mixed_opt BARRE NOM
    {
        $$->push_back($3);
    }
| /* vide */
    {
        $$ = new vector<string>();
    }
;

ast_elt_mixed_opt
: AST
    {
        $$ = new string("*");
    }
| /* vide */
    {
        $$ = new string("");
    }
;

elt_children
: choice_elt_children cond_elt_children_opt
    {
        $1->setQuantifier(*$2);
        $$ = $1;
    }
| seq_elt_children cond_elt_children_opt
    {
        $1->setQuantifier(*$2);
        $$ = $1;
    }
;

cp_elt_children
: name_or_choice_or_seq_elt_children cond_elt_children_opt
    {
        $1->setQuantifier(*$2);
        $$ = $1;
    }
;

name_or_choice_or_seq_elt_children
: NOM
    {
        vector<DTDDefinition> v_vide;
        $$ = new DTDDefinition(BALISE, v_vide, $1);
    }
| choice_elt_children
    {
        $$ = $1;
    }
| seq_elt_children
    {
        $$ = $1;
    }
;

cond_elt_children_opt
: PTINT
    {
        $$ = new string("?");
    }
| PLUS
    {
        $$ = new string("+");
    }
| AST
    {
        $$ = new string("*");
    }
| /* vide */
    {
        $$ = new string("");
    }
;

choice_elt_children
: OUVREPAR cp_elt_children contenu_choice_elt_children FERMEPAR
    {
        $3->addChild(*$2, "front");
        $$ = $3;
    }
;

contenu_choice_elt_children
: contenu_choice_elt_children BARRE cp_elt_children
    {
        $1->addChild(*$3, "back");
        $$ = $1;
    }
| BARRE cp_elt_children
    {
        vector<DTDDefinition> v;
        v.push_back(*$2);
        $$ = new DTDDefinition(CHOICE, v);
    }
;

seq_elt_children
: OUVREPAR cp_elt_children contenu_seq_elt_children_opt FERMEPAR
    {
        $3->addChild(*$2, "front");
        $$ = $3;
    }
;

contenu_seq_elt_children_opt
: contenu_seq_elt_children_opt VIRGULE cp_elt_children
    {
        $1->addChild(*$3, "back");
        $$ = $1;
    }
| /* vide */
    {
        vector<DTDDefinition> v_vide;
        $$ = new DTDDefinition(SEQ, v_vide);
    }
;

att_definition_opt
: att_definition_opt attribut
| /* vide */
;

attribut
: NOM att_type defaut_declaration
;

att_type
: CDATA
| TOKENTYPE
| type_enumere
;

type_enumere
: OUVREPAR liste_enum_plus FERMEPAR
;

liste_enum_plus
: liste_enum BARRE NOM
;

liste_enum
: NOM
| liste_enum BARRE NOM
;

defaut_declaration
: DECLARATION
| VALEUR
| FIXED VALEUR
;

%%

int dtdwrap(void) {
	return 1;
}

void dtderror(DTDRoot *dtdroot, char *msg) {
	fprintf(stderr, "%s\n", msg);
}
