#include "DTDRoot.h"
#include "DTDParser.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 1;
	}

	DTDRoot *dtd;
	if (!(dtd = DTDParser::loadFromFile(argv[1]))) {
        return 102; // 102 == ERR_ANALYSE_SYNTAXIQUE
	} else {
		delete dtd;
		return 0;
	}
}
