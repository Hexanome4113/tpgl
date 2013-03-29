#ifndef COMMUN_H
#define COMMUN_H

// using namespace std;
// #include <list>
// #include <utility>
#include <string>

#include "../src/DTDRoot.h"
#include "../src/XMLNode.h"


// typedef pair<string,string> ElementName;
// typedef list<string> DTDList;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


typedef struct yy_buffer_state *XML_BUFFER_STATE;

typedef struct yy_buffer_state *DTD_BUFFER_STATE;

extern int xmldebug;
extern FILE *xmlin;

extern int dtddebug;
extern FILE *dtdin;

void xmlerror(char **dtd, XMLNode **xmlRoot, char *msg);
int xmllex(void);
int xmlparse(char **dtd, XMLNode **xmlRoot);
XML_BUFFER_STATE xml_scan_string(const char *str);
void xml_delete_buffer(XML_BUFFER_STATE buffer);
int xmlwrap(void);

void dtderror(DTDRoot **dtdroot, std::string *info, char *msg);
int dtdlex(void);
int dtdparse(DTDRoot **dtdroot, std::string *info);
DTD_BUFFER_STATE dtd_scan_string(const char *str);
void dtd_delete_buffer(DTD_BUFFER_STATE buffer);
int dtdwrap(void);

#endif
