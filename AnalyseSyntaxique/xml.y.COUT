%{

using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "commun.h"

%}

%parse-param {
	char **dtd
}

%union {
	char *s;
	ElementName *en;  // le nom d'un element avec son namespace, cf commun.h
}

%token EGAL SLASH SUP SUPSPECIAL DOCTYPE
%token <s> ENCODING VALEUR DONNEES COMMENT NOM ENNOM
%token <en> OBALISEEN OBALISE OBALISESPECIALE FBALISE FBALISEEN
%type <s> declaration

%%

document
	: declarations element misc_seq_opt	{printf("document - declarations element misc_seq_opt\n");}
;

misc_seq_opt
: misc_seq_opt misc	{printf("misc_seq_opt\n");}
| /*vide*/	{printf("misc_seq_opt\n");}
;

misc
	: COMMENT	{printf("misc\n");}
;

declarations
: declarations declaration  { *dtd = $2; }
| /*vide*/
;

declaration
: DOCTYPE NOM NOM VALEUR SUP  { $$ = $4; }
;

element
	: ouvre attributs_opt vide_ou_contenu	{printf("element\n");}
;

ouvre
: OBALISE	{cout <<"ouvre- OBALISE \n " + $1->second;}
| OBALISEEN	{printf("ouvre- OBALISEEN\n");}
;

attributs_opt
	: attributs_opt attribut	{printf("attributs_opt\n");}
| /*vide*/
;

attribut
	: NOM EGAL VALEUR	{printf("attribut- NOM EGAL VALEUR\n");}
| ENNOM EGAL VALEUR	{printf("attribut- ENNOM EGAL VALEUR\n");}
;

vide_ou_contenu
	: SLASH SUP	{printf("vide_ou_contenu - SLASH SUP\n");}
| ferme_contenu_et_fin SUP	{printf("vide_ou_contenu - ferme_contenu_et_fin SUP\n");}
;

ferme_contenu_et_fin
	: SUP contenu_opt ferme	{printf("ferme_contenu_et_fin\n");}
;

ferme
	: FBALISE	{printf("ferme- FBALISE\n");}
| FBALISEEN	{printf("ferme- FBALISEEN\n");}
;

contenu_opt
	: contenu_opt DONNEES	{printf("contenu_opt- contenu_opt DONNEES\n");}
| contenu_opt misc	{printf("contenu_opt- contenu_opt misc\n");}
| contenu_opt element	{printf("contenu_opt- contenu_opt element\n");}
| /*vide*/	{printf("contenu_opt- vide\n");}
;

%%

int xmlwrap(void) {
	return 1;
}

void xmlerror(char **dtd, char *msg) {
	fprintf(stderr, "%s\n", msg);
}
