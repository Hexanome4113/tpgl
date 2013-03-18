#ifndef COMMUN_H
#define COMMUN_H

using namespace std;
#include <list>
#include <utility>
#include <string>

typedef pair<string,string> ElementName;
typedef list<string> DTDList;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


extern int xmldebug;
extern FILE *xmlin;

extern int dtddebug;
extern FILE *dtdin;

void xmlerror(char **dtd, char *msg);
int xmllex(void);
int xmlparse(char **dtd);
int xmlwrap(void);

void dtderror(char *msg);
int dtdlex(void);
int dtdparse(void);
int dtdwrap(void);

#endif
