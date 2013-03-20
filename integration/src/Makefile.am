bin_PROGRAMS = hello parsedtd
hello_SOURCES = hello.cpp

AM_LFLAGS=-Pdtd -olex.yy.c
AM_YFLAGS=-p dtd -d
parsedtd_SOURCES = dtd.y dtd.l DTDDefinition.cpp DTDElement.cpp DTDRoot.cpp DTDParser.cpp parsedtd.cpp
