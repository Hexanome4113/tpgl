.PHONY: all clean
.SUFFIXES: .lex.c .lex.o .tab.c .tab.h .tab.o

FLEX?=flex
BISON?=bison

SRC_DIR=src/
BIN_DIR=bin/
BUILD_DIR=build/
INCLUDE_DIR=include/
LIB_DIR=lib/

DTD_OBJS=dtd.lex.c dtd.tab.c dtd.tab.h dtd.lex.o dtd.tab.o
XML_OBJS=xml.lex.c xml.tab.c xml.tab.h xml.lex.o xml.tab.o

PARSEDTD_TARGET=$(addprefix $(BIN_DIR), parsedtd)
PARSEDTD_OBJECTS=
PARSEDTD_HEADERS=

all: $(PARSEDTD_TARGET)

clean:
	-rm -f $(addprefix $(BUILD_DIR), $(DTD_OBJS) $(XML_OBJS) $(PARSEDTD_OBJECTS)) $(PARSEDTD_TARGET)

$(PARSEDTD_TARGET): $(addprefix $(SRC_DIR), $(PARSEDTD_HEADERS)) $(addprefix $(BUILD_DIR), $(DTD_OBJS) $(PARSEDTD_OBJECTS))
	$(CXX) $(LDFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $(addprefix $(BUILD_DIR), $(DTD_OBJS) $(PARSEDTD_OBJECTS)) $(LOADLIBES) $(LDLIBS) -lpcre -o $(PARSEDTD_TARGET)

$(BUILD_DIR)%.lex.c: $(SRC_DIR)%.l
	$(FLEX) $(FLFLAGS) -P$(notdir $(basename $^)) -o$@ $^

$(BUILD_DIR)%.tab.c $(BUILD_DIR)%.tab.h: $(SRC_DIR)%.y
	$(BISON) $(BFLAGS) -o $@ -p $(notdir $(basename $^)) --defines=$(addprefix $(BUILD_DIR), $(addsuffix .tab.h, $(notdir $(basename $^)))) $^

$(BUILD_DIR)%.lex.o: $(BUILD_DIR)%.lex.c $(BUILD_DIR)%.tab.h
