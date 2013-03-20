.PHONY: all clean $(PARSEDTD_TARGET)
.SUFFIXES: .lex.cpp .lex.o .tab.cpp .tab.h .tab.o

BISON?=bison
FLEX?=flex

CPPFLAGS=-I$(INCLUDE_DIR)
LDFLAGS=-L$(LIB_DIR)

SRC_DIR=src/
BIN_DIR=bin/
BUILD_DIR=build/
INCLUDE_DIR=include/
LIB_DIR=lib/

DTD_OBJS=dtd.lex.cpp dtd.tab.cpp dtd.tab.h dtd.lex.o dtd.tab.o regex.o DTDDefinition.o DTDElement.o DTDRoot.o DTDParser.o
XML_OBJS=xml.lex.cpp xml.tab.cpp xml.tab.h xml.lex.o xml.tab.o XMLNode.o XMLParser.o

PARSEDTD_TARGET=parsedtd
PARSEDTD_OBJECTS=parsedtd.o
PARSEDTD_HEADERS=

all: $(addprefix $(BIN_DIR), $(PARSEDTD_TARGET))

clean:
	-rm -f $(addprefix $(BUILD_DIR), $(DTD_OBJS) $(XML_OBJS) $(PARSEDTD_OBJECTS)) $(addprefix $(BIN_DIR), $(PARSEDTD_TARGET)) $(addprefix $(BUILD_DIR), $(addsuffix .d, $(basename $(filter %.o, $(DTD_OBJS) $(XML_OBJS) $(PARSEDTD_OBJECTS)))))

$(PARSEDTD_TARGET): $(BIN_DIR)$(PARSEDTD_TARGET)

$(BIN_DIR)$(PARSEDTD_TARGET): $(addprefix $(SRC_DIR), $(PARSEDTD_HEADERS)) $(addprefix $(BUILD_DIR), $(DTD_OBJS) $(PARSEDTD_OBJECTS))
	$(CXX) $(LDFLAGS) $(addprefix $(BUILD_DIR), $(filter %.o, $(DTD_OBJS) $(PARSEDTD_OBJECTS))) $(LOADLIBES) $(LDLIBS) -lpcre -o $(BIN_DIR)$(PARSEDTD_TARGET)

ifneq ($(MAKECMDGOALS), clean)
$(shell mkdir -p $(BIN_DIR) $(BUILD_DIR))
-include $(addprefix $(BUILD_DIR), $(addsuffix .d, $(basename $(filter %.o, $(DTD_OBJS) $(XML_OBJS) $(PARSEDTD_OBJECTS)))))
endif

$(BUILD_DIR)%.lex.d: $(BUILD_DIR)%.lex.cpp
	@$(CXX) -MM -MT '$@ $(addprefix $(BUILD_DIR), $(addsuffix .o, $(notdir $(basename $@))))' -MF $@ $<

$(BUILD_DIR)%.tab.d: $(BUILD_DIR)%.tab.cpp
	@$(CXX) -MM -MT '$@ $(addprefix $(BUILD_DIR), $(addsuffix .o, $(notdir $(basename $@))))' -MF $@ $<

$(BUILD_DIR)%.d: $(SRC_DIR)%.c
	@$(CC) -MM -MT '$@ $(addprefix $(BUILD_DIR), $(addsuffix .o, $(notdir $(basename $@))))' -MF $@ $<

$(BUILD_DIR)%.d: $(SRC_DIR)%.cpp
	@$(CXX) -MM -MT '$@ $(addprefix $(BUILD_DIR), $(addsuffix .o, $(notdir $(basename $@))))' -MF $@ $<

$(BUILD_DIR)%.lex.cpp: $(SRC_DIR)%.l
	$(FLEX) $(FLFLAGS) -P$(notdir $(basename $^)) -o$@ $^

$(BUILD_DIR)%.tab.cpp $(BUILD_DIR)%.tab.h: $(SRC_DIR)%.y
	$(BISON) $(BFLAGS) -o $@ -p $(notdir $(basename $^)) --defines=$(addprefix $(BUILD_DIR), $(addsuffix .tab.h, $(notdir $(basename $^)))) $^

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $(filter %.c, $^)

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $(filter %.cpp, $^)
