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

%type <elem> elt_content
%type <vs> contenu_elt_mixed_opt
%type <str> ast_elt_mixed_opt cond_elt_children_opt
%type <vs_str> elt_mixed
%type <def> name_or_choice_or_seq_elt_children seq_elt_children choice_elt_children cp_elt_children elt_children contenu_seq_elt_children_opt contenu_choice_elt_children
%type <s> att_definition_opt attribut

/* notre parseur prend en parametre un DTDRoot */
%parse-param {DTDRoot *dtdroot}

%%

main: dtd_list_opt { cout << "main found" << endl; }
;

dtd_list_opt
: dtd_list_opt ELEMENT NOM elt_content SUP
    {
        $4->setNom($3);
        dtdroot->addElement(*$4);
        delete $4;
        cout << "new dtdelement " << $3 << " of cspec " << $4 << endl; 
    }
| dtd_list_opt ATTLIST NOM att_definition_opt SUP { cout << "attlist found" << endl; }
    {
        dtdroot->addAttlist($3, $4);
    }
| /* vide */
    {
        dtdroot = new DTDRoot();
    }
;

elt_content
: EMPTY { cout << "elt empty found" << endl; }
    {
        $$ = new DTDElement();
        $$->setContentSpec(CS_EMPTY);
    }
| ANY { cout << "elt any found" << endl; }
    {
        $$ = new DTDElement();
        $$->setContentSpec(CS_ANY);
    }
| elt_mixed { cout << "elt mixed found" << endl; }
    {
        $$ = new DTDElement();
        $$->setContentSpec(CS_MIXED);
        DTDDefinition def;
        def.setQuantifier($1->str);
        def.setType(CHOICE);
        vector<DTDDefinition> v_vide;
        for (int i=0 ; i < $1->vs.size() ; i++) {
            def.addChild(DTDDefinition(BALISE, v_vide, $1->vs[i]), "back");
        }
        $$->setDefinition(def);
        delete $1;
    }
| elt_children { cout << "elt children found" << endl; }
    {
        $$ = new DTDElement();
        $$->setContentSpec(CS_CHILDREN);
        $$->setDefinition(*$1);
        delete $1;
    }
;

elt_mixed
: OUVREPAR PCDATA contenu_elt_mixed_opt FERMEPAR ast_elt_mixed_opt
    {
        $$ = new VsAndStr();
        $$->vs = *$3;
        $$->str = *$5;
        delete $3;
        delete $5;
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
        delete $2;
    }
| seq_elt_children cond_elt_children_opt
    {
        $1->setQuantifier(*$2);
        $$ = $1;
        delete $2;
    }
;

cp_elt_children
: name_or_choice_or_seq_elt_children cond_elt_children_opt
    {
        $1->setQuantifier(*$2);
        $$ = $1;
        delete $2;
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
        delete $2;
    }
;

contenu_choice_elt_children
: contenu_choice_elt_children BARRE cp_elt_children
    {
        $1->addChild(*$3, "back");
        $$ = $1;
        delete $3;
    }
| BARRE cp_elt_children
    {
        vector<DTDDefinition> v;
        v.push_back(*$2);
        $$ = new DTDDefinition(CHOICE, v);
        delete $2;
    }
;

seq_elt_children
: OUVREPAR cp_elt_children contenu_seq_elt_children_opt FERMEPAR
    {
        $3->addChild(*$2, "front");
        $$ = $3;
        delete $2;
    }
;

contenu_seq_elt_children_opt
: contenu_seq_elt_children_opt VIRGULE cp_elt_children
    {
        $1->addChild(*$3, "back");
        $$ = $1;
        delete $3;
    }
| /* vide */
    {
        vector<DTDDefinition> v_vide;
        $$ = new DTDDefinition(SEQ, v_vide);
    }
;

att_definition_opt
: att_definition_opt attribut
    {
        $$ = $2; // on ecrase les anciens att_definition_opt
    }
| /* vide */
;

attribut
: NOM att_type defaut_declaration
    {
        $$ = $1; // on oublie att_type & defaut_declaration
    }
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
