#include <iostream>
#include <string>
#include "regex.h"

using namespace std;

int main()
{
    string chaine = "front note note lite author author front author back ";
    string regex = "^(?:(?:front )(?:(?:p )|(?:lite )|(?:note ))*(?:author )+(?:back )?)*$";

    bool match = regex_match(chaine, regex);
    if (match)
        cout << "Match :)" << endl;
    else
        cout << "Not match :(" << endl;
    
    return 0;
}