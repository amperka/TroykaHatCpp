VERSION = $(shell cat VERSION)

CXX = g++
CXX_FLAGS = -std=c++11 -Wall
LDLIB_WIRINGPI = -lwiringPi
LDLIB_FOR_EXAMPLES = -lGpioExpanderPi -lstdc++

LIB_FOLDER = src/

LIB_INST_DIR_DEST ?= /usr
LIB_INST_DIR_PREFIX ?= /local
LDCONFIG ?= ldconfig

LIB_TARGET = libGpioExpanderPi.so.$(VERSION) 
LIB_SOURCES = GpioExpanderPi.cpp
LIB_OBJECTS = GpioExpanderPi.o
LIB_HEADERS = GpioExpanderPi.h

EXAMPLE_SOURCES = examples/digitalWrite.cpp examples/digitalRead.cpp examples/analogReadWrite.cpp
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:.cpp=.o)
EXAMPLE_TARGETS = $(EXAMPLE_SOURCES:.cpp=)

.PHONY: all
all: $(LIB_TARGET)

.PHONY: examples
examples: $(EXAMPLE_TARGETS) clean-examples

$(LIB_TARGET): $(LIB_FOLDER)$(LIB_OBJECTS)
	@echo [Link lGpioExpanderPi library]
	$(CXX) $(CXX_FLAGS) -shared -o $(LIB_FOLDER)$(LIB_TARGET) $(LIB_FOLDER)$(LIB_OBJECTS) $(LDLIB_WIRINGPI)

$(LIB_FOLDER)$(LIB_OBJECTS): $(LIB_FOLDER)$(LIB_SOURCES)
	@echo [Compile lGpioExpanderPi library]
	$(CXX) $(CXX_FLAGS) -c $< -o $@

examples/digitalWrite: examples/digitalWrite.o
	@echo [Link example $< ]
	$(CXX) $(CXXFLAGS) -o $@ examples/digitalWrite.o $(LDLIB_WIRINGPI) $(LDLIB_FOR_EXAMPLES)

examples/digitalRead: examples/digitalRead.o
	@echo [Link example $< ]
	$(CXX) $(CXXFLAGS) -o $@ examples/digitalRead.o $(LDLIB_WIRINGPI) $(LDLIB_FOR_EXAMPLES)

examples/analogReadWrite: examples/analogReadWrite.o
	@echo [Link example $< ]
	$(CXX) $(CXXFLAGS) -o $@ examples/analogReadWrite.o $(LDLIB_WIRINGPI) $(LDLIB_FOR_EXAMPLES)

examples/%.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: install
install:
	@echo [Install lGpioExpanderPi library headers]
	install -m 0755 -d														$(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/include
	install -m 0644 $(LIB_FOLDER)$(LIB_HEADERS)										$(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/include	
	@echo [Install lGpioExpanderPi library]
	install -m 0755 -d														$(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/lib
	install -m 0755 $(LIB_FOLDER)$(LIB_TARGET)											$(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/lib/libGpioExpanderPi.so.$(VERSION)
	ln -sf $(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/lib/$(LIB_TARGET)		$(LIB_INST_DIR_DEST)/lib/libGpioExpanderPi.so
	$(LDCONFIG)

.PHONY:	uninstall
uninstall:
	@echo [Uninstall lGpioExpanderPi library]
	cd $(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/include/ && rm -f $(LIB_HEADERS)
	cd $(LIB_INST_DIR_DEST)$(LIB_INST_DIR_PREFIX)/lib/     && rm -f libGpioExpanderPi.*
	$(LDCONFIG)

.PHONY: clean 
clean:
	@echo [Clean]
	rm -f $(LIB_FOLDER)$(LIB_TARGET) $(LIB_FOLDER)$(LIB_OBJECTS)

.PHONY: clean-examples
clean-examples:
	@echo [Clean examples]
	rm -f $(EXAMPLE_OBJECTS)

