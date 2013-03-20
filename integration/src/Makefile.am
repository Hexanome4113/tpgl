bin_PROGRAMS = hello parsedtd
hello_SOURCES = hello.cpp

parsedtd_LFLAGS=-Pdtd -olex.yy.c
parsedtd_YFLAGS=-p dtd --defines=dtd.tab.h
parsedtd_SOURCES = dtd.l dtd.y DTDDefinition.cpp DTDElement.cpp DTDRoot.cpp DTDParser.cpp parsedtd.cpp

dtd.l: dtd.tab.h
