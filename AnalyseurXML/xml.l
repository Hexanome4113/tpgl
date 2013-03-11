%option 8bit nodefault
%option noyywrap

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "commun.h"
#include "yy.tab.h"

// si vous activez l'option -P de flex, changez les deux lignes suivantes
#define YYTEXT yytext
#define YYLVAL yylval
// exemple avec -Pxml
//#define YYTEXT xmltext
//#define YYLVAL xmllval

// supprime les espaces en début et fin de chaine
static char* supprimeEspaces(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return buf;
}

// enlève les " au début et à la fin
static char * enleveGuillemets(char *s) {
   s++;
   s[strlen(s)-1] = '\0';
   return s;
}

// extrait le mot
static char* mot(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; !isalpha(s[k]); k++) ;
  for (i = k; isalpha(s[i])||s[i]=='-'; i++) ;
  buf = (char *) malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}

/* extrait la première partie, l'espace de nom */
static char * espaceDeNom(char *s)  
{
   char *name;
   int i,k;
   for (k = 0; isspace(s[k]) || s[k]=='<' || s[k]=='/'; k++) ;
   for (i=k;s[i]!=':';i++) ;
   name = (char*) malloc((i-k+1)*sizeof(char));
   strncpy(name,s+k,i-k);
   name[i-k] = '\0';
   return name;
}

/* extrait la deuxième partie après l'espace de nom */
static char * separeNom(char *s) 
{ 
   char *name;
   int i,k;
   for (i=0;s[i]!=':';i++) ;
   i++;
   name = (char*) malloc((strlen(s+i)+1)*sizeof(char));
   strcpy(name,s+i);
   return name;
}


%}

nl		(\r\n|\r|\n)
esp		[ \t\r\n]+
inf		{esp}?"<"
sup		">"{nl}?
debutnom	[A-Za-z\200-\377_]
caracnom	[A-Za-z\200-\377_0-9.-]
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
nom		{debutnom}{caracnom}*
ennom		{debutnom}{caracnom}*":"{debutnom}{caracnom}*
data		([^<\n&]|\n[^<&]|\n{esc}|{esc})+
pcdata		[^<]+
comment		{inf}"!--"([^-]|"-"[^-])*"--"{sup}
chaine		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
xmlversion   {esp}?"<?xml"{esp}"version="{chaine}{esp}"encoding="{chaine}"?>"{nl}?
doctype     {esp}?"<!DOCTYPE"{esp}
infspecial {esp}?"<?"
supspecial "?>"{nl}?

/*
 * Le mode CONTENU est utilisé entre les balises ouvrantes et fermantes
 * Le mode INITIAL est utilisé en dehors de la balise racine ou entre les < >
 */

%s CONTENU

%%

<INITIAL>{esp}		{/* skip */}
<INITIAL>{xmlversion} {/* skip */}
<INITIAL>{doctype} {return DOCTYPE;}
<INITIAL>"/"		{return SLASH;}
<INITIAL>"="		{return EGAL;}
<INITIAL>{sup}	{BEGIN(CONTENU); return SUP;}
<INITIAL>{supspecial}	{ return SUPSPECIAL;}
<INITIAL>{nom}		{YYLVAL.s = strdup(YYTEXT); return NOM;}
<INITIAL>{ennom}		{YYLVAL.s = strdup(YYTEXT); return ENNOM;}
<INITIAL>{chaine}	{YYLVAL.s = strdup(enleveGuillemets(YYTEXT)); return VALEUR;}

{infspecial}{esp}?{nom}	{BEGIN(INITIAL); char * tmp = mot(YYTEXT); YYLVAL.en = new ElementName("",tmp); free(tmp); return OBALISESPECIALE;}
{inf}{esp}?{nom}	{BEGIN(INITIAL); char * tmp = mot(YYTEXT); YYLVAL.en = new ElementName("",tmp); free(tmp); return OBALISE;}
{inf}{esp}?{ennom}	{BEGIN(INITIAL); char *tmp1 = espaceDeNom(YYTEXT); char * tmp2 = separeNom(YYTEXT); YYLVAL.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return OBALISEEN;}
{inf}"/"{nom}		{BEGIN(INITIAL); char * tmp = mot(YYTEXT); YYLVAL.en = new ElementName("",tmp); free(tmp); return FBALISE;}
{inf}"/"{ennom}		{BEGIN(INITIAL); char *tmp1 = espaceDeNom(YYTEXT); char * tmp2 = separeNom(YYTEXT); YYLVAL.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return FBALISEEN;}
{comment}		{YYLVAL.s = strdup(YYTEXT); return COMMENT;}

<CONTENU>{esp}?{pcdata}		{YYLVAL.s = strdup(supprimeEspaces(YYTEXT)); return DONNEES;}

.			{fprintf(stderr, "!ERROR(%c)\n", *YYTEXT);}
