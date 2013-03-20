%{

using namespace std;

#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>
#include <vector>

#include "../src/XMLNode.h"
#include "../src/XMLTypes.h"

#include "../src/commun.h"

%}

%parse-param {char **dtd}
%parse-param {XMLNode **xmlRoot}

%union {
	char *s;
	ElementName *en;  // le nom d'un element avec son namespace, cf commun.h
	XMLNode *xmlnp;
	map<string, string> *att_map;
	vector<XMLNode*> *node_vect;
}

%token EGAL SLASH SUP SUPSPECIAL DOCTYPE
%token <s> ENCODING VALEUR DONNEES COMMENT NOM ENNOM
%token <en> OBALISEEN OBALISE OBALISESPECIALE FBALISE FBALISEEN
%type <s> declaration
%type <xmlnp> element
%type <en> ouvre attribut
%type <att_map> attributs_opt
%type <node_vect> vide_ou_contenu ferme_contenu_et_fin contenu_opt

%%

document
: declarations element misc_seq_opt
;

misc_seq_opt
: misc_seq_opt misc
| /*vide*/
;

misc
: COMMENT
;

declarations
: declarations declaration  { *dtd = $2; }
| /*vide*/
;

declaration
: DOCTYPE NOM NOM VALEUR SUP  { $$ = $4; }
;

element
: ouvre attributs_opt vide_ou_contenu	{
											if ($3 == NULL)
											{
												$$ = new XMLNode($1->first, $1->second, *$2);
											} else
											{
												$$ = new XMLNode($1->first, $1->second, *$2, *$3);
											}
											*xmlRoot = $$->getDocumentRoot();
											//cout << "AFFICHE" << endl << $$->Affiche();
										}
;

ouvre
: OBALISE {$$=$1;}
| OBALISEEN {$$=$1;}
;

attributs_opt
: attributs_opt attribut	{$$->insert(*$2);}
| /*vide*/ 			{$$ = new std::map<string, string>();}
;

attribut
: NOM EGAL VALEUR		{$$ = new pair<string, string>($1,$3);}
| ENNOM EGAL VALEUR		{$$ = new pair<string, string>($1,$3);}		//  A REVOIR? OHOH
;

vide_ou_contenu
: SLASH SUP			{$$=NULL;}
| ferme_contenu_et_fin SUP	{$$ = $1;}
;

ferme_contenu_et_fin
: SUP contenu_opt ferme		{$$ = $2;}
;

ferme
: FBALISE
| FBALISEEN
;

contenu_opt
: contenu_opt DONNEES	{$$->push_back(new XMLNode($2));}		//PUSH_FRONT? -> VECTOR?
| contenu_opt misc
| contenu_opt element	{$$->push_back($2);}
| /*vide*/		{$$=new std::vector<XMLNode*>();}
;

%%

int xmlwrap(void) {
	return 1;
}

void xmlerror(char **dtd, XMLNode **xmlRoot, char *msg) {
	fprintf(stderr, "%s\n", msg);
}
