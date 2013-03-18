#ifndef MYTYPES_H
#define MYTYPES_H

using namespace std;

#include "DTDElement.h"

#include <vector>
#include <string>

struct VsAndStr {
    vector<string> vs;
    string str;
};

struct CspecAndVsstr {
    ContentSpec cspec;
    VsAndStr vsstr;
};

#endif