all: traitement_template

traitement_template: main.cpp 
	g++ -g -DXMLDEBUG=1 -DDTDDEBUG=1 -o traitement_template main.cpp ../Code/src/XMLNode.cpp


clean:
	-rm -rf traitement_template
