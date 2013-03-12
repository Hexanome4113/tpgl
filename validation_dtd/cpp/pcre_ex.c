#include <string.h>
#include <stdio.h>
#include "pcre/pcre.h"

int regex_match(const char* str, const char* regex)
{
    // pcre_compile :
    const char *err;
    int errOffset;
    pcre *re = pcre_compile(regex, PCRE_MULTILINE, &err, &errOffset, 0);
    if (!re)
    {
        printf("pcre_compile failed (offset: %d), %s\n", errOffset, err);
        return 0;
    }

    // pcre_exec :
    int ovector[100];
    unsigned int len = strlen(str);
    int match_ok = pcre_exec(re, 0, str, len, 0, 0, ovector, 100);
    return (match_ok == 1);
}

int main()
{
    int match_ok = regex_match(
        "front note note lite author author front author back ",
        "^(?:(?:front )(?:(?:p )|(?:lite )|(?:note ))*(?:author )+(?:back )?)*$"
    );
    if (match_ok)
        printf("Match :)\n");
    else
        printf("Not match :(\n");
    return 0;
}