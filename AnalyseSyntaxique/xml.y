%{

using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>
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
: ouvre attributs_opt vide_ou_contenu
;

ouvre
: OBALISE
| OBALISEEN
;

attributs_opt
: attributs_opt attribut
| /*vide*/
;

attribut
: NOM EGAL VALEUR
;

vide_ou_contenu
: SLASH SUP
| ferme_contenu_et_fin SUP
;

ferme_contenu_et_fin
: SUP contenu_opt FBALISE
;

contenu_opt
: contenu_opt DONNEES
| contenu_opt misc
| contenu_opt element
| /*vide*/
;

%%

int xmlwrap(void) {
	return 1;
}

void xmlerror(char **dtd, char *msg) {
	fprintf(stderr, "%s\n", msg);
}
