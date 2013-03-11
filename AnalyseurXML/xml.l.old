%option 8bit nodefault
%option noyywrap

%{
#include "commun.h"
#include "yy.tab.h"

//récupérer le premier mot contenu dans s
static char* skipSpace(char *s) {
  char *buf;
  int i, lastnonspace;
  for (buf=s ; isspace(*buf) ; buf++) ;		//ne lit pas l'indentation ou l(es) espace(s) avant le mot
  
  //récupérer la taille du mot (jusqu'au prochain espace)
  for (i=0, lastnonspace=0 ; buf[i] ; i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  
  buf[lastnonspace+1] = '\0';	//fermer le buffer
  return buf;
}


// enlève les "(guillemets) au début et à la fin
static char* getString(char *s) {
   s++;		//avance le pointeur de 1 caractère
   s[strlen(s)-1] = '\0';	//recule le caractère de fin de char*
   return s;
}

//récupérer le premier mot contenu dans s avec la sortie en malloc
static char* word(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
  for (i = k; s[i] && ! isspace(s[i]); i++) ;
  buf = (char *) malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}

//extrait la première partie, l'espace de nom
//sortie en malloc
static char* nameSpace(char *s)
{
   char *name;
   int i,k;
   for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
   for (i=k;s[i]!=':';i++) ;	//fin de l'espace de nom au ':'
   name = (char*) malloc((i-k+1)*sizeof(char));
   strncpy(name,s+k,i-k);
   name[i-k] = '\0';
   return name;
}

//extrait la deuxième partie après l'espace de nom
//sortie en malloc
static char *split_namespace(char *s) {
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
ws		[ \t\r\n]+
open		{ws}?"<"
close		">"{nl}?
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
name		{namestart}{namechar}*
nsname		{namestart}{namechar}*":"{namestart}{namechar}*
data		([^<\n&]|\n[^<&]|\n{esc}|{esc})+
pcdata		[^<]+
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
xmlversion   {ws}?"<?xml"{ws}"version="{string}{ws}"encoding="{string}"?>"{nl}?
doctype     {ws}?"<!DOCTYPE"{ws}
openspecial {ws}?"<?"
closespecial "?>"{nl}?

/*
 * Le mode CONTENT est utilisé pour le contenu des éléments, c-à-d
 *  entre le ">" et le "<" des balises 
 * Le mode INITIAL est utilisé en dehors de l'élément RACINE 
 *  et à l'intérieur des balises
 */

%s CONTENT


%%

<INITIAL>{ws}				{ /* skip */}
<INITIAL>{xmlversion} 		{ /* skip */}
<INITIAL>{doctype} 			{ return DOCTYPE;}
<INITIAL>"/"				{ return SLASH;}
<INITIAL>"="				{ return EQ;}
<INITIAL>{close}			{ BEGIN(CONTENT); return CLOSE;}
<INITIAL>{closespecial}		{ return CLOSESPECIAL;}
<INITIAL>{name}				{ yylval.s = strdup(yytext); return IDENT;}
<INITIAL>{nsname}			{ yylval.s = strdup(yytext); return NSIDENT;}
<INITIAL>{string}			{ yylval.s = strdup(getString(yytext)); return STRING;}

{openspecial}{ws}?{name}	{ BEGIN(INITIAL); char * tmp = word(yytext); yylval.en = new ElementName("",tmp); free(tmp); return STARTSPECIAL;}
{open}{ws}?{name}			{ BEGIN(INITIAL); char * tmp = word(yytext); yylval.en = new ElementName("",tmp); free(tmp); return START;}
{open}{ws}?{nsname}			{ BEGIN(INITIAL); char *tmp1 = nameSpace(yytext); char * tmp2 = split_namespace(yytext); yylval.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return NSSTART;}
{open}"/"{name}				{ BEGIN(INITIAL); char * tmp = word(yytext); yylval.en = new ElementName("",tmp); free(tmp); return END;}
{open}"/"{nsname}			{ BEGIN(INITIAL); char *tmp1 = nameSpace(yytext); char * tmp2 = split_namespace(yytext); yylval.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return NSEND;}
{comment}					{ yylval.s = strdup(yytext); return COMMENT;}

<CONTENT>{ws}?{pcdata}		{ yylval.s = strdup(skipSpace(yytext)); return DATA;}

.			{ fprintf(stderr, "!ERROR(%c)\n", *yytext);}

