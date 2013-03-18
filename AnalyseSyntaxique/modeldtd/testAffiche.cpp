#include <iostream>
#include <string>
#include <vector>
#include "regex.h"
#include "DTDElement.h"
#include "DTDDefinition.h"
#include "DTDRoot.h"
#include "algo_validation.h"

using namespace std;

/*
<!ATTLIST ARTICLE EDITOR CDATA #IMPLIED>
<!ATTLIST ARTICLE DATE CDATA #IMPLIED>
<!ATTLIST ARTICLE EDITION CDATA #IMPLIED>
*/

int main()
{

	vector<DTDElement> v_vide;
	v_vide.clear();
	vector<DTDAttlist> v_attlist;

	DTDAttlist article;
	article.elementName = "ARTICLE";
	vector<string> v_string;
	string editor = "EDITOR";
	v_string.push_back(editor);
	string date = "DATE";
	v_string.push_back(date);
	string edition = "EDITION";
	v_string.push_back(edition);
	article.list = v_string;
	v_attlist.push_back(article);

	DTDRoot root(v_vide, v_attlist);

	cout << root.affiche() << '\n';
	
	return 0;
}
