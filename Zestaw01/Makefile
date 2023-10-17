CXX := g++
CXXFLAGS := -Wall -Wextra -O3 -pedantic
LDFLAGS :=

HEADERS := $(wildcard *.hpp)
NAMES := $(patsubst %.cpp,%,$(wildcard *.cpp))
OBJS := $(patsubst %,%.o,$(NAMES))
TAR_FNAME := Milosz_Bargiel_Zestaw01.tar.gz
TO_COMPRESS := $(wildcard *.*)

EX_4_FILENAME := Generator.cpp
EX_5_FILENAME := ONP.cpp


.PHONY: all clean tar
all: Stack.x Generator.x ONP.x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

Generator.x: Generator.o $(HEADERS)

Stack.x: ArrayStack.o LinkedStack.o $(HEADERS) 

ONP.x: $(HEADERS)

main.x: main.o LinkedStack.o TemplateStack.o LinkedStack.hpp TemplateStack.hpp

clean:
	$(RM) $(wildcard *.[o|x])

tar:
	make clean
	tar -cvzf ../$(TAR_FNAME) $(TO_COMPRESS)
