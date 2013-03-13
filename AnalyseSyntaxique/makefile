all: analyseur

analyseur: main.cpp analyseXML analyseDTD
	g++ -g -DXMLDEBUG=1 -DDTDDEBUG=1 -o analyseur main.cpp lex.xml.c xml.tab.c lex.dtd.c dtd.tab.c

analyseXML: xml.l xml.y commun.h
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y

analyseDTD: dtd.l dtd.y
	flex -Pdtd dtd.l
	bison -p dtd --debug --verbose --defines=dtd.tab.h dtd.y

clean:
	-rm -rf xml.tab.c lex.xml.c xml.tab.h xml.output dtd.tab.c lex.dtd.c dtd.tab.h dtd.output analyseur
