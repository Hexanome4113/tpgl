%{

using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>


void yyerror(char *msg);
int yywrap(void);
int yylex(void);

%}

%union { 
   char *s; 
}

%token ELEMENT ATTLIST SUP OUVREPAR FERMEPAR VIRGULE BARRE FIXED EMPTY ANY PCDATA AST PTINT PLUS CDATA
%token <s> NOM TOKENTYPE DECLARATION VALEUR

%%

main: dtd_list_opt
;

dtd_list_opt
: dtd_list_opt ELEMENT NOM elt_content SUP
| dtd_list_opt ATTLIST NOM att_definition_opt SUP
| /* vide */
;

elt_content
: EMPTY
| ANY
| elt_mixed
| elt_children
;

elt_mixed
: OUVREPAR PCDATA contenu_elt_mixed_opt FERMEPAR AST
| OUVREPAR PCDATA FERMEPAR
;

contenu_elt_mixed_opt
: contenu_elt_mixed_opt BARRE NOM
| /* vide */
;

elt_children
: choice_elt_children cond_elt_children_opt
| seq_elt_children cond_elt_children_opt
;

cp_elt_children
: name_or_choice_or_seq_elt_children cond_elt_children_opt
;

name_or_choice_or_seq_elt_children
: NOM
| choice_elt_children
| seq_elt_children
;

cond_elt_children_opt
: PTINT
| PLUS
| AST
| /* vide */
;

choice_elt_children
: OUVREPAR cp_elt_children contenu_choice_elt_children FERMEPAR
;

contenu_choice_elt_children
: contenu_choice_elt_children BARRE cp_elt_children
| BARRE cp_elt_children
;

seq_elt_children
: OUVREPAR cp_elt_children contenu_seq_elt_children_opt FERMEPAR
;

contenu_seq_elt_children_opt
: contenu_seq_elt_children_opt VIRGULE cp_elt_children
| /* vide */
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

int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

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
