%{

using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "commun.h"
#include "yy.tab.h"

// ces trois fonctions devront changer de nom dans le cas où l'otion -p est utilisée
int yywrap(void);
void yyerror(char *msg);
int yylex(void);

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace, cf commun.h */
}

%token EGAL SLASH SUP SUPSPECIAL DOCTYPE
%token <s> ENCODING VALEUR DONNEES COMMENT NOM ENNOM
%token <en> OBALISEEN OBALISE OBALISESPECIALE FBALISE FBALISEEN

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
 : declarations declaration
 | /*vide*/
 ;
 
declaration
 : DOCTYPE NOM NOM VALEUR SUP
 ;

element
 : ouvre vide_ou_contenu  
 ;
ouvre
 : OBALISE
 | OBALISEEN
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

int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	else  printf("Parse ended with success\n", err);
  return 0;
}
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

