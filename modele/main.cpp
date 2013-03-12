#include <iostream>
#include "xmlnode.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
	
	map<string, string> mapvide, mapattr;
	mapattr.insert(make_pair<string, string>("toto","titi"));
	
	XMLNode f1("blabla1\n"), f2("blabla2\n");
	XMLNode uniq("unique",mapattr);
	
	vector<XMLNode*> fils;
	fils.push_back(&f1);
	fils.push_back(&uniq);
	fils.push_back(&f1);
	
	XMLNode b("b",mapvide, fils);
	
	cout << b.Affiche() << endl;
	
    return 0;
}
